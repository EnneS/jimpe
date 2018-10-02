#include "MyImage.h"
MyImage::MyImage(const wxString& fileName): wxImage(fileName){}

MyImage::MyImage(wxImage image): wxImage(image){}


MyImage::MyImage(int largeur, int hauteur): wxImage(largeur, hauteur){}

MyImage::MyImage(): wxImage(){}


MyImage::~MyImage()
{
    //dtor
}

MyImage MyImage::Negative(){
    unsigned char* data = GetData();
    int length = (GetWidth() * GetHeight() * 3);
    for(unsigned long i = 0; i < length ; i++){
        data[i] = 255-data[i];
    }
    return *this;
}

MyImage MyImage::Desaturate(){
    unsigned char* data = GetData();
    float moyenne;
    int length = (GetWidth() * GetHeight() * 3);
    for(unsigned long i = 0; i < length; i+=3){
        moyenne = (data[i] + data[i+1] + data[i+2])/3.0f;
        data[i] = (int) moyenne;
        data[i+1] = (int) moyenne;
        data[i+2] = (int) moyenne;
    }
    return *this;
}

MyImage MyImage::Threshold(int seuil){
    unsigned char* data = GetData();
    float moyenne;
    register int val;
    int length = (GetWidth() * GetHeight() * 3);
    for(unsigned long i = 0; i < length; i+=3){
        moyenne = (data[i] + data[i+1] + data[i+2])/3.0f;
        val = moyenne<=seuil?0:255;
        data[i] = val;
        data[i+1] = val;
        data[i+2] = val;
    }
    return *this;
}

MyImage* MyImage::Rotate180(){
    int length = (GetWidth() * GetHeight() * 3);
    unsigned char* data = GetData();
    unsigned char* dataBuffer = new unsigned char[length];

    for(unsigned long i = 0; i < length; i+=3){
        dataBuffer[i] = data[length - i];
        dataBuffer[i+1] = data[length - i+1];
        dataBuffer[i+2] = data[length - i+2];
    }
    MyImage* newImage = new MyImage(wxImage(GetWidth(), GetHeight(), dataBuffer));
    return newImage;
}

MyImage* MyImage::Mirror(bool horizontally){
    int length = (GetWidth() * GetHeight() * 3);
    int height = GetHeight();
    int width = GetWidth();
    int full_width = GetWidth()*3;

    unsigned char* dataBuffer = new unsigned char[length];
    unsigned char* data = GetData();

    if(horizontally){
        int line_i = 0;
        int line_s = 0;
        for(unsigned long i = 0; i < length; i+=3){
            line_i = i % full_width;
            line_s = i - line_i;
            dataBuffer[i] = data[line_s + full_width - 3 - line_i];
            dataBuffer[i+1] = data[line_s + full_width - 3 - line_i+1];
            dataBuffer[i+2] = data[line_s + full_width - 3 - line_i+2];
        }
    } else {
        int indice = 0;
        for(unsigned long i = 0; i < length; i++){
            indice = length-(full_width-(i%full_width)) - full_width*(i/full_width);
            dataBuffer[i] = data[indice];
        }
    }

    MyImage* newImage = new MyImage(wxImage(GetWidth(), GetHeight(), dataBuffer));
    return newImage;
}

MyImage* MyImage::Rotate90(bool clockwise = true){
    unsigned char * data = GetData();
    int length = (GetWidth() * GetHeight() * 3);
    unsigned char* dataBuffer = new unsigned char[length];
    int height = GetHeight();
    int width = GetWidth();
    int full_width = width*3;
    int indice = 0;
    if(clockwise){
        for(unsigned long i = 0; i < length/3; i++){
                // filtre 3x3 rotated LCD pop rgb v2 : indice = (i%height)*full_width + (i*3)/height;

                indice = length - ((i%height)*width + width - i/height )*3;
                dataBuffer[3*i] = data[indice];
                dataBuffer[3*i+1] = data[indice+1];
                dataBuffer[3*i+2] = data[indice+2];

        }
    } else {
         for(unsigned long i = 0; i < length/3; i++){
                // filtre 3x3 ecran pop rgb v2 : indice = (i%height)*full_width + (i*3)/height;

                indice = ((i%height)*width + width - 1 - i/height )*3;
                dataBuffer[3*i] = data[indice];
                dataBuffer[3*i+1] = data[indice+1];
                dataBuffer[3*i+2] = data[indice+2];

        }
    }

    /*for(unsigned long i = 0; i < length; i+=3){
        dataBuffer[i] = data[((i+GetWidth()+(GetWidth()-1)*(i-1))%(GetWidth()*GetHeight()*3-1))-GetWidth()];
        dataBuffer[i+1] = data[((i+1+GetWidth()+(GetWidth()-1)*(i))%(GetWidth()*GetHeight()*3-1))-GetWidth()];
        dataBuffer[i+2] = data[((i+2+GetWidth()+(GetWidth()-1)*(i+1))%(GetWidth()*GetHeight()*3-1))-GetWidth()];
    }*/
    MyImage* newImage = new MyImage(wxImage(GetHeight(), GetWidth(), dataBuffer));
    return newImage;
}


MyImage MyImage::Posterize(int nb){
    unsigned char* data = GetData();
    unsigned char lookup_table[256];
    unsigned char m = 255;
    int length = (GetWidth() * GetHeight() * 3);
    unsigned char nbCouleurs = 1 << nb;

    for(int i = 0; i < 256; i++){
        lookup_table[i] = (i / (256/nbCouleurs)) * (m / (nbCouleurs - 1));
    }

    for(unsigned long i = 0; i < length; i++){
        /*data[i] = data[i] | ( m >> nbCouleur);
        data[i+1] = data[i+1] | ( m >> nbCouleur);
        data[i+2] = data[i+2] | ( m >> nbCouleur);

        data[i] = data[i] - data[i] % (256 >> nbCouleur);
        data[i+1] = data[i+1] - data[i+1] % (256 >> nbCouleur);
        data[i+2] = data[i+2] - data[i+2] % (256 >> nbCouleur);
*/
        data[i] = lookup_table[data[i]];

    }
    return *this;
}
