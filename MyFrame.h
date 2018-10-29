#ifndef MYFRAME_H
#define MYFRAME_H
#include <wx/wx.h>
#include "MyPanel.h"
#include "RotatePanel.h"
#include "BlurPanel.h"
#include "ThresholdPanel.h"
#include "PosterizePanel.h"
#include "SaturationPanel.h"
#include "QuantizationPanel.h"
#include "GammaPanel.h"
#include "HuePanel.h"

class MyFrame: public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void OnProcess(wxCommandEvent& event);
private:
    void OnSave(wxCommandEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnRotate(wxCommandEvent& event);
    void OnBlur(wxCommandEvent& event);
    void OnPosterize(wxCommandEvent& event);
    void OnSaturation(wxCommandEvent& event);
    void OnThreshold(wxCommandEvent& event);
    void OnGamma(wxCommandEvent& event);
    void OnHue(wxCommandEvent& event);
    void OnGeneratePalette(wxCommandEvent& event);
    wxPanel *m_process_panel;
    MyPanel *m_panel; // the panel inside the main frame
    wxToolBar *m_toolbar;
    int currentProcessPanel;
};

enum{
    ID_Record = 1001,
    ID_Stop

};

#endif // MYFRAME_H
