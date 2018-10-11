#ifndef MYIMAGE_H
#define MYIMAGE_H
#include <wx/wx.h>
#include <iostream>

class MyImage : public wxImage
{
    public:
        MyImage(const wxString& fileName);
        MyImage(wxImage image);
        MyImage(int largeur, int hauteur);
        MyImage();
        virtual ~MyImage();
        MyImage* Blur(int amount);
        MyImage* Negative();
        MyImage* Desaturate();
        MyImage* Threshold(int seuil);
        MyImage* Mirror(bool horizontally);
        MyImage* Rotate90(bool clockwise);
        MyImage* Rotate180();
        MyImage* Posterize(int nb = 1);
    protected:

    private:
};

#endif // MYIMAGE_H
