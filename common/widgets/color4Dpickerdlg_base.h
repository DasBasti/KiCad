///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug  4 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __COLOR4DPICKERDLG_BASE_H__
#define __COLOR4DPICKERDLG_BASE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
class DIALOG_SHIM;

#include "dialog_shim.h"
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/slider.h>
#include <wx/spinctrl.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class COLOR4D_PICKER_DLG_BASE
///////////////////////////////////////////////////////////////////////////////
class COLOR4D_PICKER_DLG_BASE : public DIALOG_SHIM
{
	private:
	
	protected:
		wxNotebook* m_notebook;
		wxPanel* m_panelFreeColors;
		wxStaticBitmap* m_RgbBitmap;
		wxStaticBitmap* m_HsvBitmap;
		wxStaticText* m_staticTextBright;
		wxSlider* m_sliderBrightness;
		wxStaticText* m_staticTextR;
		wxStaticText* m_staticTextG;
		wxStaticText* m_staticTextB;
		wxSpinCtrl* m_spinCtrlRed;
		wxSpinCtrl* m_spinCtrlGreen;
		wxSpinCtrl* m_spinCtrlBlue;
		wxStaticText* m_staticTextHue;
		wxStaticText* m_staticTextSat;
		wxSpinCtrl* m_spinCtrlHue;
		wxSpinCtrl* m_spinCtrlSaturation;
		wxPanel* m_panelDefinedColors;
		wxBoxSizer* m_SizerDefinedColors;
		wxFlexGridSizer* m_fgridColor;
		wxBoxSizer* m_SizerTransparency;
		wxStaticText* m_staticText9;
		wxSlider* m_sliderTransparency;
		wxStaticText* m_staticTextOldColor;
		wxStaticBitmap* m_OldColorRect;
		wxStaticText* m_staticTextNewColor;
		wxStaticBitmap* m_NewColorRect;
		wxStaticLine* m_staticline;
		wxStdDialogButtonSizer* m_sdbSizer;
		wxButton* m_sdbSizerOK;
		wxButton* m_sdbSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onRGBMouseClick( wxMouseEvent& event ) { event.Skip(); }
		virtual void onRGBMouseDrag( wxMouseEvent& event ) { event.Skip(); }
		virtual void onHSVMouseClick( wxMouseEvent& event ) { event.Skip(); }
		virtual void onHSVMouseDrag( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnChangeBrightness( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnChangeEditRed( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnChangeEditGreen( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnChangeEditBlue( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnChangeEditHue( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnChangeEditSat( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnChangeAlpha( wxScrollEvent& event ) { event.Skip(); }
		
	
	public:
		
		COLOR4D_PICKER_DLG_BASE( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Color Picker"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 707,375 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~COLOR4D_PICKER_DLG_BASE();
	
};

#endif //__COLOR4DPICKERDLG_BASE_H__
