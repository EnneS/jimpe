// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include "MyImage.h"
#include "MyFrame.h"
#endif

class MyApp: public wxApp
{
public:
	virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();
	MyFrame *frame = new MyFrame( wxT("Jimpe"), wxPoint(50, 50), wxSize(450, 340) );
	frame->Show(true);
	frame->Centre();
	return true;
}
