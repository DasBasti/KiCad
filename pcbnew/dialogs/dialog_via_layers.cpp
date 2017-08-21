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

    // Set all the layer dropdowns
    m_ViaStartLayer->SetLayersHotkeys( false );
    m_ViaStartLayer->SetLayerSet( LSET::AllNonCuMask() );
    m_ViaStartLayer->SetBoardFrame( (PCB_BASE_FRAME*)aParent );
    m_ViaStartLayer->Resync();
    
    m_ViaEndLayer->SetLayersHotkeys( false );
    m_ViaEndLayer->SetLayerSet( LSET::AllNonCuMask() );
    m_ViaEndLayer->SetBoardFrame( (PCB_BASE_FRAME*)aParent );
    m_ViaEndLayer->Resync();

    m_BlindBurriedViaStartLayer->SetLayersHotkeys( false );
    m_BlindBurriedViaStartLayer->SetLayerSet( LSET::AllNonCuMask() );
    m_BlindBurriedViaStartLayer->SetBoardFrame( (PCB_BASE_FRAME*)aParent );
    m_BlindBurriedViaStartLayer->Resync();

    m_BlindBurriedViaEndLayer->SetLayersHotkeys( false );
    m_BlindBurriedViaEndLayer->SetLayerSet( LSET::AllNonCuMask() );
    m_BlindBurriedViaEndLayer->SetBoardFrame( (PCB_BASE_FRAME*)aParent );
    m_BlindBurriedViaEndLayer->Resync();

    m_MicroViaTopStartLayer->SetLayersHotkeys( false );
    m_MicroViaTopStartLayer->SetLayerSet( LSET::AllNonCuMask() );
    m_MicroViaTopStartLayer->SetBoardFrame( (PCB_BASE_FRAME*)aParent );
    m_MicroViaTopStartLayer->Resync();

    m_MicroViaTopEndLayer->SetLayersHotkeys( false );
    m_MicroViaTopEndLayer->SetLayerSet( LSET::AllNonCuMask() );
    m_MicroViaTopEndLayer->SetBoardFrame( (PCB_BASE_FRAME*)aParent );
    m_MicroViaTopEndLayer->Resync();

    m_MicroViaBottomStartLayer->SetLayersHotkeys( false );
    m_MicroViaBottomStartLayer->SetLayerSet( LSET::AllNonCuMask() );
    m_MicroViaBottomStartLayer->SetBoardFrame( (PCB_BASE_FRAME*)aParent );
    m_MicroViaBottomStartLayer->Resync();

    m_MicroViaBottomEndLayer->SetLayersHotkeys( false );
    m_MicroViaBottomEndLayer->SetLayerSet( LSET::AllNonCuMask() );
    m_MicroViaBottomEndLayer->SetBoardFrame( (PCB_BASE_FRAME*)aParent );
    m_MicroViaBottomEndLayer->Resync();
  
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
