/***************************************************************************
                          PacketIdentifier.h  -  description
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
#ifndef PacketIdentifier_h_h
#define PacketIdentifier_h_h

#include "PacketLibDefinition.h"

namespace PacketLib {

//##ModelId=3C0F6C190364
//##Documentation
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/PacketIdentifier.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: PacketIdentifier.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.2 $
//##	\brief Identifier of packet.
class PacketIdentifier
{
    public:

	//##ModelId=3EADC13A0178
        word fieldNumber;

        //##ModelId=3C0F6C1A01EC
        //##Documentation
        //## This field rappresent which list of fields read:
        //## \li 0 - List of fields of PacketHeader;
        //## \li 1 - List of fields of DataFieldHeader
        //## \li 2 - List of fields of SourceDataField
        byte type;

	//##ModelId=3EADC13A0199
        word value;

        //##ModelId=3C18775100C8
        PacketIdentifier(int fn, byte t, word v);

        //##ModelId=3EADC13A01FC
        ~PacketIdentifier();

};

}
#endif
