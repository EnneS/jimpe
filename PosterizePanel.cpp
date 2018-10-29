#include "PosterizePanel.h"

PosterizePanel::PosterizePanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(200, 500), wxSIMPLE_BORDER)
{
    m_posterize = new wxSlider( this, wxID_ANY, 3, 1, 5, wxPoint(20,10), wxSize(165,60), wxSL_HORIZONTAL|wxSL_LABELS );
    m_cancelButton = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(104,70), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));

    m_posterize->Bind(wxEVT_SCROLL_THUMBTRACK, &PosterizePanel::sendMessage, this);
    m_cancelButton->Bind(wxEVT_BUTTON, &PosterizePanel::sendCancelMessage, this);
}

PosterizePanel::~PosterizePanel()
{
}

void PosterizePanel::sendMessage(wxCommandEvent& event){
    wxCommandEvent outEvent(DO_POSTERIZE) ;	// création d'un événement propre
    outEvent.SetInt(m_posterize->GetValue());
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
}

void PosterizePanel::sendCancelMessage(wxCommandEvent& event){
    wxCommandEvent outEvent(DO_POSTERIZE) ;	// création d'un événement propre
    outEvent.SetInt(-1);
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
}
