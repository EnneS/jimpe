#ifndef MYPANEL_H
#define MYPANEL_H

#include <wx/wx.h>
#include <opencv2/opencv.hpp>
#include "MyImage.h"
#include "MyThresholdDialog.h"
#include "MyRotateDialog.h"
#include "MyPosterizeDialog.h"
#include "VideoStream.h"
#include "GeneratePaletteThread.h"
#include <iostream>

enum	// énumération. Elle gère la numérotation automatiquement
{
	ID_MiroirH = 0,
	ID_MiroirV,
	ID_Rotate,
	ID_Quantization,
	ID_BorderDetect,
	ID_Posterize,
    ID_Negative,
    ID_Hue,
    ID_Saturation,
    ID_BrightnessContrast,
    ID_Gamma,
    ID_Blur,
    ID_Threshold,

	EFFECTS_COUNT
};

class Effect{
private:
    bool active;
    int parameter;
    double doubleParameter;
    unsigned int type;
    void* pointer;

public:
    Effect(int type_ = 0, int param = 0, void* ptr = nullptr, double db = 0.0) : active(false), parameter(param), type(type_), pointer(ptr), doubleParameter(db)
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
    void setParam(int param){
        parameter = param;
    }
    void setDoubleParam(bool db){
        doubleParameter = db;
    }
    void setPointer(void* ptr){
        pointer = ptr;
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
            case ID_BorderDetect:
                image->BorderDetect();
                break;
            case ID_Quantization:
                image->Quantization((KDTree*)pointer, parameter);
                break;
            case ID_Saturation:
                image->Saturation(parameter);
                break;
            case ID_Hue:
                image->Hue(parameter);
                break;
            case ID_BrightnessContrast:
                image->BrightnessContrast(parameter, doubleParameter);
                break;
            case ID_Gamma:
                image->Gamma(doubleParameter);
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
    void Rotate(int r);
    void Blur();
    void Negative();
    void Threshold();
    void Posterize();
    void BorderDetect();
    void Desaturate();
    void Saturate();
    void Saturation(double factor);

    void showStream(wxCommandEvent& evt);
    void generatePalette(int nb_colors);
    void paletteGenerated(wxCommandEvent& evt);

    void debug(int i);


private:
    void deleteThread();
    wxCriticalSection palette_thread_cs;
    int rotation;
    wxBitmap m_bitmap;	// used to display the image
    Effect effects[EFFECTS_COUNT];
    MyImage *m_image;		// used to load and process the image
    DoubleBuffer buffer;
    VideoStream* thread;
    int debug_var;
    KDTree* current_palette;
    KDTree* processing_palette;
    GeneratePaletteThread* palette_thread;

};

#endif // MYPANEL_H
