#ifndef KDTREE_H
#define KDTREE_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <array>
#include <unordered_map>
typedef std::pair<cv::Vec<unsigned char, 3>, unsigned char> point_type;

class Node{

public:
    Node(std::vector<point_type>& data, unsigned int* splits_var);
    ~Node();
    void maxVarSplit();
    void getMaxVar(Node*& node, float& maxVar, unsigned char& axis, unsigned char& tresh);
    void split(unsigned char tresh, unsigned char axis);
    cv::Vec<unsigned char, 3>& getColor(unsigned char* color, unsigned int N_color);

private:
    Node();
    Node(Node* p, std::vector<point_type>& parent_points, bool h);

    void otsuAxes(float& maxVar, unsigned char& axis, unsigned char& tresh);
    void otsu(unsigned char lmin, unsigned char lmax, unsigned char axis, float& maxVar, unsigned char& tresh);
    void getLimits(unsigned char axis, unsigned char& lmin, unsigned char& lmax);
    void getLow(unsigned char axis, unsigned char& current);
    void getHigh(unsigned char axis, unsigned char& current);
    void setPoints(std::vector<point_type>& data);
    void updateAverage();

    unsigned int* nb_split;

    std::vector<point_type> points;

    cv::Vec<unsigned char, 3> average;
    unsigned char treshold;
    unsigned char split_axis;
    unsigned int split_number;

    bool higher;

    Node* parent;
    Node* children;

};
namespace std{
    template<>
    struct hash<cv::Vec<unsigned char, 3>>{
        std::size_t operator()(const cv::Vec<unsigned char, 3>& input) const{
            using std::hash;
            using std::size_t;

            size_t output;
            unsigned char* ptr = (unsigned char*)&output;
            *(ptr++) = input[0];
            *(ptr++) = input[1];
            *(ptr++) = input[2];

            return output;
        }
    };
}
class KDTree
{
    public:
        KDTree(cv::Mat& image);
        virtual ~KDTree();
        cv::Vec<unsigned char, 3> getColor(unsigned char* color, unsigned int N_color);
        void addColor();
    protected:

    private:
        Node* root;
        unsigned int nb_split;
};

#endif // KDTREE_H
