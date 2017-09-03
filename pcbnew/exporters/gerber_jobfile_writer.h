/**
 * @file gerber_jobfile_writer.h
 * @brief Classes used in drill files, map files and report files generation.
 */

/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 1992-2017 Jean_Pierre Charras <jp.charras at wanadoo.fr>
 * Copyright (C) 1992-2017 KiCad Developers, see change_log.txt for contributors.
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

#ifndef GERBER_JOBFILE_WRITER_H
#define GERBER_JOBFILE_WRITER_H


// A helper enum to handle sides of some layers (silk, mask)
enum ONSIDE
{
    SIDE_NONE = 0,      // layers not present
    SIDE_TOP = 1,       // top layer only
    SIDE_BOTTOM = 2,    // bottom layer only
    SIDE_BOTH = SIDE_TOP|SIDE_BOTTOM    // both layers
};

class BOARD;

/**
 * class JOBFILE_PARAMS store the list of parameters written in Gerber job file
 * especialy list of .gbr filenames and the corresponding layer id belonging the job
 */
class JOBFILE_PARAMS
{
public:
    wxArrayString m_GerberFileList;         // the list of gerber filenames (without path)
    std::vector<PCB_LAYER_ID> m_LayerId;    // the list of corresponding layer id
};


/**
 * GERBER_JOBFILE_WRITER is a class used to create Gerber job file
 * a Gerber job file stores info to make a board:
 * list of gerber files
 * info about the board itsel:
 *  size, number of copper layers
 *  thickness of the board, copper and dielectric
 *  and some other info (colors, finish type ...)
 *
 * note: dimensions are always in mm in Kicad job file (can be also in inches in a job file)
 * and they are in floating point notation
 */
class GERBER_JOBFILE_WRITER
{
public:
    GERBER_JOBFILE_WRITER( BOARD* aPcb, REPORTER* aReporter = nullptr );

    virtual ~GERBER_JOBFILE_WRITER()
    {
    }

    /**
     * add a gerber file name and type in job file list
     * @param aLayer is the PCB_LAYER_ID corresponding to the gerber file
     * @param aFilename is the filename (without path) of the gerber file
     */
    void AddGbrFile( PCB_LAYER_ID aLayer, wxString& aFilename )
    {
        m_params.m_GerberFileList.Add( aFilename );
        m_params.m_LayerId.push_back( aLayer );
    }

    /**
     * Creates an Excellon drill file
     * @param aFullFilename = the full filename
     * @param aParams = true for a NPTH file, false for a PTH file
     * @return true, or false if the file cannot be created
     */
    bool  CreateJobFile( const wxString& aFullFilename );

private:
    /** @return SIDE_NONE if no silk screen layer is in list
     * SIDE_TOP if top silk screen layer is in list
     * SIDE_BOTTOM if bottom silk screen layer is in list
     * SIDE_BOTH if top and bottom silk screen layers are in list
     */
    enum ONSIDE hasSilkLayers();

    /** @return SIDE_NONE if no soldermask layer is in list
     * SIDE_TOP if top soldermask layer is in list
     * SIDE_BOTTOM if bottom soldermask layer is in list
     * SIDE_BOTH if top and bottom soldermask layers are in list
     */
    enum ONSIDE hasSolderMasks();

    /** @return the key associated to sides used for some layers
     * No TopOnly BotOnly Both
     */
    const char* sideKeyValue( enum ONSIDE aValue );


private:
    BOARD* m_pcb;               // The board
    REPORTER* m_reporter;       // a reporter for messages (can be null)
    JOBFILE_PARAMS m_params;    // the list of various prms and data to write in a job file
    double m_conversionUnits;   // scaling factor to convert brd units to gerber units (mm)
};

#endif  //  #ifndef GERBER_JOBFILE_WRITER_H
