#include "GammaPanel.h"

GammaPanel::GammaPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(200, 500), wxSIMPLE_BORDER)
{
    m_title = new wxStaticText(this, wxID_ANY, "Gamma",  wxPoint(10,10), wxSize(200,60), wxALIGN_CENTER | wxST_NO_AUTORESIZE);
    m_gamma = new wxSlider( this, wxID_ANY, 175, 50, 300, wxPoint(20,20), wxSize(165,60), wxSL_HORIZONTAL|wxSL_LABELS );
    m_cancelButton = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(104,90), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));

    m_gamma->Bind(wxEVT_SCROLL_THUMBTRACK, &GammaPanel::sendMessage, this);
    m_cancelButton->Bind(wxEVT_BUTTON, &GammaPanel::sendCancelMessage, this);
}

GammaPanel::~GammaPanel()
{
}

void GammaPanel::sendMessage(wxCommandEvent& event){
    wxCommandEvent outEvent(DO_GAMMA) ;	// création d'un événement propre
    outEvent.SetInt(m_gamma->GetValue());
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
}

void GammaPanel::sendCancelMessage(wxCommandEvent& event){
    wxCommandEvent outEvent(DO_GAMMA) ;	// création d'un événement propre
    outEvent.SetInt(-1);
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
}
