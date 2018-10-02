#ifndef MYPOSTERIZEDIALOG_H
#define MYPOSTERIZEDIALOG_H

#include <wx/wx.h>

class MyPosterizeDialog : public wxDialog
{
    public:
        MyPosterizeDialog(wxWindow* parent, wxWindowID id = wxID_ANY,const wxString& title = wxEmptyString,
                          const wxPoint& pos = wxDefaultPosition,
                          const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		virtual ~MyPosterizeDialog();

        wxSlider* m_posterize;
    protected:
        wxButton* m_okButton;
        wxButton* m_cancelButton;
    private:
};

#endif // MYPOSTERIZEDIALOG_H
