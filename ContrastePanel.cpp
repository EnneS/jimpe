#include "ContrastePanel.h"

ContrastePanel::ContrastePanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(200, 500), wxSIMPLE_BORDER)
{
    m_title = new wxStaticText(this, wxID_ANY, "Contraste et Luminosite",  wxPoint(10,10), wxSize(200,60), wxALIGN_CENTER | wxST_NO_AUTORESIZE);
    m_contraste = new wxSlider( this, wxID_ANY, 100, 0, 200, wxPoint(20,20), wxSize(165,60), wxSL_HORIZONTAL|wxSL_LABELS );
    m_brightness = new wxSlider( this, wxID_ANY, 0, -255, 255, wxPoint(20,70), wxSize(165,60), wxSL_HORIZONTAL|wxSL_LABELS );
    m_cancelButton = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(104,140), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));

    m_brightness->Bind(wxEVT_SCROLL_THUMBTRACK, &ContrastePanel::sendMessage, this);
    m_contraste->Bind(wxEVT_SCROLL_THUMBTRACK, &ContrastePanel::sendMessage, this);
    m_cancelButton->Bind(wxEVT_BUTTON, &ContrastePanel::sendCancelMessage, this);
}

ContrastePanel::~ContrastePanel()
{
    delete m_title;
}

void ContrastePanel::sendMessage(wxCommandEvent& event){
    wxCommandEvent outEvent(DO_CONTRASTE) ;	// création d'un événement propre
    outEvent.SetInt(m_brightness->GetValue());
    outEvent.SetString(wxString::Format(wxT("%i"), m_contraste->GetValue()));
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
}

void ContrastePanel::sendCancelMessage(wxCommandEvent& event){
    wxCommandEvent outEvent(DO_CONTRASTE) ;	// création d'un événement propre
    outEvent.SetInt(-1);
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
}
