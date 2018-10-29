#ifndef HUEPANEL_H
#define HUEPANEL_H
#include <wx/wx.h>
wxDECLARE_EVENT(DO_HUE, wxCommandEvent);


class HuePanel : public wxPanel
{
    public:
        HuePanel(wxWindow* parent);
        virtual ~HuePanel();
        void sendMessage(wxCommandEvent& event);
        void sendCancelMessage(wxCommandEvent& event);
        wxSlider* m_hue;
        wxButton* m_cancelButton;
        wxStaticText* m_title;
    protected:

    private:
};

#endif // HUEPANEL_H
