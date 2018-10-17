#ifndef VIDEOSTREAM_H
#define VIDEOSTREAM_H

#include <wx/wx.h>
#include <opencv2/opencv.hpp>
class MyPanel;

wxDECLARE_EVENT(NEW_FRAME_EVENT, wxCommandEvent);

class VideoStream : public wxThread
{
    public:
        VideoStream(MyPanel* p, cv::Mat& f, wxMutex& m);
        ~VideoStream();
    private:
        cv::VideoCapture stream;
        MyPanel* panel;
        cv::Mat& frame;
        wxMutex& mutex;

        virtual void* Entry();
};
#include "MyPanel.h"
#endif // VIDEOSTREAM_H
