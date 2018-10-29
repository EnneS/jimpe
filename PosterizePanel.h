#ifndef POSTERIZEPANEL_H
#define POSTERIZEPANEL_H
#include <wx/wx.h>
wxDECLARE_EVENT(DO_POSTERIZE, wxCommandEvent);


class PosterizePanel : public wxPanel
{
    public:
        PosterizePanel(wxWindow* parent);
        virtual ~PosterizePanel();
        void sendMessage(wxCommandEvent& event);
        void sendCancelMessage(wxCommandEvent& event);
        wxSlider* m_posterize;
        wxButton* m_cancelButton;
        wxStaticText* m_title;

    protected:

    private:
};

#endif // POSTERIZEPANEL_H
