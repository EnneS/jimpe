#include "KDTree.h"

Node::Node(std::vector<point_type>& data, unsigned int* splits_var) : nb_split(splits_var){
    (*nb_split) = 0;
    points = data;

    treshold = 0;
    split_axis = 0;
    split_number = 1;
    higher = false;

    parent = nullptr;
    children = nullptr;
    updateAverage();
}
Node::Node(){

}

Node::Node(Node* p, std::vector<point_type>& parent_points, bool h) : nb_split(p->nb_split){
    treshold = 0;
    split_axis = 0;
    split_number = (*nb_split)+1;
    higher = h;

    parent = p;
    children = nullptr;
    setPoints(parent_points);
}

Node::~Node(){
    if(children)
        delete[] children;
}

void Node::setPoints(std::vector<point_type>& data){
    unsigned char xmin, xmax, ymin, ymax, zmin, zmax;
    getLimits(0, xmin, xmax);
    getLimits(1, ymin, ymax);
    getLimits(2, zmin, zmax);

    for(size_t i = 0; i < data.size(); i++){
        if(data[i].first[0] >= xmin && data[i].first[0] <= xmax &&
           data[i].first[1] >= ymin && data[i].first[1] <= ymax &&
           data[i].first[2] >= zmin && data[i].first[2] <= zmax){

            points.push_back(data[i]);
        }
    }
    updateAverage();
}

void Node::updateAverage(){
    unsigned long long total, x, y, z;
    total = x = y = z = 0;

    for(int i = 0; i < points.size(); i++){
        total += points[i].second;
        x += points[i].first[0] * points[i].second;
        y += points[i].first[1] * points[i].second;
        z += points[i].first[2] * points[i].second;
    }
    if(total == 0){
        total = 1;
    }
    average[0] = x/total;
    average[1] = y/total;
    average[2] = z/total;
}

void Node::split(unsigned char tresh, unsigned char axis){
    treshold = tresh;
    split_axis = axis;
    (*nb_split)++;

    children = new Node[2];
    children[0] = Node(this, points, false);
    children[1] = Node(this, points, true);

}
cv::Vec<unsigned char, 3>& Node::getColor(unsigned char* color, unsigned int N_color){
    if(split_number < N_color && children){
        if(color[split_axis] >= treshold){
            return children[1].getColor(color, N_color);
        }
        else{
            return children[0].getColor(color, N_color);
        }
    }
    else{
        return average;
    }
}

void Node::getLimits(unsigned char axis, unsigned char& lmin, unsigned char& lmax){
    lmin = 0;
    lmax = 255;
    getLow(axis, lmin);
    getHigh(axis, lmax);
}
void Node::getLow(unsigned char axis, unsigned char& current){
    if(!parent){
        return;
    }
    if(axis == parent->split_axis && higher && current < parent->treshold){
        current = parent->treshold;
    }
    parent->getLow(axis, current);
}
void Node::getHigh(unsigned char axis, unsigned char& current){
    if(!parent){
        return;
    }
    if(axis == parent->split_axis && !higher && current >= parent->treshold){
        current = parent->treshold-1;
    }
    parent->getHigh(axis, current);

}

void Node::otsu(unsigned char lmin, unsigned char lmax, unsigned char axis, float& maxVar, unsigned char& tresh){
    size_t nb_points = points.size();
    unsigned long long sum = 0;
    unsigned long long total = 0;
    unsigned long long wL = 0;
    unsigned long long wH = 0;

    float avgL = 0.0f;
    float avgH = 0.0f;

    float sumL = 0.0f;

    float bVar = 0.0f;

    for(size_t i = 0; i < nb_points; i++){
        sum += points[i].second * points[i].first[axis];
        total += points[i].second;
    }

    std::sort(points.begin(), points.end(), [axis](point_type& p1, point_type& p2)->bool{
        return p1.first[axis] < p2.first[axis];
    });

    for(size_t i = 0; i < nb_points; i++){ //valeurs de treshold possibles
        wL += points[i].second;

        wH = total - wL;
        if(wH == 0) break;

        sumL += ((float) points[i].second) * ((float) points[i].first[axis]);
        avgL = sumL/wL;
        avgH = (sum - sumL) / wH;

        bVar = (float)wL * (float)wH * (avgL - avgH) * (avgL - avgH);
        if(bVar > maxVar){
            maxVar = bVar;
            tresh = points[i].first[axis];
        }
    }
}

void Node::otsuAxes(float& maxVar, unsigned char& axis, unsigned char& tresh){
    unsigned char t_tresh = 0;
    float t_maxVar = 0.0f;
    unsigned char lmin;
    unsigned char lmax;

    for(unsigned char a = 0; a < 3; a++){
        getLimits(a, lmin, lmax);

        otsu(lmin, lmax, a, t_maxVar, t_tresh);

        if(t_maxVar > maxVar){
            maxVar = t_maxVar;
            axis = a;
            tresh = t_tresh;
        }

    }
}

void Node::getMaxVar(Node*& node, float& maxVar, unsigned char& axis, unsigned char& tresh){
    float t_maxVar = 0.0f;
    unsigned char t_axis = 0;
    unsigned char t_treshold = 0;

    if(!children){
        otsuAxes(t_maxVar, t_axis, t_treshold);
        if(t_maxVar > maxVar){
            maxVar = t_maxVar;
            axis = t_axis;
            node = this;
            tresh = t_treshold;
        }
    }
    else{
        children[0].getMaxVar(node, maxVar, axis, tresh);
        children[1].getMaxVar(node, maxVar, axis, tresh);
    }

}

void Node::maxVarSplit(){
    Node* node = this;
    float maxVar = 0.0f;
    unsigned char axis = 0;
    unsigned char tresh = 0;
    getMaxVar(node, maxVar, axis, tresh);
    node->split(tresh, axis);
}


KDTree::KDTree(cv::Mat& image)
{
    nb_split = 0;
    uchar* p = image.data;
    std::unordered_map<cv::Vec<unsigned char, 3>, unsigned char> data;
    size_t s = image.rows * image.cols * 3;

    cv::Vec<unsigned char, 3> point;
    for(size_t i = 0; i < s; i+=3){
        point[0] = p[i];
        point[1] = p[i+1];
        point[2] = p[i+2];

        auto ptr = data.find(point);
        if(ptr == data.end()){
            data.emplace(std::make_pair<>(point, (unsigned char)1));
        }
        else{
            ptr->second++;
        }

    }

    std::vector<point_type> output(data.begin(), data.end());

    root = new Node(output, &nb_split);
}

KDTree::~KDTree()
{
    delete root;
}

cv::Vec<unsigned char, 3> KDTree::getColor(unsigned char* color, unsigned int N_color){
    return root->getColor(color, N_color);
}

void KDTree::addColor(){
    std::cout << "color" << std::endl;
    root->maxVarSplit();
}
