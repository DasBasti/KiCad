/**
 * @file dialog_constraint_layer_selection.cpp
 */

/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2017 Bastian Neumann, neumann.bastian@gmail.com
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


/* functions relative to the design rules editor layer constraint selection
 */

#include <pcbnew.h>
#include <wxPcbStruct.h>
#include <class_board_design_settings.h>

#include <wx/generic/gridctrl.h>

#include "dialog_constraint_layer_selection.h"

DIALOG_CONSTRAINT_LAYER_SELECTION::DIALOG_CONSTRAINT_LAYER_SELECTION( PCB_EDIT_FRAME* parent , unsigned int aLayers ):
    DIALOG_CONSTRAINT_LAYER_SELECTION_BASE( parent )
{
    m_Parent = parent;
    m_layerSelection = aLayers;
    SetAutoLayout( true );
    
    // First layer is
    BOARD* board = m_Parent->GetBoard();
    wxASSERT( board );

    for( int i = 0; i < 32; i++ ) // KiCad has 32 Layer available
    {
        m_grid3->AppendRows();
        int row = m_grid3->GetRows()-1;
        m_grid3->SetRowLabelValue( row, board->GetLayerName( ToLAYER_ID( i ) ) );
        m_grid3->SetCellRenderer( row, 0, new wxGridCellBoolRenderer );
        m_grid3->SetCellEditor( row, 0, new wxGridCellBoolEditor );
        wxString cheked = m_grid3->GetCellValue(row, 0);
    }
    
    Layout();
    
    FinishDialogSettings();
}


unsigned int DIALOG_CONSTRAINT_LAYER_SELECTION::GetConstraintLayers()
{
    
    
    return m_layerSelection;
}