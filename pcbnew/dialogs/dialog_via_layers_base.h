///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 16 2016)
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
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/bmpcbox.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class DIALOG_VIA_LAYERS_BASE
///////////////////////////////////////////////////////////////////////////////
class DIALOG_VIA_LAYERS_BASE : public DIALOG_SHIM
{
	private:
	
	protected:
		wxStaticText* m_staticText3;
		wxStaticText* m_staticText71;
		wxStaticText* m_staticText8;
		wxStaticText* m_staticText9;
		PCB_LAYER_BOX_SELECTOR* m_ViaStartLayer;
		PCB_LAYER_BOX_SELECTOR* m_ViaEndLayer;
		wxStaticText* m_staticText5;
		PCB_LAYER_BOX_SELECTOR* m_BlindBurriedViaStartLayer;
		PCB_LAYER_BOX_SELECTOR* m_BlindBurriedViaEndLayer;
		wxStaticText* m_staticText7;
		PCB_LAYER_BOX_SELECTOR* m_MicroViaTopStartLayer;
		PCB_LAYER_BOX_SELECTOR* m_MicroViaTopEndLayer;
		wxStaticText* m_staticText10;
		PCB_LAYER_BOX_SELECTOR* m_MicroViaBottomStartLayer;
		PCB_LAYER_BOX_SELECTOR* m_MicroViaBottomEndLayer;
		wxStaticLine* m_staticline1;
		wxStdDialogButtonSizer* m_stdButtons;
		wxButton* m_stdButtonsOK;
		wxButton* m_stdButtonsCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void onCancelClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onOkClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		DIALOG_VIA_LAYERS_BASE( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Via layer config"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 354,236 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~DIALOG_VIA_LAYERS_BASE();
	
};

#endif //__DIALOG_VIA_LAYERS_BASE_H__
