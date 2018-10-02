#include "MyPosterizeDialog.h"

MyPosterizeDialog::MyPosterizeDialog(wxWindow* parent, wxWindowID id, const wxString& title,
                                     const wxPoint& pos, const wxSize& size, long style)
                    : wxDialog(parent, id, title, pos, size, style)
{
	m_posterize = new wxSlider( this, wxID_ANY, 1, 1, 7, wxPoint(20,10), wxSize(165,60), wxSL_HORIZONTAL|wxSL_LABELS );
	m_okButton = new wxButton( this, wxID_OK, wxT("OK"), wxPoint(16,70), wxDefaultSize, 0 );
    m_cancelButton = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(104,70), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
}

MyPosterizeDialog::~MyPosterizeDialog()
{
    //dtor
}
