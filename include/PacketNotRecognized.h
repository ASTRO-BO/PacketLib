/***************************************************************************
                          PacketNotRecognized.h  -  description
                             -------------------
    begin                : Mon Jan 21 2002
    copyright            : (C) 2002 by Andrea Bulgarelli
    email                : bulgarelli@bo.iasf.cnr.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *             
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/

#ifndef PACKETNOTRECOGNIZED_H
#define PACKETNOTRECOGNIZED_H

#include "Packet.h"
#include "PacketLibDefinition.h"

namespace PacketLib {

//##ModelId=3C87743F0349
//##Documentation
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/PacketNotRecognized.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: PacketNotRecognized.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.2 $
//##	\brief Packet not recognized.
class PacketNotRecognized : public Packet
{
    public:

        //##ModelId=3AA64A03005A
        PacketNotRecognized(bool bigendian);

        //##ModelId=3AA64A03005B
        virtual ~PacketNotRecognized();

        //##ModelId=3AA64A03005D
        virtual bool createPacketType(char* fileName, bool prefix, word dimprefix) throw (PacketException*);

        //##ModelId=3AA64A030065
        virtual bool setPacketValue(ByteStream* prefix, ByteStream* packetHeader, ByteStream* packetDataField);
};

}
#endif
