#ifndef BLURPANEL_H
#define BLURPANEL_H
#include <wx/wx.h>
wxDECLARE_EVENT(DO_BLUR, wxCommandEvent);


class BlurPanel : public wxPanel
{
    public:
        BlurPanel(wxWindow* parent);
        virtual ~BlurPanel();
        void sendMessage(wxCommandEvent& event);
        void sendCancelMessage(wxCommandEvent& event);
        wxSlider* m_blur;
        wxButton* m_cancelButton;
        wxStaticText* m_title;
    protected:

    private:
};

#endif // BLURPANEL_H
