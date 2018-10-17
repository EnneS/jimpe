#ifndef MYPANEL_H
#define MYPANEL_H

#include <wx/wx.h>
#include <opencv2/opencv.hpp>
#include "MyImage.h"
#include "MyThresholdDialog.h"
#include "MyRotateDialog.h"
#include "MyPosterizeDialog.h"
#include "VideoStream.h"
#include <iostream>

enum	// énumération. Elle gère la numérotation automatiquement
{
	ID_MiroirH = 0,
	ID_MiroirV,
	ID_Blur,
	ID_Rotate,
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
    void apply(MyImage* image){
        if(!active)
            return;

        switch(type){
            case ID_MiroirH:
                image->Mirror(true);
                break;
            case ID_MiroirV:
                image->Mirror(false);
                break;
            case ID_Blur:
                image->Blur(parameter);
                break;
            case ID_Rotate:
                if(parameter == 1)
                    image->Rotate90(true);
                else if(parameter == 2)
                    image->Rotate180();
                else if(parameter == 3)
                    image->Rotate90(false);

                break;
            case ID_Negative:
                image->Negative();
                break;
            case ID_Threshold:
                image->Threshold(parameter);
                break;
            case ID_Posterize:
                image->Posterize(parameter);
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
    void Negative();
    void Threshold();
    void Posterize();
    void showStream(wxCommandEvent& evt);
    void Rotate(int r);

private:
    int rotation;
    wxBitmap m_bitmap;	// used to display the image
    Effect effects[EFFECTS_COUNT];
    MyImage *m_image;		// used to load and process the image
    DoubleBuffer buffer;
    VideoStream thread;

};

#endif // MYPANEL_H
