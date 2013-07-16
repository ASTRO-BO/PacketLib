/***************************************************************************
                          DataFieldHeader.h  -  description
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
#ifndef DataFieldHeader_h_h
#define DataFieldHeader_h_h

#include "PacketLibDefinition.h"
#include "PartOfPacket.h"

namespace PacketLib {

//##ModelId=3C0F6C1902E3
//##Documentation
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/DataFieldHeader.h,v 1.3 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: DataFieldHeader.h,v 1.3 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.3 $
//##	\brief This class represent the data field header of a packet
class DataFieldHeader : public PartOfPacket
{
    public:

      DataFieldHeader();

};

}
#endif
