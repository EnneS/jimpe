#include "GeneratePaletteThread.h"

GeneratePaletteThread::GeneratePaletteThread(MyPanel* p, DoubleBuffer& b, KDTree*& t) : panel(p), tree(t)
{
    img = *b.GetFront();
    max_colors = 8;
}

GeneratePaletteThread::~GeneratePaletteThread()
{

}
wxThread::ExitCode GeneratePaletteThread::Entry(){
    KDTree* tmp = new KDTree(img);
    for(unsigned int i = 0; i < max_colors-1; i++){
        if(TestDestroy()){
            delete tmp;
            return (wxThread::ExitCode)0;
        }

        tmp->addColor();
    }
    tree = tmp;
    wxCommandEvent* evt = new wxCommandEvent(END_TASK_GEN_PALETTE);
    wxQueueEvent(panel, evt);
    return (wxThread::ExitCode)0 ;	// the thread is finished in a clean way
}
