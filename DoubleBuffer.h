#ifndef DOUBLEBUFFER_H
#define DOUBLEBUFFER_H
#include <wx/wx.h>
#include <opencv2/opencv.hpp>

class DoubleBuffer
{
    public:
        DoubleBuffer();
        virtual ~DoubleBuffer();
        cv::Mat* GetBack();
        cv::Mat* GetFront();

        void FlagFront();
        void FlagBack();
    private:
        void Swap();
        unsigned int current;
        unsigned int state;
        cv::Mat frames[2];
        wxMutex mutex_back;
        wxMutex mutex_front;
        wxCondition condition_back;
        wxCondition condition_front;

};

#endif // DOUBLEBUFFER_H
