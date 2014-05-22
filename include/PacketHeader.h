/***************************************************************************
                          PacketHeader.h  -  description
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
 
#ifndef _PACKETHEADER_H_H
#define _PACKETHEADER_H_H

#include "PacketLibDefinition.h"
#include "PartOfPacket.h"

namespace PacketLib
{

///	\brief Header of packet.
class PacketHeader : public PartOfPacket
{
public:

    PacketHeader();

    ~PacketHeader();

    /// Sets the name of packet header
    void setName(char* n)
    {
        name = n;
    };

    /// Loads data header from configuration file.
    bool loadHeader(char* fileName) throw(PacketException*);

    /// Returns the total lenght of "packet data field" (data field header plus source data field)
    dword getPacketLength();

    //set the length of the packet in the 'packet lenght' field (the "packet data field" dimension)
	//It is encoded as "data field dimension - 1
    void setPacketLength(dword dim);

    Field * getFieldWithPacketDimension();

    inline word sizeOfPacketLength()
    {
        return dimensionOfPacketLength;
    };

private:

    /// Packet name
    char* name;

    /// Numbers of fields into the header that contains the dimension of packet.
    word numberOfFieldWithPacketDimension;

    /// 16 or 32 bit
    word dimensionOfPacketLength;

};

}
#endif
