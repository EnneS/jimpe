#include "MyImage.h"
#include <cstdlib>
#include <cmath>
MyImage::MyImage(int largeur, int hauteur, DoubleBuffer& img): wxImage(largeur, hauteur), image(img){}

MyImage::MyImage(DoubleBuffer& img) : wxImage(), image(img){}


MyImage::~MyImage()
{
    //dtor
}

void MyImage::Blur(int amount){
    int kernel_size = amount*2 + 1;
    cv::Mat* img = image.GetFront();
    cv::Mat tmp;

    cv::GaussianBlur(*img, tmp, cv::Size(kernel_size, kernel_size), 0.0, 0.0, cv::BORDER_DEFAULT);
    *img = tmp;
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
void MyImage::Saturate(){
    Posterize(1);
}
/*
void MyImage::Saturation(double factor){
    cv::Mat original = image.GetFront()->clone();
    cv::Mat* img = image.GetFront();
    if(factor < 0.0){
        Desaturate();
        factor = -factor;
    }
    else{
        Saturate();
    }

    cv::addWeighted(*img, factor, original, 1.0 - factor, 0.0, *img);
}*/

void MyImage::Saturation(int amount){
    cv::Mat* img = image.GetFront();
    cv::cvtColor(*img, *img, CV_RGB2HSV);

    unsigned char* data = img->data;
    size_t s = img->rows * img->cols * 3;
    for(size_t i = 1; i < s; i+=3){
        data[i] = cv::saturate_cast<uchar>(data[i] + amount);
    }

    cv::cvtColor(*img, *img, CV_HSV2RGB);
}

void MyImage::Hue(int rotation){
    cv::Mat* img = image.GetFront();
    cv::cvtColor(*img, *img, CV_RGB2HSV);

    unsigned char* data = img->data;
    size_t s = img->rows * img->cols * 3;
    for(size_t i = 0; i < s; i+=3){
        data[i] = cv::saturate_cast<uchar>(data[i] + rotation);
    }

    cv::cvtColor(*img, *img, CV_HSV2RGB);
}

void MyImage::BrightnessContrast(int brightness, double contrast){
    cv::Mat* img = image.GetFront();
    unsigned char* data = img->data;
    size_t s = img->rows * img->cols * 3;
    for(size_t i = 0; i < s; i++){
        data[i] = cv::saturate_cast<uchar>(contrast * data[i] + brightness);
    }
}
void MyImage::Gamma(double gamma){
    cv::Mat* img = image.GetFront();
    cv::Mat lut(1, 256, CV_8U);
    unsigned char* data = lut.data;
    for(int i = 0; i < 256; i++){
        data[i] = cv::saturate_cast<uchar>(pow(i/255.0, gamma) * 255.0);
    }
    cv::LUT(*img, lut, *img);
}

void MyImage::Threshold(int seuil){
    cv::Mat* img = image.GetFront();
    cv::cvtColor(*img, *img, CV_RGB2GRAY);
    cv::threshold(*img, *img, (double)seuil, (double)255, CV_THRESH_BINARY);
    cv::cvtColor(*img, *img, CV_GRAY2RGB);
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
    cv::Mat lut(1, 256, CV_8U);
    unsigned char m = 255;
    unsigned char nbCouleurs = 1 << nb;
    unsigned char* data = lut.data;
    for(int i = 0; i < 256; i++){
        data[i] = (i / (256/nbCouleurs)) * (m / (nbCouleurs - 1));
    }
    cv::LUT(*img, lut, *img);
}
void MyImage::BorderDetect(){
    float data[9] = {1, 1, 1, 1, -8, 1, 1, 1, 1};
    cv::Mat* img = image.GetFront();
    cv::Mat kernel = cv::Mat(3, 3, CV_32F, data);
    cv::Mat dst = cv::Mat(img->rows, img->cols, CV_8UC3);
    cv::filter2D(*img, dst, -1, kernel, cv::Point(-1, -1), 0, cv::BORDER_CONSTANT);
    *img = dst;
}

void MyImage::Quantization(KDTree* palette, int nb_colors){
    std::cout << "quant" << std::endl;
    cv::Vec<unsigned char, 3> color;
    cv::Mat* img = image.GetFront();
    unsigned char* data = img->data;
    size_t s = img->rows * img->cols * 3;
    //s = 40000;
    for(size_t i = 0; i < s; i+=3){
        color = palette->getColor(data + i, nb_colors);
        data[i] = color[0];
        data[i+1] = color[1];
        data[i+2] = color[2];
    }
}

void MyImage::Reload(){
    cv::Mat* img = image.GetFront();
    SetData(img->data, img->cols, img->rows, true);
}

