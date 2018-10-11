#ifndef MYPANEL_H
#define MYPANEL_H

#include <wx/wx.h>
#include "MyImage.h"
#include "MyThresholdDialog.h"
#include "MyRotateDialog.h"
#include "MyPosterizeDialog.h"
#include "WebcamStream.h"

enum	// énumération. Elle gère la numérotation automatiquement
{
	ID_MiroirH = 0,
	ID_MiroirV,
	ID_Blur,
	ID_RotateL,
	ID_RotateR,
	ID_Negative,
	ID_Threshold,
	ID_Posterize,

	EFFECTS_COUNT
};

class Effect{
private:
    bool active;
    unsigned int parameter;
    unsigned int type;

public:
    Effect(int type_ = 0, int param = 0) : active(false), parameter(param), type(type_)
    {}
    bool toggle(){
        return active = !active;
    }
    bool isActive(){
        return active;
    }
    void setActive(bool active_){
        active = active_;
    }
    void setParam(unsigned int param){
        parameter = param;
    }
    MyImage* apply(MyImage* image){
        if(!active)
            return image;

        switch(type){
            case ID_MiroirH:
                return image->Mirror(true);
                break;
            case ID_MiroirV:
                return image->Mirror(false);
                break;
            case ID_Blur:
                return image->Blur(parameter);
                break;
            case ID_RotateL:
            case ID_RotateR:
                if(parameter == 1)
                    return image->Rotate90(true);
                else if(parameter == 2)
                    return image->Rotate180();
                else if(parameter == 3)
                    return image->Rotate90(false);

                break;
            case ID_Negative:
                return image->Negative();
                break;
            case ID_Threshold:
                return image->Threshold(parameter);
                break;
            case ID_Posterize:
                return image->Posterize(parameter);
                break;
        }
    }
};

class MyPanel: public wxPanel
{
public:
    MyPanel( wxWindow *parent ) ;
    ~MyPanel() ;
    void openImage(wxString fileName);
    void onPaint(wxPaintEvent &WXUNUSED(event));
    void saveImage(wxString fileName);
    void Miroir(bool horizontal);
    void Blur();
    void Rotate90();
    void RotateCounter90();
    void Negative();
    void Threshold();
    void Posterize();
    void showStream();

private:
    void Rotate();
    int rotation;
    wxBitmap m_bitmap;	// used to display the image
    MyImage *m_image;		// used to load and process the image
    cv::VideoCapture stream;
    cv::Mat prev_frame;
    Effect effects[EFFECTS_COUNT];
};

#endif // MYPANEL_H
