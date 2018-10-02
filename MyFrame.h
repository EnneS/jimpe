#ifndef MYFRAME_H
#define MYFRAME_H
#include "MyPanel.h"
#include <wx/wx.h>

class MyFrame: public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    void OnSave(wxCommandEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnProcess(wxCommandEvent& event);

    MyPanel *m_panel; // the panel inside the main frame
};

enum	// énumération. Elle gère la numérotation automatiquement
{
	ID_Open = 1,
	ID_Save = 2,
	ID_MiroirH,
	ID_MiroirV,
	ID_Blur,
	ID_Rotate,
	ID_Negative,
	ID_Threshold,
	ID_Posterize
};
#endif // MYFRAME_H
