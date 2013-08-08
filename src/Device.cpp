/***************************************************************************
                          Device.cpp  -  description
                             -------------------
    begin                : Mon Mar 4 2002
    copyright            : (C) 2002, 2013 by Andrea Bulgarelli
    email                : bulgarelli@iasfbo.inaf.it
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

Device::Device(bool bigendian)
{
    eof = true;
    closed = true;
    this->bigendian = bigendian;
}

bool Device::isBigEndian() const
{
    return bigendian;
}


/*Device::~Device(){
} */

bool Device::isClosed() const
{
    return closed;
}


bool Device::isEOF() const
{
    if(!closed)
        return eof;
    else
        return true;
}


/// Read property of bool endsession. 
const bool& Device::getEndSession() const
{
    return endsession;
}


/// Write property of bool endsession.
void Device::setEndSession( const bool& _newVal)
{
    endsession = _newVal;
}
