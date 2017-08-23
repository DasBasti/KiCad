/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2017 Bastian Neumann <neumann.bastian@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#include "dialog_via_layers.h"
#include <base_units.h>
#include <confirm.h>
#include <boost/optional.hpp>
#include <class_pcb_layer_box_selector.h>

#include "class_board_design_settings.h"

DIALOG_VIA_LAYERS::DIALOG_VIA_LAYERS( wxWindow* aParent, BOARD_DESIGN_SETTINGS& aSettings ) :
    DIALOG_VIA_LAYERS_BASE( aParent ),
    m_settings( aSettings )
{
  std::list<wxBoxSizer*> layers;
  std::list<wxBoxSizer*>::iterator itLayers;

    for( int i = 0; i < 10; i++ )
    {
        wxBoxSizer* bSizerVialListItem;
        bSizerVialListItem = new wxBoxSizer( wxHORIZONTAL );
        
        wxStaticText* staticTextViaName = new wxStaticText( m_scrolledWindow1, wxID_ANY, _("Through"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
        staticTextViaName->Wrap( -1 );
        bSizerVialListItem->Add( staticTextViaName, 0, wxALL, 5 );
        
        PCB_LAYER_BOX_SELECTOR* ViaStartLayer = new PCB_LAYER_BOX_SELECTOR( m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), 0, NULL, 0 ); 
        bSizerVialListItem->Add( ViaStartLayer, 0, wxALL, 5 );
        
        PCB_LAYER_BOX_SELECTOR* ViaEndLayer = new PCB_LAYER_BOX_SELECTOR( m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), 0, NULL, 0 ); 
        bSizerVialListItem->Add( ViaEndLayer, 0, wxALL, 5 );
        
        wxTextCtrl* textCtrl1 = new wxTextCtrl( m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), 0 );
        bSizerVialListItem->Add( textCtrl1, 0, wxALL, 5 );
        
        wxTextCtrl* textCtrl2 = new wxTextCtrl( m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), 0 );
        bSizerVialListItem->Add( textCtrl2, 0, wxALL, 5 );
    }
    
    for( itLayers = layers.begin(); itLayers != layers.end(); ++itLayers )
    {
/*        fgSizerVias->Add( *itLayers, 0, wxALL, 5 );
        (*itLayers)->SetLayersHotkeys( false );
        (*itLayers)->SetLayerSet( LSET::AllNonCuMask() );
        (*itLayers)->SetBoardFrame( (PCB_BASE_FRAME*)aParent );
        (*itLayers)->Resync();
  */      bSizerVialListItems->Add( (*itLayers), 1, wxEXPAND, 0 );        
    }


  
    // Now all widgets have the size fixed, call FinishDialogSettings
    FinishDialogSettings();

    // Pressing ENTER when any of the text input fields is active applies changes
    Connect( wxEVT_TEXT_ENTER, wxCommandEventHandler( DIALOG_VIA_LAYERS::onOkClick ), NULL, this );
}


bool DIALOG_VIA_LAYERS::check()
{
/*    if( m_trackWidth.GetValue() <= 0 )
    {
        DisplayError( GetParent(), _( "Invalid track width" ) );
        m_trackWidthText->SetFocus();
        return false;
    }

    if( m_viaDiameter.GetValue() <= 0 )
    {
        DisplayError( GetParent(), _( "Invalid via diameter" ) );
        m_viaDiameterText->SetFocus();
        return false;
    }

    if( m_viaDrill.GetValue() <= 0 )
    {
        DisplayError( GetParent(), _( "Invalid via drill size" ) );
        m_viaDrillText->SetFocus();
        return false;
    }

    if( m_viaDrill.GetValue() >= m_viaDiameter.GetValue() )
    {
        DisplayError( GetParent(), _( "Via drill size has to be smaller than via diameter" ) );
        m_viaDrillText->SetFocus();
        return false;
    }
*/
    return true;
}


void DIALOG_VIA_LAYERS::onClose( wxCloseEvent& aEvent )
{
    EndModal( 0 );
}


void DIALOG_VIA_LAYERS::onOkClick( wxCommandEvent& aEvent )
{
    if( check() )
    {
        EndModal( 1 );
    }
}


void DIALOG_VIA_LAYERS::onCancelClick( wxCommandEvent& aEvent )
{
    EndModal( 0 );
}
