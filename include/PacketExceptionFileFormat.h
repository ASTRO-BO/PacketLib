/***************************************************************************
                          PacketExceptionFileFormat.h  -  description
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

#ifndef PACKETEXCEPTIONFILEFORMAT_H
#define PACKETEXCEPTIONFILEFORMAT_H

#include "PacketException.h"

namespace PacketLib
{

//##ModelId=3C87743F030D
//##Documentation
//##	$Date: 2012/06/08 15:14:29 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/PacketExceptionFileFormat.h,v 1.3 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Id: PacketExceptionFileFormat.h,v 1.3 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Revision: 1.3 $
//##	\brief Exception class of the PacketLib. The error is the bad file format of the configuration files.
class PacketExceptionFileFormat : public PacketException
{
public:

    //##ModelId=3AA649E50210
    PacketExceptionFileFormat(const char* error);

    //##ModelId=3AA649E50219
    virtual ~PacketExceptionFileFormat();
};

}
#endif
