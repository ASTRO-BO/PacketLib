/***************************************************************************
                          PacketHeader.h  -  description
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001 by Andrea Bulgarelli
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
#ifndef PacketHeader_h_h
#define PacketHeader_h_h

#include "PacketLibDefinition.h"
#include "PartOfPacket.h"

namespace PacketLib {

//##ModelId=3C0F6C19035E
//##Documentation
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/PacketHeader.h,v 1.3 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: PacketHeader.h,v 1.3 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.3 $
//##	\brief Header of packet.
class PacketHeader : public PartOfPacket
{
    public:

        //##ModelId=3EADC13A0088
        PacketHeader();
    
        //##ModelId=3EADC13A0016
        ~PacketHeader();

        //##ModelId=3C0F6C1A01DC
        //##Documentation
        //## Sets the name of packet header
        void setName(char* n){ name = n;};

        //##ModelId=3C14980F00F2
        //##Documentation
        //## Loads data header from configuration file.
        bool loadHeader(char* fileName) throw(PacketException*);

        //##ModelId=3C15ED930064
        //##Documentation
        //## Returns the total lenght of packet data field (data field header plus source data field)
        word getPacketLength();

        //##ModelId=3EADC13A00BC
        Field * getFieldWithPacketDimension();

    private:

        //##ModelId=3EADC1390359
        //##Documentation
        //## Packet name
        char* name;

        //##Documentation
        //## Numbers of fields into the header that contains the dimension of packet.
        word numberOfFieldWithPacketDimension;

};

}
#endif
