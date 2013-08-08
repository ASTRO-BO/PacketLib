/***************************************************************************
                          DataFieldHeader.h
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001, 2013 by Andrea Bulgarelli
    email                : bulgarelli@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/

#ifndef _DATAFIELDHEADER_H
#define _DATAFIELDHEADER_H

#include "PacketLibDefinition.h"
#include "PartOfPacket.h"

namespace PacketLib
{

///	\brief This class represent the data field header of a packet
class DataFieldHeader : public PartOfPacket
{
public:

    DataFieldHeader();

};

}
#endif
