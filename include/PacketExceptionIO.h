/***************************************************************************
                          PacketExceptionIO.h  -  description
                             -------------------
    begin                : Tue Jan 15 2002
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

#ifndef _PACKETEXCEPTIONIO_H
#define _PACKETEXCEPTIONIO_H

#include "PacketException.h"

namespace PacketLib
{

///	\brief Exception class of the PacketLib. The error is an IO error.
class PacketExceptionIO : public PacketException
{
public:

    PacketExceptionIO(const char* error);

    virtual ~PacketExceptionIO();
};

}
#endif
