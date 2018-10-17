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

}
void MyImage::Reload(){
    cv::Mat* img = image.GetFront();
    SetData(img->data, img->cols, img->rows, true);
}

