#include "DoubleBuffer.h"

DoubleBuffer::DoubleBuffer() : condition_back(mutex_back), condition_front(mutex_front)
{
    current = 0;
    state = 0;
    frames[0] = cv::Mat(800, 600, CV_8UC3);
    frames[1] = cv::Mat(800, 600, CV_8UC3);
}

DoubleBuffer::~DoubleBuffer()
{

}
cv::Mat* DoubleBuffer::GetBack(){
    mutex_back.Lock();

    while(state & 1)
        condition_back.Wait();

    mutex_back.Unlock();
    return &frames[current];
}
cv::Mat* DoubleBuffer::GetFront(){
    mutex_front.Lock();

    while(state & 2)
        condition_front.Wait();

    mutex_front.Unlock();

    return &frames[1-current];
}

void DoubleBuffer::FlagBack(){
    mutex_back.Lock();
    state |= 1;
    Swap();

    mutex_back.Unlock();

}

void DoubleBuffer::FlagFront(){
    mutex_front.Lock();
    state |= 2;
    Swap();

    mutex_front.Unlock();
}

void DoubleBuffer::Swap(){

    if(state == 3){
        current = 1 - current;
        state = 0;
        condition_back.Signal();
        condition_front.Signal();
    }

}
