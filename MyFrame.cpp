#include "MyFrame.h"

wxDEFINE_EVENT(DO_ROTATE, wxCommandEvent);

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
    m_panel = new MyPanel(this);
    m_panel->SetBackgroundColour(wxColour(wxT("RED")));
    /*
    * TOOLBAR
    */

    m_toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_VERTICAL);

    // Images des tools
    wxBitmap negativeIcon(wxT("negative.png"), wxBITMAP_TYPE_PNG);
    wxBitmap mirrorHIcon(wxT("mirroirh.png"), wxBITMAP_TYPE_PNG);
    wxBitmap mirrorVIcon(wxT("mirrorv.png"), wxBITMAP_TYPE_PNG);
    wxBitmap rotateIcon(wxT("rotate.png"), wxBITMAP_TYPE_PNG);

    // Ajout des tools à la toolbar
    m_toolbar->AddTool(ID_Negative, wxT("Negatif"), negativeIcon);
    m_toolbar->AddTool(ID_MiroirH, wxT("Miroir Vertical"), mirrorHIcon);
    m_toolbar->AddTool(ID_MiroirV, wxT("Miroir Horizontal"), mirrorVIcon);
    m_toolbar->AddTool(ID_Rotate, wxT("Rotation"), rotateIcon);

    // Activation de la toolbar
    m_toolbar->Realize();
    SetToolBar(m_toolbar);

    /*
    * MENUBAR
    */

	wxMenu *menuFile = new wxMenu ;

    menuFile->Append(wxID_ABOUT) ;
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT) ;

	menuFile->Append(wxID_EXIT) ;
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT) ;

    wxMenu *menuProcess = new wxMenu ;
	menuProcess->Append(ID_MiroirH, wxT("Miroir horizontal \tCtrl-H"), _("Applique un effet mirroir horizontal")) ;
	Bind(wxEVT_MENU, &MyFrame::OnProcess, this, ID_MiroirH) ;
    menuProcess->Append(ID_MiroirV, wxT("Miroir vertical \tCtrl-V"), _("Applique un effet mirroir vertical")) ;
	Bind(wxEVT_MENU, &MyFrame::OnProcess, this, ID_MiroirV) ;
	menuProcess->Append(ID_Blur, wxT("Flou \tCtrl-F"), _("Applique un effet de flou")) ;
	Bind(wxEVT_MENU, &MyFrame::OnProcess, this, ID_Blur);
    menuProcess->Append(ID_Rotate, wxT("Rotation \tCtrl-R"), _("Applique une rotation a l'image")) ;
	Bind(wxEVT_MENU, &MyFrame::OnProcess, this, ID_Rotate);
    menuProcess->Append(ID_Negative, wxT("Negatif \tCtrl-N"), _("Negativer l\'image")) ;
	Bind(wxEVT_MENU, &MyFrame::OnProcess, this, ID_Negative);
    menuProcess->Append(ID_Threshold, wxT("Seuillage \tCtrl-T"), _("Applique un seuillage a l\'image")) ;
	Bind(wxEVT_MENU, &MyFrame::OnProcess, this, ID_Threshold);
    menuProcess->Append(ID_Posterize, wxT("Postérisation \tCtrl-P"), _("Applique une posterisation a l\'image")) ;
	Bind(wxEVT_MENU, &MyFrame::OnProcess, this, ID_Posterize);

    //Connect( wxID_ANY, wxEVT_IDLE, wxIdleEventHandler(MyFrame::OnIdle) );

	wxMenuBar *menuBar = new wxMenuBar ;
	menuBar->Append( menuFile, wxT("File" )) ;
    menuBar->Append( menuProcess, wxT("Process" )) ;
	SetMenuBar(menuBar) ;

	CreateStatusBar();
    SetStatusText(wxT("Mon visualiseur d'image"));
}

void MyFrame::OnOpen(wxCommandEvent& event)
{
    //m_panel->openImage(wxT(""));
}

void MyFrame::OnExit(wxCommandEvent& event)
{
	Close( true );
}

void MyFrame::OnSave(wxCommandEvent& event)
{
	wxString fileName;
	wxString str;
	fileName = wxSaveFileSelector(wxT("Sauvegarder"), wxT(""), str);
	if(fileName != "") {
        m_panel->saveImage(fileName);
	}
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
	wxLogMessage(wxT("Auteur : moi !!!"));
}

void MyFrame::OnProcess(wxCommandEvent& event)
{
    switch(event.GetId()){
        case ID_MiroirH :
            m_panel->Miroir(true);
            break;
        case ID_MiroirV : m_panel->Miroir(false); break;
        case ID_Blur : m_panel->Blur(); break;
        case ID_Rotate : {
                m_process_panel = new RotatePanel(this);
                m_panel->SetPosition(wxPoint(m_process_panel->GetSize().GetWidth(),0));
                Bind(DO_ROTATE, &MyFrame::OnRotate, this) ;
                Fit();
            break;
        }
        case ID_Negative : m_panel->Negative(); break;
        case ID_Threshold : m_panel->Threshold(); break;
        case ID_Posterize : m_panel->Posterize(); break;
    }
}

void MyFrame::OnRotate(wxCommandEvent& event){
    m_panel->Rotate(1);
}
