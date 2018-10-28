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

void MyPanel::Blur(){
    if(m_image){
        effects[ID_Blur].setParam(3);
        effects[ID_Blur].toggle();

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

void MyPanel::Threshold(){
    if(m_image){
        if(effects[ID_Threshold].toggle()){
            MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Seuillage"), wxDefaultPosition, wxSize(210,140)) ;
            int process = dlg->ShowModal();
            if(process == wxID_OK){
                effects[ID_Threshold].setParam(dlg->m_threshold->GetValue());
                delete dlg;
            }
        }
    }
    else {
        wxMessageDialog error(this, "Pas d'image ouverte");
        error.ShowModal();
    }
}

void MyPanel::Posterize(){
    if(m_image){
        effects[ID_Posterize].setParam(2);
        effects[ID_Posterize].toggle();
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
void MyPanel::debug(int i){
    debug_var = i;

}
void MyPanel::showStream(wxCommandEvent& evt){



    for(int i = 0; i < EFFECTS_COUNT; i++){
        effects[i].apply(m_image);
    }

    std::cout << "display" << std::endl;
    m_image->Reload();

    Refresh();
    SetSize(m_image->GetSize());
    buffer.FlagFront();
}

void MyPanel::generatePalette(int nb_colors){
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







