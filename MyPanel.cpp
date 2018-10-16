#include "MyPanel.h"
#include <thread>
#include <chrono>
#include <cstring>
void MyPanel::onPaint(wxPaintEvent &WXUNUSED(event)){
    wxPaintDC dc(this);
    if(m_image){
        m_bitmap = wxBitmap(*m_image);
        dc.DrawBitmap(m_bitmap, 0, 0);
    }
}

MyPanel::MyPanel(wxWindow *parent) : wxPanel(parent), rotation(0), stream(0){
    Bind(wxEVT_PAINT, &MyPanel::onPaint, this) ;
    for(int i = 0; i < EFFECTS_COUNT; i++){
        effects[i] = Effect(i, 0);
    }

    cv::Mat m;
    stream >> m;
}

MyPanel::~MyPanel(void){
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
    rotation = (rotation+r) % 4;
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
        if(effects[ID_Posterize].toggle()){
            MyPosterizeDialog *dlg = new MyPosterizeDialog(this, -1, wxT("Postérisation"), wxDefaultPosition, wxSize(210,140)) ;
            int process = dlg->ShowModal();
            if(process == wxID_OK){
                effects[ID_Posterize].setParam(dlg->m_posterize->GetValue());
            }
        }
    }
    else {
        wxMessageDialog error(this, "Pas d'image ouverte");
        error.ShowModal();
    }
}

void MyPanel::showStream(){
    if(m_image){
        delete m_image;
        m_image = nullptr;
    }

    if(stream.isOpened()){
        cv::Mat frame;
        cv::Mat trans_avg = cv::Mat::eye(2,3,CV_64FC1);
        stream >> frame;

        m_image = new MyImage(frame.cols, frame.rows);
        std::memcpy(m_image->GetData(), frame.data, frame.cols * frame.rows * 3);

        for(int i = 0; i < EFFECTS_COUNT; i++){
            effects[i].apply(m_image);
        }
        Refresh();
        SetSize(m_image->GetSize());
        GetParent()->SetClientSize(m_image->GetSize());
    }
}

