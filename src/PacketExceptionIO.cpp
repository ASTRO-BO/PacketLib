/***************************************************************************
                          PacketExceptionIO.cpp  -  description
                             -------------------
    begin                : Tue Jan 15 2002
    copyright            : (C) 2002 by Andrea Bulgarelli
    email                : bulgarelli@tesre.bo.cnr.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "PacketExceptionIO.h"

using namespace PacketLib;

//##ModelId=3AA649E902A2
PacketExceptionIO::PacketExceptionIO(const char* error) : PacketException(error)
{

}


//##ModelId=3AA649E902AC
PacketExceptionIO::~PacketExceptionIO()
{

}
