/***************************************************************************
                          PacketIdentifier.h  -  description
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
 
#ifndef _PACKETIDENTIFIER_H_H
#define _PACKETIDENTIFIER_H_H

#include "PacketLibDefinition.h"

namespace PacketLib
{

///	\brief Identifier of packet.
class PacketIdentifier
{
public:

    word fieldNumber;

    /// This field rappresent which list of fields read:
    /// \li 0 - List of fields of PacketHeader;
    /// \li 1 - List of fields of DataFieldHeader
    /// \li 2 - List of fields of SourceDataField
    byte type;

    word value;

    PacketIdentifier(int fn, byte t, word v);

    ~PacketIdentifier();

};

}
#endif
