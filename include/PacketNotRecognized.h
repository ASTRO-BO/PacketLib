/***************************************************************************
                          PacketNotRecognized.h  -  description
                             -------------------
    begin                : Mon Jan 21 2002
    copyright            : (C) 2002, 2013 by Andrea Bulgarelli
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

#ifndef _PACKETNOTRECOGNIZED_H
#define _PACKETNOTRECOGNIZED_H

#include "Packet.h"
#include "PacketLibDefinition.h"

namespace PacketLib
{

///	\brief Packet not recognized.
class PacketNotRecognized : public Packet
{
public:

    PacketNotRecognized(bool bigendian);

    virtual ~PacketNotRecognized();

    virtual bool createPacketType(char* fileName, bool prefix, word dimprefix) throw (PacketException*);

    virtual bool setPacketValue(ByteStreamPtr prefix, ByteStreamPtr packetHeader, ByteStreamPtr packetDataField);
};

}
#endif
