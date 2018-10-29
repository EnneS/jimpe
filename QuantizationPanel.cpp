#include "QuantizationPanel.h"

QuantizationPanel::QuantizationPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(200, 500), wxSIMPLE_BORDER)
{
    m_title = new wxStaticText(this, wxID_ANY, "Quantization",  wxPoint(10,10), wxSize(200,60), wxALIGN_CENTER | wxST_NO_AUTORESIZE);
    validator.SetRange(1, 2048);
    PaletteSize = new wxTextCtrl(this, wxID_ANY, wxT("8"), wxPoint(16, 35), wxDefaultSize, 0, validator, wxT("Palette size"));
    m_cancelButton = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(104,70), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));

    GeneratePalette = new wxButton(this, wxID_OK, _("Generate Palette"), wxPoint(16,110), wxDefaultSize);
    GeneratePalette->Bind(wxEVT_BUTTON, &QuantizationPanel::sendMessage, this);
    m_cancelButton->Bind(wxEVT_BUTTON, &QuantizationPanel::sendCancelMessage, this);
}

QuantizationPanel::~QuantizationPanel()
{
    delete PaletteSize;
    delete GeneratePalette;
}

void QuantizationPanel::sendMessage(wxCommandEvent& event){
    wxCommandEvent outEvent(START_TASK_GEN_PALETTE) ;	// création d'un événement propre
    outEvent.SetInt(wxAtoi(PaletteSize->GetValue()));
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
}

void QuantizationPanel::sendCancelMessage(wxCommandEvent& event){
    wxCommandEvent outEvent(START_TASK_GEN_PALETTE) ;	// création d'un événement propre
    outEvent.SetInt(-1);
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
}

