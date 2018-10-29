#include "BlurPanel.h"

BlurPanel::BlurPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(200, 500), wxSIMPLE_BORDER)
{
    m_title = new wxStaticText(this, wxID_ANY, "Flou",  wxPoint(10,10), wxSize(200,60), wxALIGN_CENTER | wxST_NO_AUTORESIZE);
    m_blur = new wxSlider( this, wxID_ANY, 7, 1, 15, wxPoint(20,20), wxSize(165,60), wxSL_HORIZONTAL|wxSL_LABELS );
    m_cancelButton = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(104,90), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));

    m_blur->Bind(wxEVT_SCROLL_THUMBTRACK, &BlurPanel::sendMessage, this);
    m_cancelButton->Bind(wxEVT_BUTTON, &BlurPanel::sendCancelMessage, this);
}

BlurPanel::~BlurPanel()
{
    delete m_title;
}

void BlurPanel::sendMessage(wxCommandEvent& event){
    wxCommandEvent outEvent(DO_BLUR) ;	// création d'un événement propre
    outEvent.SetInt(m_blur->GetValue());
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
}

void BlurPanel::sendCancelMessage(wxCommandEvent& event){
    wxCommandEvent outEvent(DO_BLUR) ;	// création d'un événement propre
    outEvent.SetInt(-1);
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
}
