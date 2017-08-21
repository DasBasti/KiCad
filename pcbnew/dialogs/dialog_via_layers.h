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

#ifndef __dialog_via_layers__
#define __dialog_via_layers__

#include <wx_unit_binder.h>

#include "dialog_via_layers_base.h"

class BOARD_DESIGN_SETTINGS;

/** Implementing DIALOG_VIA_LAYERS_BASE */
class DIALOG_VIA_LAYERS : public DIALOG_VIA_LAYERS_BASE
{
public:
    /** Constructor */
    DIALOG_VIA_LAYERS( wxWindow* aParent, BOARD_DESIGN_SETTINGS& aSettings );

protected:


    // Routings settings that are modified by the dialog.
    BOARD_DESIGN_SETTINGS& m_settings;

    ///> Checks if values given in the dialog are sensible.
    bool check();

    // Handlers for DIALOG_TRACK_VIA_SIZE_BASE events.
    void onClose( wxCloseEvent& aEvent ) override;
    void onOkClick( wxCommandEvent& aEvent ) override;
    void onCancelClick( wxCommandEvent& aEvent ) override;
};

#endif // __dialog_via_layers__
