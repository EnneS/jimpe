#include "VideoStream.h"

VideoStream::VideoStream(MyPanel* p)
{
    m_panel = p;
}

VideoStream::~VideoStream()
{
    //dtor
}
void* VideoStream::Entry(){
    while(!TestDestroy())	// tant que le thread n'est pas détruit
    {
        m_panel->showStream();
    }
    return NULL ;	// the thread is finished in a clean way
}
