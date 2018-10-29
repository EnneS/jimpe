#include "SaturationPanel.h"

SaturationPanel::SaturationPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(200, 500), wxSIMPLE_BORDER)
{
    m_saturation = new wxSlider( this, wxID_ANY, 0, -255, 255, wxPoint(20,10), wxSize(165,60), wxSL_HORIZONTAL|wxSL_LABELS );
    m_cancelButton = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(104,70), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));

    m_saturation->Bind(wxEVT_SCROLL_THUMBTRACK, &SaturationPanel::sendMessage, this);
    m_cancelButton->Bind(wxEVT_BUTTON, &SaturationPanel::sendCancelMessage, this);
}

SaturationPanel::~SaturationPanel()
{
}

void SaturationPanel::sendMessage(wxCommandEvent& event){
    wxCommandEvent outEvent(DO_SATURATION) ;	// création d'un événement propre
    outEvent.SetInt(m_saturation->GetValue());
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
}

void SaturationPanel::sendCancelMessage(wxCommandEvent& event){
    wxCommandEvent outEvent(DO_SATURATION) ;	// création d'un événement propre
    outEvent.SetInt(-256);
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
}
