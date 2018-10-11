#include "RotatePanel.h"

RotatePanel::RotatePanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(200, 500), wxSIMPLE_BORDER)
{
    wxString __wxRadioBoxChoices_1[3] =
  {
    wxT("90    "),
    wxT("180   "),
    wxT("-90   ")
  };
  RadioBox1 = new wxRadioBox(this, wxID_ANY, _("Rotation angle"), wxPoint(16,8), wxSize(175,90), 3, __wxRadioBoxChoices_1, 3, 0, wxDefaultValidator, _T("ID_RADIOBOX1"));
  Button1 = new wxButton(this, wxID_OK, _("OK"), wxPoint(16,110), wxDefaultSize);
  Button1->Bind(wxEVT_BUTTON, &RotatePanel::sendMessage, this);
}

RotatePanel::~RotatePanel()
{
    //dtor
}

void RotatePanel::sendMessage(wxCommandEvent& event){
    wxCommandEvent outEvent(DO_ROTATE) ;	// création d'un événement propre
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
}
