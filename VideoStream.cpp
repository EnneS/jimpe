#include "VideoStream.h"


VideoStream::VideoStream(MyPanel* p, DoubleBuffer& b) : stream("vid.mp4"), panel(p), buffer(b)
{
    frameDelay = 1000 / stream.get(CV_CAP_PROP_FPS);
}

VideoStream::~VideoStream()
{
    //dtor
}
void* VideoStream::Entry(){
    while(!TestDestroy())	// tant que le thread n'est pas détruit
    {
        if(stream.isOpened()){
            long long int currentTime;
            wxLongLong t = wxGetLocalTimeMillis();
            *((long*)((void*)(&currentTime))) = t.GetLo();
            *((long*)((void*)(&currentTime))+1) = t.GetHi();


            wxMilliSleep(std::max(0LL, frameDelay + time - currentTime));

            cv::Mat* frame = buffer.GetBack();
            stream >> *frame;
            cv::cvtColor(*frame, *frame, CV_BGR2RGB);
            buffer.FlagBack();

            wxCommandEvent* evt = new wxCommandEvent(NEW_FRAME_EVENT);
            wxQueueEvent(panel, evt);
            t = wxGetLocalTimeMillis();
            *((long*)((void*)(&time))) = t.GetLo();
            *((long*)((void*)(&time))+1) = t.GetHi();
        }


    }
    return NULL ;	// the thread is finished in a clean way
}
void VideoStream::ForceRead(){
    cv::Mat* frame = buffer.GetBack();
    stream >> *frame;
    cv::cvtColor(*frame, *frame, CV_BGR2RGB);
    buffer.FlagBack();
}
