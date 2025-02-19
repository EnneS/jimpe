#include "MyPanel.h"
#include <thread>
#include <chrono>
#include <cstring>

wxDEFINE_EVENT(NEW_FRAME_EVENT, wxCommandEvent);
wxDEFINE_EVENT(END_TASK_GEN_PALETTE, wxCommandEvent);


void MyPanel::onPaint(wxPaintEvent &WXUNUSED(event)){
    wxPaintDC dc(this);
    if(m_image){
        m_bitmap = wxBitmap(*m_image);
        dc.DrawBitmap(m_bitmap, 0, 0);
    }
}

MyPanel::MyPanel(wxWindow *parent) : wxPanel(parent), rotation(0){
    thread = new VideoStream(this, buffer);

    Bind(wxEVT_PAINT, &MyPanel::onPaint, this);
    Bind(NEW_FRAME_EVENT, &MyPanel::showStream, this);
    Bind(END_TASK_GEN_PALETTE, &MyPanel::paletteGenerated, this);

    current_palette = nullptr;
    processing_palette = nullptr;
    palette_thread = nullptr;

    for(int i = 0; i < EFFECTS_COUNT; i++){
        effects[i] = Effect(i, 0);
    }

    m_image = new MyImage(buffer);
    m_image->Reload();
    wxCommandEvent ev;

    thread->ForceRead();
    buffer.FlagFront();
    showStream(ev);


	thread->Create();
	thread->Run();


}


MyPanel::~MyPanel(void){

    thread->Delete();
    deleteThread();

    if(m_image){
        delete m_image;
        m_image = nullptr;
    }

}


void MyPanel::saveImage(wxString fileName){
    if(m_image){
        m_bitmap.SaveFile(fileName, wxBITMAP_DEFAULT_TYPE);
    } else {
        wxMessageDialog error(this, "Pas d'image ouverte");
        error.ShowModal();
    }
}

// ===================
// == PROCESS IMAGE ==
// ===================

void MyPanel::Miroir(bool horizontal){
    if(m_image){
        m_image->Mirror(horizontal);
        if(horizontal)
            effects[ID_MiroirH].toggle();
        else
            effects[ID_MiroirV].toggle();

    } else {
        wxMessageDialog error(this, "Pas d'image ouverte");
        error.ShowModal();
    }
}

void MyPanel::Blur(int value){
    if(m_image){
        if(value == -1){
            effects[ID_Blur].setActive(false);
        } else {
            if(!effects[ID_Blur].isActive())
                effects[ID_Blur].setActive(true);
            effects[ID_Blur].setParam(value);
        }
    } else {
        wxMessageDialog error(this, "Pas d'image ouverte");
        error.ShowModal();
    }
}


void MyPanel::Rotate(int r){
    rotation += r;
    if(rotation >= 4)
        rotation -= 4;
    if(rotation < 0)
        rotation += 4;

    if(m_image){
        effects[ID_Rotate].setParam(rotation);
        effects[ID_Rotate].setActive(true);
    }
    else {
        wxMessageDialog error(this, "Pas d'image ouverte");
        error.ShowModal();
    }
}

void MyPanel::Negative(){
    if(m_image){
        effects[ID_Negative].toggle();
    } else {
        wxMessageDialog error(this, "Pas d'image ouverte");
        error.ShowModal();
    }


}

void MyPanel::Threshold(int value){
    if(m_image){
        if(value == -1){
            effects[ID_Threshold].setActive(false);
        } else {
            if(!effects[ID_Threshold].isActive())
                effects[ID_Threshold].setActive(true);
            effects[ID_Threshold].setParam(value);
        }
    }
    else {
        wxMessageDialog error(this, "Pas d'image ouverte");
        error.ShowModal();
    }
}

void MyPanel::Posterize(int value){
    if(m_image){
        if(value == -1){
            effects[ID_Posterize].setActive(false);
        } else {
            if(!effects[ID_Posterize].isActive())
                effects[ID_Posterize].setActive(true);
            effects[ID_Posterize].setParam(value);
        }
    } else {
        wxMessageDialog error(this, "Pas d'image ouverte");
        error.ShowModal();
    }
}

void MyPanel::BorderDetect(){
    if(m_image){
        effects[ID_BorderDetect].toggle();
    } else {
        wxMessageDialog error(this, "Pas d'image ouverte");
        error.ShowModal();
    }
}

void MyPanel::Saturation(int factor){
    if(m_image){
        if(factor == -256){
            effects[ID_Saturation].setActive(false);
        } else {
            if(!effects[ID_Saturation].isActive())
                effects[ID_Saturation].setActive(true);
            effects[ID_Saturation].setParam(factor);
        }
    } else {
        wxMessageDialog error(this, "Pas d'image ouverte");
        error.ShowModal();
    }
}

void MyPanel::Gamma(int factor){

    double factorDouble = factor/100.0;
    if(m_image){
        if(factor == -1){
            effects[ID_Gamma].setActive(false);
        } else {
            if(!effects[ID_Gamma].isActive())
                effects[ID_Gamma].setActive(true);
            effects[ID_Gamma].setDoubleParam(factorDouble);
        }
    } else {
        wxMessageDialog error(this, "Pas d'image ouverte");
        error.ShowModal();
    }
}

void MyPanel::Hue(int value){
    if(m_image){
        if(value == -1){
            effects[ID_Hue].setActive(false);
        } else {
            if(!effects[ID_Hue].isActive())
                effects[ID_Hue].setActive(true);
            effects[ID_Hue].setParam(value);
        }
    } else {
        wxMessageDialog error(this, "Pas d'image ouverte");
        error.ShowModal();
    }
}

void MyPanel::BrightnessContrast(int brightness, int contrast){
    if(m_image){
        if(brightness == -1){
            effects[ID_BrightnessContrast].setActive(false);
        } else {
            if(!effects[ID_BrightnessContrast].isActive())
                effects[ID_BrightnessContrast].setActive(true);
                effects[ID_BrightnessContrast].setParam(brightness);
                effects[ID_BrightnessContrast].setParam(contrast/100.0);
        }
    } else {
        wxMessageDialog error(this, "Pas d'image ouverte");
        error.ShowModal();
    }
}

void MyPanel::debug(int i){
    debug_var = i;

}
void MyPanel::showStream(wxCommandEvent& evt){



    for(int i = 0; i < EFFECTS_COUNT; i++){
        effects[i].apply(m_image);
    }

    m_image->Reload();

    Refresh();
    SetSize(m_image->GetSize());
    buffer.FlagFront();
}

void MyPanel::generatePalette(int nb_colors){
    if(m_image){
        if(nb_colors == -1){
            effects[ID_Quantization].setActive(false);
        } else {
            deleteThread();

            if(processing_palette){
                delete processing_palette;
                processing_palette = nullptr;
            }
            effects[ID_Quantization].setParam(nb_colors);
            palette_thread = new GeneratePaletteThread(this, buffer, processing_palette, nb_colors);

            palette_thread->Create();
            palette_thread->Run();
        }
    }
}
void MyPanel::paletteGenerated(wxCommandEvent& evt){

    if(current_palette){
        delete current_palette;
    }
    palette_thread = nullptr;
    current_palette = processing_palette;
    processing_palette = nullptr;

    effects[ID_Quantization].setPointer(current_palette);
    effects[ID_Quantization].setActive(true);
}

void MyPanel::deleteThread(){
    {
        wxCriticalSectionLocker enter(palette_thread_cs);
        if (palette_thread)
        {
            palette_thread->Delete();
        }
    }
}







