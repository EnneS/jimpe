#include "VideoStream.h"


VideoStream::VideoStream(MyPanel* p, cv::Mat& f, wxMutex& m) : stream(0), panel(p), frame(f), mutex(m)
{
    stream >> frame;
}

VideoStream::~VideoStream()
{
    //dtor
}
void* VideoStream::Entry(){
    while(!TestDestroy())	// tant que le thread n'est pas détruit
    {
        if(stream.isOpened()){

            wxMilliSleep(10);
            mutex.Lock();
            stream >> frame;
            cv::cvtColor(frame, frame, CV_BGR2RGB);
            mutex.Unlock();

            wxCommandEvent* evt = new wxCommandEvent(NEW_FRAME_EVENT);
            wxQueueEvent(panel, evt);
        }

    }
    return NULL ;	// the thread is finished in a clean way
}
