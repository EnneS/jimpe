#ifndef VIDEOSTREAM_H
#define VIDEOSTREAM_H

#include <wx/wx.h>
#include <opencv2/opencv.hpp>
class MyPanel;

wxDECLARE_EVENT(NEW_FRAME_EVENT, wxCommandEvent);
wxDEFINE_EVENT(NEW_FRAME_EVENT, wxCommandEvent);

class VideoStream : public wxThread
{
    public:
        VideoStream(MyPanel* p, cv::Mat& f, wxMutex& m);
        ~VideoStream();
    private:
        MyPanel* panel;
        wxMutex& mutex;
        cv::Mat& frame;
        cv::VideoCapture stream;
        virtual void* Entry();
};
#include "MyPanel.h"
#endif // VIDEOSTREAM_H
