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

MyPanel::MyPanel(wxWindow *parent) : wxPanel(parent), stream(0){
    Bind(wxEVT_PAINT, &MyPanel::onPaint, this) ;
    cv::Mat m;
    stream >> m;
}
MyPanel::~MyPanel(void){
    if(m_image){
        delete m_image;
        m_image = nullptr;
    }
}

void MyPanel::openImage(wxString fileName){

    showStream();


    Refresh();
    SetSize(m_image->GetSize());
    GetParent()->SetClientSize(m_image->GetSize());
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
        MyImage* img = m_image->Mirror(horizontal);
        delete m_image;
        m_image = img;
        Refresh();
    } else {
        wxMessageDialog error(this, "Pas d'image ouverte");
        error.ShowModal();
    }
}

void MyPanel::Blur(){
    if(m_image){
        MyImage * img = new MyImage(m_image->Blur(3));
        delete m_image;
        m_image = img;
        Refresh();
    } else {
        wxMessageDialog error(this, "Pas d'image ouverte");
        error.ShowModal();
    }
}

void MyPanel::Rotate(){
    if(m_image){
        MyRotateDialog *dlg = new MyRotateDialog(this, -1, wxDefaultPosition, wxSize(250,140)) ;
        int process = dlg->ShowModal();
        if(process == wxID_OK){
            int rotateValue = dlg->RadioBox1->GetSelection();
            MyImage* img;
            if(rotateValue == 0){
                img = m_image->Rotate90(true);
            } else if(rotateValue == 1){
                img = m_image->Rotate180();
            } else {
                img = m_image->Rotate90(false);
            }
            delete m_image;
            delete dlg;
            m_image = img;
            Refresh();
            SetSize(m_image->GetSize());
            GetParent()->SetClientSize(m_image->GetSize());
        }

    } else {
        wxMessageDialog error(this, "Pas d'image ouverte");
        error.ShowModal();
    }
}

void MyPanel::Negative(){
    if(m_image){
        MyImage* img = new MyImage();
        *img = m_image->Negative();
        delete m_image;
        m_image = img;
        Refresh();
    } else {
        wxMessageDialog error(this, "Pas d'image ouverte");
        error.ShowModal();
    }
}

void MyPanel::Threshold(){
    if(m_image){
        MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Seuillage"), wxDefaultPosition, wxSize(210,140)) ;
        int process = dlg->ShowModal();
        if(process == wxID_OK){
            MyImage* img = new MyImage();
            *img = m_image->Threshold(dlg->m_threshold->GetValue());
            delete m_image;
            delete dlg;
            m_image = img;
            Refresh();
        }
    } else {
        wxMessageDialog error(this, "Pas d'image ouverte");
        error.ShowModal();
    }
}

void MyPanel::Posterize(){
    if(m_image){/*
        MyPosterizeDialog *dlg = new MyPosterizeDialog(this, -1, wxT("Postérisation"), wxDefaultPosition, wxSize(210,140)) ;
        int process = dlg->ShowModal();
        if(process == wxID_OK){
            MyImage* img = new MyImage();
            *img = m_image->Posterize(dlg->m_posterize->GetValue());
            delete m_image;
            delete dlg;
            m_image = img;
            Refresh();
        }*/
        showStream();
        Refresh();
        SetSize(m_image->GetSize());
            GetParent()->SetClientSize(m_image->GetSize());
    } else {
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
https://stackoverflow.com/questions/21622608/video-stabilization-using-opencv
        stream >> frame;
        cv::cvtColor(frame, frame, CV_BGR2RGB, 3);
        cv::Mat trans;
        if(!prev_frame.empty())
        {
            trans=estimateRigidTransform(frame,prev_frame,0);
            trans(cv::Range(0,2),cv::Range(0,2))=cv::Mat::eye(2,2,CV_64FC1);
            trans_avg+=(trans-trans_avg)/2.0;
            warpAffine(frame,warped,trans_avg,Size( frame.cols, frame.rows));

            imshow("Camw",warped);
        }

        m_image = new MyImage(frame.cols, frame.rows);
        std::memcpy(m_image->GetData(), frame.data, frame.cols * frame.rows * 3);
    }
}
