#ifndef CONTRASTEPANEL_H
#define CONTRASTEPANEL_H
#include <wx/wx.h>
wxDECLARE_EVENT(DO_CONTRASTE, wxCommandEvent);


class ContrastePanel : public wxPanel
{
    public:
        ContrastePanel(wxWindow* parent);
        virtual ~ContrastePanel();
        void sendMessage(wxCommandEvent& event);
        void sendCancelMessage(wxCommandEvent& event);
        wxSlider* m_contraste;
        wxSlider* m_brightness;
        wxButton* m_cancelButton;
        wxStaticText* m_title;
    protected:

    private:
};

#endif // HUEPANEL_H
