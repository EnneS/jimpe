#include "MyImage.h"
#include <cstdlib>

MyImage::MyImage(int largeur, int hauteur, DoubleBuffer& img): wxImage(largeur, hauteur), image(img){}

MyImage::MyImage(DoubleBuffer& img) : wxImage(), image(img){}


MyImage::~MyImage()
{
    //dtor
}

void MyImage::Blur(int amount){

}
void MyImage::Negative(){
    cv::Mat* img = image.GetFront();
    cv::bitwise_not(*img, *img);
}
void MyImage::Desaturate(){
    cv::Mat* img = image.GetFront();
    cv::cvtColor(*img, *img, CV_RGB2GRAY);
    cv::cvtColor(*img, *img, CV_GRAY2RGB);
}
void MyImage::Threshold(int seuil){
    cv::Mat* img = image.GetFront();
    cv::threshold(*img, *img, (double)seuil, (double)255, CV_THRESH_BINARY);
}
void MyImage::Mirror(bool horizontally){
    cv::Mat* img = image.GetFront();
    cv::Mat dst = cv::Mat(img->rows, img->cols, CV_8UC3);
    cv::flip(*img, dst, (int)horizontally);
    *img = dst;
}
void MyImage::Rotate90(bool clockwise){
    cv::Mat* img = image.GetFront();
    cv::Mat dst = cv::Mat(img->rows, img->cols, CV_8UC3);
    cv::transpose(*img, dst);
    cv::flip(dst, *img, (int)clockwise);
}
void MyImage::Rotate180(){
    cv::Mat* img = image.GetFront();
    cv::Mat dst = cv::Mat(img->rows, img->cols, CV_8UC3);
    cv::flip(*img, dst, -1);
    *img = dst;
}
void MyImage::Posterize(int nb){
    cv::Mat* img = image.GetFront();
    unsigned char* data = img->ptr();
    unsigned char lookup_table[256];
    unsigned char m = 255;
    int length = (img->rows * img->cols * 3);
    unsigned char nbCouleurs = 1 << nb;

    for(int i = 0; i < 256; i++){
        lookup_table[i] = (i / (256/nbCouleurs)) * (m / (nbCouleurs - 1));
    }

    for(unsigned long i = 0; i < length; i++){
        data[i] = lookup_table[data[i]];
    }
}
void MyImage::BorderDetect(){
    float data[9] = {1, 1, 1, 1, -8, 1, 1, 1, 1};
    cv::Mat* img = image.GetFront();
    cv::Mat kernel = cv::Mat(3, 3, CV_32F, data);
    cv::Mat dst = cv::Mat(img->rows, img->cols, CV_8UC3);
    cv::filter2D(*img, dst, -1, kernel, cv::Point(-1, -1), 0, cv::BORDER_CONSTANT);
    *img = dst;
}

void MyImage::Quantization(KDTree* palette){
    cv::Vec<unsigned char, 3> color;
    cv::Mat* img = image.GetFront();
    unsigned char* data = img->data;
    size_t s = img->rows * img->cols * 3;
    //s = 40000;
    for(size_t i = 0; i < s; i+=3){
        color = palette->getColor(data + i, 4);
        data[i] = color[0];
        data[i+1] = color[1];
        data[i+2] = color[2];
    }
}

void MyImage::Reload(){
    cv::Mat* img = image.GetFront();
    SetData(img->data, img->cols, img->rows, true);
}

