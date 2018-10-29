#include "HuePanel.h"

HuePanel::HuePanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(200, 500), wxSIMPLE_BORDER)
{
    m_title = new wxStaticText(this, wxID_ANY, "Hue",  wxPoint(10,10), wxSize(200,60), wxALIGN_CENTER | wxST_NO_AUTORESIZE);
    m_hue = new wxSlider( this, wxID_ANY, 0, 0, 180, wxPoint(20,20), wxSize(165,60), wxSL_HORIZONTAL|wxSL_LABELS );
    m_cancelButton = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(104,90), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));

    m_hue->Bind(wxEVT_SCROLL_THUMBTRACK, &HuePanel::sendMessage, this);
    m_cancelButton->Bind(wxEVT_BUTTON, &HuePanel::sendCancelMessage, this);
}

HuePanel::~HuePanel()
{
}

void HuePanel::sendMessage(wxCommandEvent& event){
    wxCommandEvent outEvent(DO_HUE) ;	// création d'un événement propre
    outEvent.SetInt(m_hue->GetValue());
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
}

void HuePanel::sendCancelMessage(wxCommandEvent& event){
    wxCommandEvent outEvent(DO_HUE) ;	// création d'un événement propre
    outEvent.SetInt(-1);
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
}
