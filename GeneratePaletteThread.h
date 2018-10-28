#ifndef GENERATEPALETTETHREAD_H
#define GENERATEPALETTETHREAD_H
#include "KDTree.h"
#include <wx/wx.h>
#include "DoubleBuffer.h"

wxDECLARE_EVENT(END_TASK_GEN_PALETTE, wxCommandEvent);

class MyPanel;

class GeneratePaletteThread : public wxThread
{
    public:
        GeneratePaletteThread(MyPanel* p, DoubleBuffer& b, KDTree*& t, int nb_colors);
        virtual ~GeneratePaletteThread();

    protected:

    private:
        MyPanel* panel;
        cv::Mat img;
        KDTree*& tree;
        unsigned int max_colors;
        virtual wxThread::ExitCode Entry();
};
#include "MyPanel.h"
#endif // GENERATEPALETTETHREAD_H
