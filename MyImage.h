#ifndef MYIMAGE_H
#define MYIMAGE_H
#include <wx/wx.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "DoubleBuffer.h"
#include "KDTree.h"
class MyImage : public wxImage
{
    public:
        MyImage(int largeur, int hauteur, DoubleBuffer& img);
        MyImage(DoubleBuffer& img);

        virtual ~MyImage();
        void Blur(int amount);
        void Negative();
        void Desaturate();
        void Saturate();
        void Saturation(int amount);
        void Hue(int rotation);
        void BrightnessContrast(int brightness, double contrast);
        void Gamma(double gamma);
        void Threshold(int seuil);
        void Mirror(bool horizontally);
        void Rotate90(bool clockwise);
        void Rotate180();
        void Posterize(int nb = 1);
        void Reload();
        void BorderDetect();
        void Quantization(KDTree* palette, int nb_colors);
    private:
        DoubleBuffer& image;
};

#endif // MYIMAGE_H
