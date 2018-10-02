#ifndef MYPANEL_H
#define MYPANEL_H

#include <wx/wx.h>
#include "MyImage.h"
#include "MyThresholdDialog.h"
#include "MyRotateDialog.h"
#include "MyPosterizeDialog.h"
#include "WebcamStream.h"

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
    void Rotate();
    void Negative();
    void Threshold();
    void Posterize();
    void showStream();

private:
    wxBitmap m_bitmap;	// used to display the image
    MyImage *m_image;		// used to load and process the image
    cv::VideoCapture stream;
};

#endif // MYPANEL_H
