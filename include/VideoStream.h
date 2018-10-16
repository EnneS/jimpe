#ifndef VIDEOSTREAM_H
#define VIDEOSTREAM_H

#include <wx/wx.h>

class MyPanel;

class VideoStream : public wxThread
{
    public:
        VideoStream(MyPanel* p);
        ~VideoStream();

    private:
        MyPanel* m_panel;
        virtual void* Entry();
};
#include "MyPanel.h"
#endif // VIDEOSTREAM_H
