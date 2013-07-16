/***************************************************************************
                          PacketExceptionIO.h  -  description
                             -------------------
    begin                : Tue Jan 15 2002
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

#ifndef PACKETEXCEPTIONIO_H
#define PACKETEXCEPTIONIO_H

#include "PacketException.h"

namespace PacketLib {

//##ModelId=3C87743F0317
//##Documentation
//##	$Date: 2012/06/08 15:14:29 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/PacketExceptionIO.h,v 1.3 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Id: PacketExceptionIO.h,v 1.3 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Revision: 1.3 $
//##	\brief Exception class of the PacketLib. The error is an IO error.
class PacketExceptionIO : public PacketException
{
    public:

        //##ModelId=3AA649E902A2
        PacketExceptionIO(const char* error);

        //##ModelId=3AA649E902AC
        virtual ~PacketExceptionIO();
};

}
#endif
