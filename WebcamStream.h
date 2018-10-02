#ifndef WEBCAMSTREAM_H
#define WEBCAMSTREAM_H

#include "opencv2/opencv.hpp"

class WebcamStream
{
    public:
        WebcamStream(int device);
        virtual ~WebcamStream();
        cv::Mat* getFrame(cv::Mat* frame);
        cv::VideoCapture getStream();
    protected:

    private:
        cv::VideoCapture stream;
};

#endif // WEBCAMSTREAM_H
