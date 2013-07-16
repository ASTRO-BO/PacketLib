/***************************************************************************
                          Device.cpp  -  description
                             -------------------
    begin                : Mon Mar 4 2002
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

#include "Device.h"
using namespace PacketLib;
//##ModelId=3C87744002A0
Device::Device(bool bigendian)
{
    eof = true;
    closed = true;
    this->bigendian = bigendian;
}


//##ModelId=3DC552600182
bool Device::isBigEndian() const
{
    return bigendian;
}


/*Device::~Device(){
} */

//##ModelId=3C87744002A2
bool Device::isClosed() const
{
    return closed;
}


//##ModelId=3C87744002AB
bool Device::isEOF() const
{
    if(!closed)
        return eof;
    else
        return true;
}


/** Read property of bool endsession. */
//##ModelId=3ACCD75E031C
const bool& Device::getEndSession() const
{
    return endsession;
}


/** Write property of bool endsession. */
//##ModelId=3ACCD75E02EE
void Device::setEndSession( const bool& _newVal)
{
    endsession = _newVal;
}
