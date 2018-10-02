#include "WebcamStream.h"

WebcamStream::WebcamStream(int device) : stream(device)
{
}

WebcamStream::~WebcamStream()
{
    //dtor
}

cv::VideoCapture WebcamStream::getStream(){
    return stream;
}

cv::Mat* WebcamStream::getFrame(cv::Mat* frame){
    getStream().read(*frame);
    return frame;
}
