///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 16 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "class_pcb_layer_box_selector.h"

#include "dialog_via_layers_base.h"

///////////////////////////////////////////////////////////////////////////

DIALOG_VIA_LAYERS_BASE::DIALOG_VIA_LAYERS_BASE( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : DIALOG_SHIM( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	
	wxBoxSizer* bSizes;
	bSizes = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	m_gridViaStack = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_gridViaStack->CreateGrid( 10, 3 );
	m_gridViaStack->EnableEditing( false );
	m_gridViaStack->EnableGridLines( true );
	m_gridViaStack->EnableDragGridSize( false );
	m_gridViaStack->SetMargins( 0, 0 );
	
	// Columns
	m_gridViaStack->AutoSizeColumns();
	m_gridViaStack->EnableDragColMove( false );
	m_gridViaStack->EnableDragColSize( false );
	m_gridViaStack->SetColLabelSize( 30 );
	m_gridViaStack->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_gridViaStack->EnableDragRowSize( true );
	m_gridViaStack->SetRowLabelSize( 80 );
	m_gridViaStack->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_gridViaStack->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	m_gridViaStack->SetMinSize( wxSize( 320,-1 ) );
	m_gridViaStack->SetMaxSize( wxSize( -1,200 ) );
	
	bSizer6->Add( m_gridViaStack, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonAddVia = new wxButton( this, wxID_ANY, _("Add Via Type"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_buttonAddVia, 0, wxALL, 5 );
	
	m_buttonRemoveVia = new wxButton( this, wxID_ANY, _("Delete Via Type"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_buttonRemoveVia, 0, wxALL, 5 );
	
	
	bSizer6->Add( bSizer7, 0, wxALIGN_CENTER|wxBOTTOM|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	
	bSizer5->Add( bSizer6, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	fgSizerVias = new wxFlexGridSizer( 0, 5, 0, 0 );
	fgSizerVias->AddGrowableCol( 1 );
	fgSizerVias->SetFlexibleDirection( wxBOTH );
	fgSizerVias->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	bSizer2->Add( fgSizerVias, 1, wxEXPAND|wxALL, 5 );
	
	bSizerViaList = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerViaListHeader;
	bSizerViaListHeader = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText3->Wrap( -1 );
	bSizerViaListHeader->Add( m_staticText3, 0, wxALL, 5 );
	
	m_staticText71 = new wxStaticText( this, wxID_ANY, _("Start Layer"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText71->Wrap( -1 );
	bSizerViaListHeader->Add( m_staticText71, 0, wxALL, 5 );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, _("End Layer"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText8->Wrap( -1 );
	bSizerViaListHeader->Add( m_staticText8, 0, wxALL, 5 );
	
	m_staticText81 = new wxStaticText( this, wxID_ANY, _("End Layer"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText81->Wrap( -1 );
	bSizerViaListHeader->Add( m_staticText81, 0, wxALL, 5 );
	
	m_staticText811 = new wxStaticText( this, wxID_ANY, _("End Layer"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText811->Wrap( -1 );
	bSizerViaListHeader->Add( m_staticText811, 0, wxALL, 5 );
	
	
	bSizerViaList->Add( bSizerViaListHeader, 0, wxEXPAND, 0 );
	
	m_scrolledWindow1 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );
	bSizerVialListItems = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizerVialListItem;
	bSizerVialListItem = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextViaName = new wxStaticText( m_scrolledWindow1, wxID_ANY, _("Through"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticTextViaName->Wrap( -1 );
	bSizerVialListItem->Add( m_staticTextViaName, 0, wxALL, 5 );
	
	m_ViaStartLayer = new PCB_LAYER_BOX_SELECTOR( m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), 0, NULL, 0 ); 
	bSizerVialListItem->Add( m_ViaStartLayer, 0, wxALL, 5 );
	
	m_ViaEndLayer = new PCB_LAYER_BOX_SELECTOR( m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), 0, NULL, 0 ); 
	bSizerVialListItem->Add( m_ViaEndLayer, 0, wxALL, 5 );
	
	m_textCtrl1 = new wxTextCtrl( m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), 0 );
	bSizerVialListItem->Add( m_textCtrl1, 0, wxALL, 5 );
	
	m_textCtrl2 = new wxTextCtrl( m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), 0 );
	bSizerVialListItem->Add( m_textCtrl2, 0, wxALL, 5 );
	
	
	bSizerVialListItems->Add( bSizerVialListItem, 1, wxEXPAND, 0 );
	
	
	m_scrolledWindow1->SetSizer( bSizerVialListItems );
	m_scrolledWindow1->Layout();
	bSizerVialListItems->Fit( m_scrolledWindow1 );
	bSizerViaList->Add( m_scrolledWindow1, 1, wxEXPAND | wxALL, 0 );
	
	
	bSizer2->Add( bSizerViaList, 1, wxEXPAND, 5 );
	
	
	bSizer5->Add( bSizer2, 2, wxEXPAND, 5 );
	
	
	bSizes->Add( bSizer5, 1, wxEXPAND, 5 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizes->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	m_stdButtons = new wxStdDialogButtonSizer();
	m_stdButtonsOK = new wxButton( this, wxID_OK );
	m_stdButtons->AddButton( m_stdButtonsOK );
	m_stdButtonsCancel = new wxButton( this, wxID_CANCEL );
	m_stdButtons->AddButton( m_stdButtonsCancel );
	m_stdButtons->Realize();
	
	bSizes->Add( m_stdButtons, 0, wxEXPAND|wxALL, 5 );
	
	
	this->SetSizer( bSizes );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( DIALOG_VIA_LAYERS_BASE::onClose ) );
	m_stdButtonsCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_VIA_LAYERS_BASE::onCancelClick ), NULL, this );
	m_stdButtonsOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_VIA_LAYERS_BASE::onOkClick ), NULL, this );
}

DIALOG_VIA_LAYERS_BASE::~DIALOG_VIA_LAYERS_BASE()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( DIALOG_VIA_LAYERS_BASE::onClose ) );
	m_stdButtonsCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_VIA_LAYERS_BASE::onCancelClick ), NULL, this );
	m_stdButtonsOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_VIA_LAYERS_BASE::onOkClick ), NULL, this );
	
}
