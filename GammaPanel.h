#ifndef GAMMAPANEL_H
#define GAMMAPANEL_H
#include <wx/wx.h>
wxDECLARE_EVENT(DO_GAMMA, wxCommandEvent);


class GammaPanel : public wxPanel
{
    public:
        GammaPanel(wxWindow* parent);
        virtual ~GammaPanel();
        void sendMessage(wxCommandEvent& event);
        void sendCancelMessage(wxCommandEvent& event);
        wxSlider* m_gamma;
        wxButton* m_cancelButton;
    protected:

    private:
};

#endif // GAMMAPANEL_H
