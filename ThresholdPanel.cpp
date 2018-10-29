#include "ThresholdPanel.h"

ThresholdPanel::ThresholdPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(200, 500), wxSIMPLE_BORDER)
{
    m_title = new wxStaticText(this, wxID_ANY, "Seuillage",  wxPoint(10,10), wxSize(200,60), wxALIGN_CENTER | wxST_NO_AUTORESIZE);
    m_threshold = new wxSlider( this, wxID_ANY, 128, 0, 255, wxPoint(20,20), wxSize(165,60), wxSL_HORIZONTAL|wxSL_LABELS );
    m_cancelButton = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(104,90), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));

    m_threshold->Bind(wxEVT_SCROLL_THUMBTRACK, &ThresholdPanel::sendMessage, this);
    m_cancelButton->Bind(wxEVT_BUTTON, &ThresholdPanel::sendCancelMessage, this);
}

ThresholdPanel::~ThresholdPanel()
{
}

void ThresholdPanel::sendMessage(wxCommandEvent& event){
    wxCommandEvent outEvent(DO_THRESHOLD) ;	// création d'un événement propre
    outEvent.SetInt(m_threshold->GetValue());
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
}

void ThresholdPanel::sendCancelMessage(wxCommandEvent& event){
    wxCommandEvent outEvent(DO_THRESHOLD) ;	// création d'un événement propre
    outEvent.SetInt(-1);
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
}
