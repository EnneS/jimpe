#ifndef QUANTIZATIONPANEL_H
#define QUANTIZATIONPANEL_H

#include <wx/wx.h>

wxDECLARE_EVENT(START_TASK_GEN_PALETTE, wxCommandEvent);

class QuantizationPanel : public wxPanel
{
    public:
        QuantizationPanel(wxWindow* parent);
        virtual ~QuantizationPanel();
        void sendMessage(wxCommandEvent& event);
        wxButton* GeneratePalette;
        //wxSpinCtrl* PaletteSize;
    protected:

    private:
};

#endif // QUANTIZATIONPANEL_H
