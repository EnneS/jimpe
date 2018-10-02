/***************************************************************
 * Name:      tp2Main.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2018-09-07
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef TP2MAIN_H
#define TP2MAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "tp2App.h"


#include <wx/button.h>
#include <wx/statline.h>
class tp2Dialog: public wxDialog
{
    public:
        tp2Dialog(wxDialog *dlg, const wxString& title);
        ~tp2Dialog();

    protected:
        enum
        {
            idBtnQuit = 1000,
            idBtnAbout
        };
        wxStaticText* m_staticText1;
        wxButton* BtnAbout;
        wxStaticLine* m_staticline1;
        wxButton* BtnQuit;

    private:
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};

#endif // TP2MAIN_H
