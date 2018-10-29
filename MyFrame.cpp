#include "MyFrame.h"

wxDEFINE_EVENT(DO_ROTATE, wxCommandEvent);
wxDEFINE_EVENT(DO_THRESHOLD, wxCommandEvent);
wxDEFINE_EVENT(DO_BLUR, wxCommandEvent);
wxDEFINE_EVENT(DO_POSTERIZE, wxCommandEvent);
wxDEFINE_EVENT(START_TASK_GEN_PALETTE, wxCommandEvent);

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
    m_panel = new MyPanel(this);
    m_panel->debug(1);
    m_panel->SetBackgroundColour(wxColour(wxT("RED")));
    m_panel->debug(2);
    /*
    * TOOLBAR
    */

    m_toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_VERTICAL);

    // Images des tools
    wxBitmap negativeIcon(wxT("negative.png"), wxBITMAP_TYPE_PNG);
    wxBitmap invertHIcon(wxT("invert.png"), wxBITMAP_TYPE_PNG);
    wxBitmap invertVIcon(wxT("invertV.png"), wxBITMAP_TYPE_PNG);
    wxBitmap rotateIcon(wxT("rotate.png"), wxBITMAP_TYPE_PNG);

    wxBitmap contourIcon(wxT("contour.png"), wxBITMAP_TYPE_PNG);
    wxBitmap blurIcon(wxT("blur.png"), wxBITMAP_TYPE_PNG);
    wxBitmap contrasteIcon(wxT("contraste.png"), wxBITMAP_TYPE_PNG);
    wxBitmap gammaIcon(wxT("gamma.png"), wxBITMAP_TYPE_PNG);
    wxBitmap hueIcon(wxT("hue.png"), wxBITMAP_TYPE_PNG);
    wxBitmap posterisationIcon(wxT("posterisation.png"), wxBITMAP_TYPE_PNG);
    wxBitmap quantizationIcon(wxT("quantization.png"), wxBITMAP_TYPE_PNG);
    wxBitmap saturationIcon(wxT("saturation.png"), wxBITMAP_TYPE_PNG);

    // Ajout des tools à la toolbar
    m_toolbar->AddTool(ID_Negative, wxT("Negatif"), negativeIcon);
    m_toolbar->AddTool(ID_MiroirH, wxT("Miroir Vertical"), invertHIcon);
    m_toolbar->AddTool(ID_MiroirV, wxT("Miroir Horizontal"), invertVIcon);
    m_toolbar->AddTool(ID_Rotate, wxT("Rotation"), rotateIcon);

    m_toolbar->AddTool(ID_BorderDetect, wxT("Détection des contours"), contourIcon);
    m_toolbar->AddTool(ID_Blur, wxT("Flou"), blurIcon);
    m_toolbar->AddTool(ID_BrightnessContrast, wxT("Contraste"), contrasteIcon);
    m_toolbar->AddTool(ID_Gamma, wxT("Gamma"), gammaIcon);
    m_toolbar->AddTool(ID_Hue, wxT("Hue"), hueIcon);
    m_toolbar->AddTool(ID_Saturation, wxT("Saturation"), saturationIcon);
    m_toolbar->AddTool(ID_Posterize, wxT("Posterize"), posterisationIcon);
    m_toolbar->AddTool(ID_Quantization, wxT("Quantization"), quantizationIcon);

    // Activation de la toolbar
    m_toolbar->SetToolBitmapSize(wxSize(32,32));
    m_toolbar->Realize();
    SetToolBar(m_toolbar);

    /*
    * MENUBAR
    */
    m_panel->debug(3);
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
	menuProcess->Append(ID_BorderDetect, wxT("Détéction de bords \tCtrl-D"), _("Applique une détéction de bords a l\'image")) ;
	Bind(wxEVT_MENU, &MyFrame::OnProcess, this, ID_BorderDetect);
    menuProcess->Append(ID_Quantization, wxT("Quantization \tCtrl-Q"), _("Applique une quantization a l\'image")) ;
	Bind(wxEVT_MENU, &MyFrame::OnProcess, this, ID_Quantization);

    m_panel->debug(4);

	wxMenuBar *menuBar = new wxMenuBar ;
	menuBar->Append( menuFile, wxT("File" )) ;
    menuBar->Append( menuProcess, wxT("Process" )) ;
	SetMenuBar(menuBar) ;

	CreateStatusBar();
    SetStatusText(wxT("Mon visualiseur d'image"));
    m_panel->debug(5);
    SetClientSize(m_panel->GetSize());
    m_panel->debug(6);
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

        case ID_Blur :
            if(m_process_panel){
                delete m_process_panel;
                m_process_panel = nullptr;
            }

            if(currentProcessPanel != ID_Blur){
                currentProcessPanel = ID_Blur;
                m_process_panel = new BlurPanel(this);
                m_panel->SetPosition(wxPoint(m_process_panel->GetSize().GetWidth(),0));
                Bind(DO_BLUR, &MyFrame::OnBlur, this);
                SetClientSize(m_process_panel->GetSize().GetWidth() + m_panel->GetSize().GetWidth(), std::max(m_process_panel->GetSize().GetHeight(), m_panel->GetSize().GetHeight()));
            } else {
                currentProcessPanel = -1;
                m_panel->SetPosition(wxPoint(0,0));
            }
            break;

        case ID_Rotate:
            if(m_process_panel){
                delete m_process_panel;
                m_process_panel = nullptr;
            }

            if(currentProcessPanel != ID_Rotate){
                currentProcessPanel = ID_Rotate;
                m_process_panel = new RotatePanel(this);
                m_panel->SetPosition(wxPoint(m_process_panel->GetSize().GetWidth(),0));
                Bind(DO_ROTATE, &MyFrame::OnRotate, this);
                SetClientSize(m_process_panel->GetSize().GetWidth() + m_panel->GetSize().GetWidth(), std::max(m_process_panel->GetSize().GetHeight(), m_panel->GetSize().GetHeight()));
            } else {
                currentProcessPanel = -1;
                m_panel->SetPosition(wxPoint(0,0));
            }
            break;

        case ID_Negative : m_panel->Negative(); break;

        case ID_Threshold :
            if(m_process_panel){
                delete m_process_panel;
                m_process_panel = nullptr;
            }
            if(currentProcessPanel != ID_Threshold){
                currentProcessPanel = ID_Threshold;
                m_process_panel = new ThresholdPanel(this);
                m_panel->SetPosition(wxPoint(m_process_panel->GetSize().GetWidth(),0));
                Bind(DO_THRESHOLD, &MyFrame::OnThreshold, this);
                SetClientSize(m_process_panel->GetSize().GetWidth() + m_panel->GetSize().GetWidth(), std::max(m_process_panel->GetSize().GetHeight(), m_panel->GetSize().GetHeight()));
            } else {
                currentProcessPanel = -1;
                m_panel->SetPosition(wxPoint(0,0));
            }
            break;

        case ID_Posterize :
            if(m_process_panel){
                delete m_process_panel;
                m_process_panel = nullptr;
            }
            if(currentProcessPanel != ID_Posterize){
                currentProcessPanel = ID_Posterize;
                m_process_panel = new PosterizePanel(this);
                m_panel->SetPosition(wxPoint(m_process_panel->GetSize().GetWidth(),0));
                Bind(DO_POSTERIZE, &MyFrame::OnPosterize, this);
                SetClientSize(m_process_panel->GetSize().GetWidth() + m_panel->GetSize().GetWidth(), std::max(m_process_panel->GetSize().GetHeight(), m_panel->GetSize().GetHeight()));
            } else {
                currentProcessPanel = -1;
                m_panel->SetPosition(wxPoint(0,0));
            }

            break;

        case ID_BorderDetect : m_panel->BorderDetect(); break;

        case ID_Quantization:
            if(m_process_panel){
                delete m_process_panel;
                m_process_panel = nullptr;
            }
            if(currentProcessPanel != ID_Quantization){
                currentProcessPanel = ID_Quantization;
                m_process_panel = new QuantizationPanel(this);
                m_panel->SetPosition(wxPoint(m_process_panel->GetSize().GetWidth(),0));
                Bind(START_TASK_GEN_PALETTE, &MyFrame::OnGeneratePalette, this);
                SetClientSize(m_process_panel->GetSize().GetWidth() + m_panel->GetSize().GetWidth(), std::max(m_process_panel->GetSize().GetHeight(), m_panel->GetSize().GetHeight()));
            } else {
                currentProcessPanel = -1;
                m_panel->SetPosition(wxPoint(0,0));
            }

            break;
    }

}

void MyFrame::OnRotate(wxCommandEvent& event){
    m_panel->Rotate(event.GetInt());
    if(event.GetInt()!= 2)
        SetClientSize(m_process_panel->GetSize().GetWidth() + std::max(m_process_panel->GetSize().GetHeight(), m_panel->GetSize().GetHeight()), m_panel->GetSize().GetWidth());
}

void MyFrame::OnGeneratePalette(wxCommandEvent& event){
    m_panel->generatePalette(event.GetInt());
}

void MyFrame::OnThreshold(wxCommandEvent& event){
    m_panel->Threshold(event.GetInt());
}

void MyFrame::OnBlur(wxCommandEvent& event){
    m_panel->Blur(event.GetInt());
}

void MyFrame::OnPosterize(wxCommandEvent& event){
    m_panel->Posterize(event.GetInt());
}

