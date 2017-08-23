///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug 23 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __DIALOG_VIA_LAYERS_BASE_H__
#define __DIALOG_VIA_LAYERS_BASE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
class DIALOG_SHIM;
class PCB_LAYER_BOX_SELECTOR;

#include "dialog_shim.h"
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/font.h>
#include <wx/grid.h>
#include <wx/gdicmn.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/bmpcbox.h>
#include <wx/statline.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class DIALOG_VIA_LAYERS_BASE
///////////////////////////////////////////////////////////////////////////////
class DIALOG_VIA_LAYERS_BASE : public DIALOG_SHIM
{
	private:
	
	protected:
		wxGrid* m_gridViaStack;
		wxButton* m_buttonAddVia;
		wxButton* m_buttonRemoveVia;
		wxStaticText* m_staticText3;
		wxStaticText* m_staticText71;
		wxStaticText* m_staticText8;
		wxStaticText* m_staticTextViaName;
		PCB_LAYER_BOX_SELECTOR* m_ViaStartLayer;
		PCB_LAYER_BOX_SELECTOR* m_ViaEndLayer;
		wxStaticLine* m_staticline2;
		wxStdDialogButtonSizer* m_stdButtons;
		wxButton* m_stdButtonsOK;
		wxButton* m_stdButtonsCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void onCancelClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onOkClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		DIALOG_VIA_LAYERS_BASE( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Via layer config"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 667,334 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~DIALOG_VIA_LAYERS_BASE();
	
};

#endif //__DIALOG_VIA_LAYERS_BASE_H__
