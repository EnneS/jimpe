#ifndef THRESHOLDPANEL_H
#define THRESHOLDPANEL_H
#include <wx/wx.h>
wxDECLARE_EVENT(DO_THRESHOLD, wxCommandEvent);


class ThresholdPanel : public wxPanel
{
    public:
        ThresholdPanel(wxWindow* parent);
        virtual ~ThresholdPanel();
        void sendMessage(wxCommandEvent& event);
        void sendCancelMessage(wxCommandEvent& event);
        wxSlider* m_threshold;
        wxButton* m_cancelButton;
    protected:

    private:
};

#endif // THRESHOLDPANEL_H
