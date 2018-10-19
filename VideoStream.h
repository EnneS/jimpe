#ifndef VIDEOSTREAM_H
#define VIDEOSTREAM_H
#include "DoubleBuffer.h"
#include <wx/wx.h>
#include <opencv2/opencv.hpp>
class MyPanel;

wxDECLARE_EVENT(NEW_FRAME_EVENT, wxCommandEvent);

class VideoStream : public wxThread
{
    public:
        VideoStream(MyPanel* p, DoubleBuffer& b);
        ~VideoStream();
    private:
        cv::VideoCapture stream;
        MyPanel* panel;
        DoubleBuffer& buffer;
        int frameDelay;
        long long int time;
        virtual void* Entry();
};
#include "MyPanel.h"
#endif // VIDEOSTREAM_H
