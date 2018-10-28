#include "QuantizationPanel.h"

QuantizationPanel::QuantizationPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(200, 500), wxSIMPLE_BORDER)
{
    //PaletteSize = new wxSpinCtrl(this, wxID_ANY, wxT("8"), wxPoint(16, 8));
    //PaletteSize.SetRange(1, 512);
    GeneratePalette = new wxButton(this, wxID_OK, _("Generate Palette"), wxPoint(16,110), wxDefaultSize);
    GeneratePalette->Bind(wxEVT_BUTTON, &QuantizationPanel::sendMessage, this);
}

QuantizationPanel::~QuantizationPanel()
{
    //dtor
}

void QuantizationPanel::sendMessage(wxCommandEvent& event){
    wxCommandEvent outEvent(START_TASK_GEN_PALETTE) ;	// création d'un événement propre
    //outEvent.SetInt(PaletteSize->GetValue());
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
}
