#ifndef ROTATEPANEL_H
#define ROTATEPANEL_H

#include <wx/wx.h>

wxDECLARE_EVENT(DO_ROTATE, wxCommandEvent);

class RotatePanel : public wxPanel
{
    public:
        RotatePanel(wxWindow* parent);
        virtual ~RotatePanel();
        void sendMessage(wxCommandEvent& event);
        wxButton* Button1;
        wxRadioBox* RadioBox1;
    protected:

    private:

};



#endif // ROTATEPANEL_H
