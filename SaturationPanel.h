#ifndef SATURATIONPANEL_H
#define SATURATIONPANEL_H
#include <wx/wx.h>
wxDECLARE_EVENT(DO_SATURATION, wxCommandEvent);


class SaturationPanel : public wxPanel
{
    public:
        SaturationPanel(wxWindow* parent);
        virtual ~SaturationPanel();
        void sendMessage(wxCommandEvent& event);
        void sendCancelMessage(wxCommandEvent& event);
        wxSlider* m_saturation;
        wxButton* m_cancelButton;
    protected:

    private:
};

#endif // SATURATIONPANEL_H
