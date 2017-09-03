/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2015 CERN
 * @author Maciej Suminski <maciej.suminski@cern.ch>
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

#include <dialogs/dialog_track_via_properties.h>
#include <class_pcb_layer_box_selector.h>
#include <tools/selection_tool.h>
#include <class_track.h>
#include <wxPcbStruct.h>
#include <confirm.h>

#include <widgets/widget_net_selector.h>
#include <board_commit.h>


int findUserViaStyle( std::vector<VIA_DIMENSION> aVdl, int aDiameter, int aDrill, VIATYPE_T aType, PCB_LAYER_ID aStartLayer, PCB_LAYER_ID aEndLayer )
{
    for( uint ii=0; ii < aVdl.size(); ++ii )
    {
        if( aVdl[ii].m_Diameter == aDiameter
         && aVdl[ii].m_Drill == aDrill
         && aVdl[ii].m_Type == aType
         && aVdl[ii].m_StartLayer == aStartLayer
         && aVdl[ii].m_EndLayer == aEndLayer )
            return ii;
    }

    return -1;
}


DIALOG_TRACK_VIA_PROPERTIES::DIALOG_TRACK_VIA_PROPERTIES( PCB_BASE_FRAME* aParent, const SELECTION& aItems ) :
    DIALOG_TRACK_VIA_PROPERTIES_BASE( aParent ), m_items( aItems ),
    m_trackStartX( aParent, m_TrackStartXCtrl, m_TrackStartXUnit ),
    m_trackStartY( aParent, m_TrackStartYCtrl, m_TrackStartYUnit ),
    m_trackEndX( aParent, m_TrackEndXCtrl, m_TrackEndXUnit ),
    m_trackEndY( aParent, m_TrackEndYCtrl, m_TrackEndYUnit ),
    m_trackWidth( aParent, m_TrackWidthCtrl, m_TrackWidthUnit ),
    m_viaX( aParent, m_ViaXCtrl, m_ViaXUnit ), m_viaY( aParent, m_ViaYCtrl, m_ViaYUnit ),
    m_viaDiameter( aParent, m_ViaDiameterCtrl, m_ViaDiameterUnit ),
    m_viaDrill( aParent, m_ViaDrillCtrl, m_ViaDrillUnit ),
    m_tracks( false ), m_vias( false )
{
    wxASSERT( !m_items.Empty() );

    // This is a way to trick gcc into considering these variables as initialized
    boost::optional<int> trackStartX = boost::make_optional<int>( false, 0 );
    boost::optional<int> trackStartY = boost::make_optional<int>( false, 0 );
    boost::optional<int> trackEndX = boost::make_optional<int>( false, 0 );
    boost::optional<int> trackEndY = boost::make_optional<int>( false, 0 );
    boost::optional<int> trackWidth = boost::make_optional<int>( false, 0 );
    boost::optional<PCB_LAYER_ID> trackLayer = boost::make_optional<PCB_LAYER_ID>( false, (PCB_LAYER_ID) 0 );
    boost::optional<int> viaX = boost::make_optional<int>( false, 0 );
    boost::optional<int> viaY = boost::make_optional<int>( false, 0 );
    boost::optional<int> viaDiameter = boost::make_optional<int>( false, 0 );
    boost::optional<int> viaDrill = boost::make_optional<int>( false, 0 );
    boost::optional<PCB_LAYER_ID> viaStartLayer = boost::make_optional<PCB_LAYER_ID>( false, (PCB_LAYER_ID) 0 );
    boost::optional<PCB_LAYER_ID> viaEndLayer = boost::make_optional<PCB_LAYER_ID>( false, (PCB_LAYER_ID) 0 );
    boost::optional<int> viaType = boost::make_optional<int>( false, 0 );

    m_haveUniqueNet = true;
    int prevNet = -1;

    printf("Create!\n");

    m_Pcb = aParent->GetBoard();
    
    m_NetComboBox->SetBoard( m_Pcb );
    m_NetComboBox->Enable( true );

    bool hasLocked = false;
    bool hasUnlocked = false;

    for( auto& item : m_items )
    {
        int net = static_cast<BOARD_CONNECTED_ITEM*>(item)->GetNetCode();

        if( prevNet >= 0 && net != prevNet )
        {
            printf("prev %d net %d\n", net, prevNet );
            m_haveUniqueNet = false;
            break;
        }

        prevNet = net;
    }

    if ( m_haveUniqueNet )
    {
        m_NetComboBox->SetSelectedNet( prevNet );
    }
    else
    {
        m_NetComboBox->SetMultiple( true );
    }

    // Look for values that are common for every item that is selected
    for( auto& item : m_items )
    {
        switch( item->Type() )
        {
            case PCB_TRACE_T:
            {
                const TRACK* t = static_cast<const TRACK*>( item );

                if( !m_tracks )     // first track in the list
                {
                    trackStartX = t->GetStart().x;
                    trackStartY = t->GetStart().y;
                    trackEndX   = t->GetEnd().x;
                    trackEndY   = t->GetEnd().y;
                    trackWidth  = t->GetWidth();
                    trackLayer  = t->GetLayer();
                    m_tracks    = true;
                }
                else        // check if values are the same for every selected track
                {
                    if( trackStartX && ( *trackStartX != t->GetStart().x ) )
                        trackStartX = boost::none;

                    if( trackStartY && ( *trackStartY != t->GetStart().y ) )
                        trackStartY = boost::none;

                    if( trackEndX && ( *trackEndX != t->GetEnd().x ) )
                        trackEndX = boost::none;

                    if( trackEndY && ( *trackEndY != t->GetEnd().y ) )
                        trackEndY = boost::none;

                    if( trackWidth && ( *trackWidth != t->GetWidth() ) )
                        trackWidth = boost::none;

                    if( trackLayer && ( *trackLayer != t->GetLayer() ) )
                        trackLayer = boost::none;
                }

                if( t->IsLocked() )
                    hasLocked = true;
                else
                    hasUnlocked = true;

                break;
            }

            case PCB_VIA_T:
            {
                const VIA* v = static_cast<const VIA*>( item );

                if( !m_vias )       // first via in the list
                {
                    viaX = v->GetPosition().x;
                    viaY = v->GetPosition().y;
                    viaDiameter = v->GetWidth();
                    viaDrill = v->GetDrillValue();
                    PCB_LAYER_ID layerStart;
                    PCB_LAYER_ID layerEnd;
                    v->LayerPair(&layerStart, &layerEnd);
                    viaStartLayer = layerStart;
                    viaEndLayer = layerEnd;
                    viaType = v->GetViaType();
                    m_vias = true;
                }
                else        // check if values are the same for every selected via
                {
                    if( viaX && ( *viaX != v->GetPosition().x ) )
                        viaX = boost::none;

                    if( viaY && ( *viaY != v->GetPosition().y ) )
                        viaY = boost::none;

                    if( viaDiameter && ( *viaDiameter != v->GetWidth() ) )
                        viaDiameter = boost::none;

                    if( viaDrill && ( *viaDrill != v->GetDrillValue() ) )
                        viaDrill = boost::none;

                    PCB_LAYER_ID layerStart;
                    PCB_LAYER_ID layerEnd;
                    v->LayerPair(&layerStart, &layerEnd);
                    if( viaStartLayer && ( viaStartLayer != layerStart ) )
                        viaStartLayer = boost::none;
                    if( viaEndLayer && ( viaEndLayer != layerEnd ) )
                        viaEndLayer = boost::none;

                    if( viaType && ( *viaType != v->GetViaType() ) )
                        viaType = boost::none;
                }

                if( v->IsLocked() )
                    hasLocked = true;
                else
                    hasUnlocked = true;

                // load up via selector with list of user vias
                wxArrayString m_ViaTypeChoiceChoices;
                std::vector<VIA_DIMENSION> ViasDimensionsList = m_Pcb->GetDesignSettings().m_ViasDimensionsList;
                uint selection;
                for( uint ii = 0; ii < ViasDimensionsList.size(); ii++ )
                {
                    wxString msg;

                    switch( ViasDimensionsList[ii].m_Type )
                    {
                        case VIA_BLIND_BURIED:
                            msg += "[B] ";
                            break;
                        case VIA_MICROVIA:
                            msg += "[M] ";
                            break;
                        case VIA_THROUGH:
                            msg += "[T] ";
                            break;
                        default:
                            msg += "[?] ";
                            break;
                    }

                    msg += StringFromValue( g_UserUnit, ViasDimensionsList[ii].m_Diameter, false );
                    msg += "/";
                    msg += StringFromValue( g_UserUnit, ViasDimensionsList[ii].m_Drill, false );
                    msg += ReturnUnitSymbol( g_UserUnit , " %s");
                    msg += "\t";

                    msg += m_Pcb->GetLayerName( ViasDimensionsList[ii].m_StartLayer );
                    msg += " - ";
                    msg += m_Pcb->GetLayerName( ViasDimensionsList[ii].m_EndLayer );

                    m_ViaTypeChoiceChoices.Add( msg );

                    PCB_LAYER_ID startLayer, endLayer;
                    v->LayerPair( &startLayer, &endLayer );
                    if( ViasDimensionsList[ii].m_Diameter == v->GetWidth()
                     && ViasDimensionsList[ii].m_Drill == v->GetDrill()
                     && ViasDimensionsList[ii].m_Type == v->GetViaType()
                     && ViasDimensionsList[ii].m_StartLayer == startLayer
                     && ViasDimensionsList[ii].m_EndLayer == endLayer
                    )
                        selection = ii;
                }

                /*m_ViaTypeChoice->Clear();
                m_ViaTypeChoice->Append(m_ViaTypeChoiceChoices);
                m_ViaTypeChoice->Enable();
                m_ViaTypeChoice->SetSelection(selection);
                */
                m_UserViaListBox->Append( m_ViaTypeChoiceChoices );
                if( selection < m_UserViaListBox->GetCount() ) // we don't know the combination. don't select any
                    m_UserViaListBox->SetSelection( selection );
                else
                    m_UserViaListBox->IsSelected(wxNOT_FOUND);
                break;
            }

            default:
                wxASSERT( false );
                break;
        }
    }

    wxASSERT( m_tracks || m_vias );

    if( m_vias )
    {
        setCommonVal( viaX, m_ViaXCtrl, m_viaX );
        setCommonVal( viaY, m_ViaYCtrl, m_viaY );
        setCommonVal( viaDiameter, m_ViaDiameterCtrl, m_viaDiameter );
        setCommonVal( viaDrill, m_ViaDrillCtrl, m_viaDrill );

        m_ViaTypeChoice->SetSelection(*viaType);
        m_ViaTypeChoice->Enable();

        m_ViaStartLayer->SetLayersHotkeys( false );
        m_ViaStartLayer->SetLayerSet( LSET::AllNonCuMask() );
        m_ViaStartLayer->SetBoardFrame( aParent );
        m_ViaStartLayer->Resync();

        if( viaStartLayer )
            m_ViaStartLayer->SetLayerSelection( *viaStartLayer );

        m_ViaEndLayer->SetLayersHotkeys( false );
        m_ViaEndLayer->SetLayerSet( LSET::AllNonCuMask() );
        m_ViaEndLayer->SetBoardFrame( aParent );
        m_ViaEndLayer->Resync();

        if( viaEndLayer )
            m_ViaEndLayer->SetLayerSelection( *viaEndLayer );

        m_ViaDiameterCtrl->SetFocus();


    }
    else
    {
        m_MainSizer->Hide( m_sbViaSizer, true );
    }

    if( m_tracks )
    {
        setCommonVal( trackStartX, m_TrackStartXCtrl, m_trackStartX );
        setCommonVal( trackStartY, m_TrackStartYCtrl, m_trackStartY );
        setCommonVal( trackEndX, m_TrackEndXCtrl, m_trackEndX );
        setCommonVal( trackEndY, m_TrackEndYCtrl, m_trackEndY );
        setCommonVal( trackWidth, m_TrackWidthCtrl, m_trackWidth );

        for( unsigned ii = 0; ii < aParent->GetDesignSettings().m_TrackWidthList.size(); ii++ )
        {
            int width = aParent->GetDesignSettings().m_TrackWidthList[ii];
            wxString msg = StringFromValue( g_UserUnit, width, false );
            m_TrackWidthCtrl->Append( msg );
        }

        m_TrackLayerCtrl->SetLayersHotkeys( false );
        m_TrackLayerCtrl->SetLayerSet( LSET::AllNonCuMask() );
        m_TrackLayerCtrl->SetBoardFrame( aParent );
        m_TrackLayerCtrl->Resync();

        if( trackLayer )
            m_TrackLayerCtrl->SetLayerSelection( *trackLayer );

        m_TrackWidthCtrl->SetFocus();
    }
    else
    {
        m_MainSizer->Hide( m_sbTrackSizer, true );
    }

    if( hasLocked && hasUnlocked )
    {
         m_lockedCbox->Set3StateValue( wxCHK_UNDETERMINED );
    }
    else if( hasLocked )
    {
        m_lockedCbox->Set3StateValue( wxCHK_CHECKED );
    }
    else
    {
        m_lockedCbox->Set3StateValue( wxCHK_UNCHECKED );
    }

    m_StdButtonsOK->SetDefault();

    // Pressing ENTER when any of the text input fields is active applies changes
    Connect( wxEVT_TEXT_ENTER, wxCommandEventHandler( DIALOG_TRACK_VIA_PROPERTIES::onOkClick ),
             NULL, this );
}


bool DIALOG_TRACK_VIA_PROPERTIES::Apply( COMMIT& aCommit )
{
    if( !check() )
        return false;

    bool changeLock = m_lockedCbox->Get3StateValue() != wxCHK_UNDETERMINED;
    bool setLock = m_lockedCbox->Get3StateValue() == wxCHK_CHECKED;

    for( auto item : m_items )
    {
        aCommit.Modify( item );

        switch( item->Type() )
        {
            case PCB_TRACE_T:
            {
                wxASSERT( m_tracks );
                TRACK* t = static_cast<TRACK*>( item );

                if( m_trackStartX.Valid() || m_trackStartY.Valid() )
                {
                    wxPoint start = t->GetStart();

                    if( m_trackStartX.Valid() )
                        start.x = m_trackStartX.GetValue();

                    if( m_trackStartY.Valid() )
                        start.y = m_trackStartY.GetValue();

                    t->SetStart( start );
                }

                if( m_trackEndX.Valid() || m_trackEndY.Valid() )
                {
                    wxPoint end = t->GetEnd();

                    if( m_trackEndX.Valid() )
                        end.x = m_trackEndX.GetValue();

                    if( m_trackEndY.Valid() )
                        end.y = m_trackEndY.GetValue();

                    t->SetEnd( end );
                }

                if( m_trackNetclass->IsChecked() )
                {
                    t->SetWidth( t->GetNetClass()->GetTrackWidth() );
                }
                else if( m_trackWidth.Valid() )
                {
                    t->SetWidth( m_trackWidth.GetValue() );
                }

                LAYER_NUM layer = m_TrackLayerCtrl->GetLayerSelection();

                if( layer != UNDEFINED_LAYER )
                    t->SetLayer( (PCB_LAYER_ID) layer );

                if( changeLock )
                    t->SetLocked( setLock );

                if ( m_NetComboBox->IsUniqueNetSelected() )
                {
                    printf("snc %d\n", m_NetComboBox->GetSelectedNet());
                    t->SetNetCode( m_NetComboBox->GetSelectedNet() );
                }


                break;
            }

            case PCB_VIA_T:
            {
                wxASSERT( m_vias );

                VIA* v = static_cast<VIA*>( item );

                if( m_viaX.Valid() || m_viaY.Valid() )
                {
                    wxPoint pos = v->GetPosition();

                    if( m_viaX.Valid() )
                        pos.x = m_viaX.GetValue();

                    if( m_viaY.Valid() )
                        pos.y = m_viaY.GetValue();

                    v->SetPosition( pos );
                }

                if( m_viaNetclass->IsChecked() )
                {
                    switch( v->GetViaType() )
                    {
                    default:
                        wxFAIL_MSG("Unhandled via type");
                        // fall through

                    case VIA_THROUGH:
                    case VIA_BLIND_BURIED:
                        v->SetWidth( v->GetNetClass()->GetViaDiameter() );
                        v->SetDrill( v->GetNetClass()->GetViaDrill() );
                        break;

                    case VIA_MICROVIA:
                        v->SetWidth( v->GetNetClass()->GetuViaDiameter() );
                        v->SetDrill( v->GetNetClass()->GetuViaDrill() );
                        break;
                    }
                }
                else
                {
                    if( m_viaDiameter.Valid() )
                        v->SetWidth( m_viaDiameter.GetValue() );

                    if( m_viaDrill.Valid() )
                        v->SetDrill( m_viaDrill.GetValue() );

                    if( m_ViaTypeChoice->GetSelection() != (int)v->GetViaType() )
                        v->SetViaType( (VIATYPE_T)m_ViaTypeChoice->GetSelection());

                    PCB_LAYER_ID startLayer, endLayer;
                    v->LayerPair( &startLayer, &endLayer );
                    if( ToLAYER_ID( m_ViaStartLayer->GetLayerSelection() ) != startLayer 
                     || ToLAYER_ID( m_ViaEndLayer->GetLayerSelection() ) != endLayer )
                        v->SetLayerPair( ToLAYER_ID( m_ViaStartLayer->GetLayerSelection() ), ToLAYER_ID( m_ViaEndLayer->GetLayerSelection() ) );

                }

                if ( m_NetComboBox->IsUniqueNetSelected() )
                {
                    printf("snc %d\n", m_NetComboBox->GetSelectedNet());
                    v->SetNetCode( m_NetComboBox->GetSelectedNet() );
                }


                if( changeLock )
                    v->SetLocked( setLock );

                break;
            }

            default:
                wxASSERT( false );
                break;
        }
    }

    return true;
}


void DIALOG_TRACK_VIA_PROPERTIES::onClose( wxCloseEvent& aEvent )
{
    EndModal( 0 );
}


void DIALOG_TRACK_VIA_PROPERTIES::onTrackNetclassCheck( wxCommandEvent& aEvent )
{
    bool enableNC = aEvent.IsChecked();

    m_TrackWidthLabel->Enable( !enableNC );
    m_TrackWidthCtrl->Enable( !enableNC );
    m_TrackWidthUnit->Enable( !enableNC );
}

void DIALOG_TRACK_VIA_PROPERTIES::onUserViaDClick( wxCommandEvent& aEvent )
{
        m_viaDiameter.SetValue(m_Pcb->GetDesignSettings().m_ViasDimensionsList[m_UserViaListBox->GetSelection()].m_Diameter);
        m_viaDrill.SetValue(m_Pcb->GetDesignSettings().m_ViasDimensionsList[m_UserViaListBox->GetSelection()].m_Drill);
        m_ViaTypeChoice->SetSelection(m_Pcb->GetDesignSettings().m_ViasDimensionsList[m_UserViaListBox->GetSelection()].m_Type);
        m_ViaStartLayer->SetLayerSelection(m_Pcb->GetDesignSettings().m_ViasDimensionsList[m_UserViaListBox->GetSelection()].m_StartLayer);
        m_ViaEndLayer->SetLayerSelection(m_Pcb->GetDesignSettings().m_ViasDimensionsList[m_UserViaListBox->GetSelection()].m_EndLayer);
}

void DIALOG_TRACK_VIA_PROPERTIES::onViaNetclassCheck( wxCommandEvent& aEvent )
{
    bool enableNC = aEvent.IsChecked();

    m_ViaDiameterLabel->Enable( !enableNC );
    m_ViaDiameterCtrl->Enable( !enableNC );
    m_ViaDiameterUnit->Enable( !enableNC );

    m_ViaDrillLabel->Enable( !enableNC );
    m_ViaDrillCtrl->Enable( !enableNC );
    m_ViaDrillUnit->Enable( !enableNC );
}


void DIALOG_TRACK_VIA_PROPERTIES::onCancelClick( wxCommandEvent& aEvent )
{
    EndModal( 0 );
}


void DIALOG_TRACK_VIA_PROPERTIES::onOkClick( wxCommandEvent& aEvent )
{
    std::vector <VIA_DIMENSION> viasDimensionsList = m_Pcb->GetDesignSettings().m_ViasDimensionsList;
    if( findUserViaStyle( viasDimensionsList,
                                     m_viaDiameter.GetValue(),
                                     m_viaDrill.GetValue(),
                                     (VIATYPE_T)m_ViaTypeChoice->GetSelection(),
                                     ToLAYER_ID( m_ViaStartLayer->GetLayerSelection() ),
                                     ToLAYER_ID( m_ViaEndLayer->GetLayerSelection() ) ) == wxNOT_FOUND )
    {
        // add via settings to user via list
        if ( m_userViaCheckBox->GetValue() )
        {
            VIA_DIMENSION via;
            via.m_Diameter = m_viaDiameter.GetValue();
            via.m_Drill = m_viaDrill.GetValue();
            via.m_Type = (VIATYPE_T)m_ViaTypeChoice->GetSelection();
            via.m_StartLayer = ToLAYER_ID( m_ViaStartLayer->GetLayerSelection() );
            via.m_EndLayer = ToLAYER_ID( m_ViaEndLayer->GetLayerSelection() );
            viasDimensionsList.push_back(via);
            // Sort new list by by increasing value
            sort( viasDimensionsList.begin(), viasDimensionsList.end() );
            // Reinitialize m_ViaSizeList
            std::vector<VIA_DIMENSION>* vialist = &m_Pcb->GetDesignSettings().m_ViasDimensionsList;
            vialist->erase( vialist->begin() + 1, vialist->end() );
            vialist->insert( vialist->end(), viasDimensionsList.begin(), viasDimensionsList.end() );

        }
    }

    if( check() )
        EndModal( 1 );
}


void DIALOG_TRACK_VIA_PROPERTIES::onViaChangeProperties( wxCommandEvent& aEvent )
{
    m_UserViaListBox->SetSelection( findUserViaStyle( m_Pcb->GetDesignSettings().m_ViasDimensionsList,
                                         m_viaDiameter.GetValue(),
                                         m_viaDrill.GetValue(),
                                         (VIATYPE_T)m_ViaTypeChoice->GetSelection(),
                                         ToLAYER_ID( m_ViaStartLayer->GetLayerSelection() ),
                                         ToLAYER_ID( m_ViaEndLayer->GetLayerSelection() ) ) );
}


void DIALOG_TRACK_VIA_PROPERTIES::onViaEndLayerCombobox( wxCommandEvent& aEvent )
{
/*    if( findUserViaStyle( m_Pcb->GetDesignSettings().m_ViasDimensionsList,
                          m_viaDiameter.GetValue(),
                          m_viaDrill.GetValue(),
                          (VIATYPE_T)m_ViaTypeChoice->GetSelection(),
                          ToLAYER_ID( m_ViaStartLayer->GetLayerSelection() ),
                          ToLAYER_ID( m_ViaEndLayer->GetLayerSelection() ) )
        =! -1)
    {
        DisplayError( GetParent(), _( "Invalid via selected. Add via configurations in Design Rules dialog." ) );
    }
    */
}


bool DIALOG_TRACK_VIA_PROPERTIES::check() const
{
    bool trackNetclass = m_trackNetclass->IsChecked();
    bool viaNetclass = m_trackNetclass->IsChecked();

    if( m_tracks && !trackNetclass && m_trackWidth.Valid() && m_trackWidth.GetValue() <= 0 )
    {
        DisplayError( GetParent(), _( "Invalid track width" ) );
        m_TrackWidthCtrl->SetFocus();
        return false;
    }

    if( m_vias && !viaNetclass )
    {
        if( m_viaDiameter.Valid() && m_viaDiameter.GetValue() <= 0 )
        {
            DisplayError( GetParent(), _( "Invalid via diameter" ) );
            m_ViaDiameterCtrl->SetFocus();
            return false;
        }

        if( m_viaDrill.Valid() && m_viaDrill.GetValue() <= 0 )
        {
            DisplayError( GetParent(), _( "Invalid via drill size" ) );
            m_ViaDrillCtrl->SetFocus();
            return false;
        }

        if( m_viaDiameter.Valid() && m_viaDrill.Valid() && m_viaDiameter.GetValue() <= m_viaDrill.GetValue() )
        {
            DisplayError( GetParent(), _( "Via drill size has to be smaller than via diameter" ) );
            m_ViaDrillCtrl->SetFocus();
            return false;
        }
        if( findUserViaStyle( m_Pcb->GetDesignSettings().m_ViasDimensionsList,
                                         m_viaDiameter.GetValue(),
                                         m_viaDrill.GetValue(),
                                         (VIATYPE_T)m_ViaTypeChoice->GetSelection(),
                                         ToLAYER_ID( m_ViaStartLayer->GetLayerSelection() ),
                                         ToLAYER_ID( m_ViaEndLayer->GetLayerSelection() ) ) == wxNOT_FOUND )
        {
            DisplayError( GetParent(), _( "Via settings are not found in user via classes.\n\r" \
                                           "Select Add Via to add user via list." ) );
            return false;
        }
    }

    return true;
}
