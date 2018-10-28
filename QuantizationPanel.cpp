#include "QuantizationPanel.h"

QuantizationPanel::QuantizationPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(200, 500), wxSIMPLE_BORDER)
{
    validator.SetRange(1, 2048);
    PaletteSize = new wxTextCtrl(this, wxID_ANY, wxT("8"), wxPoint(16, 8), wxDefaultSize, 0, validator, wxT("Palette size"));


    GeneratePalette = new wxButton(this, wxID_OK, _("Generate Palette"), wxPoint(16,110), wxDefaultSize);
    GeneratePalette->Bind(wxEVT_BUTTON, &QuantizationPanel::sendMessage, this);
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
