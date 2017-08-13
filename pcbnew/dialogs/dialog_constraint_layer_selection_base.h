///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 16 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __DIALOG_CONSTRAINT_LAYER_SELECTION_BASE_H__
#define __DIALOG_CONSTRAINT_LAYER_SELECTION_BASE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
class DIALOG_SHIM;

#include "dialog_shim.h"
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/font.h>
#include <wx/grid.h>
#include <wx/gdicmn.h>
#include <wx/statline.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class DIALOG_CONSTRAINT_LAYER_SELECTION_BASE
///////////////////////////////////////////////////////////////////////////////
class DIALOG_CONSTRAINT_LAYER_SELECTION_BASE : public DIALOG_SHIM
{
	private:
	
	protected:
		wxGrid* m_grid3;
		wxStaticLine* m_staticline2;
		wxStdDialogButtonSizer* m_sdbSizer3;
		wxButton* m_sdbSizer3OK;
		wxButton* m_sdbSizer3Cancel;
	
	public:
		
		DIALOG_CONSTRAINT_LAYER_SELECTION_BASE( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Select Layer:"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 209,183 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~DIALOG_CONSTRAINT_LAYER_SELECTION_BASE();
	
};

#endif //__DIALOG_CONSTRAINT_LAYER_SELECTION_BASE_H__
