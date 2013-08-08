/***************************************************************************
                          Input.cpp  -  description
                             -------------------
    begin                : Sat Oct 26 2002
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

#include "Input.h"

using namespace PacketLib;

Input::Input(bool bigendian)
{
    eof = true;
    closed = true;
    this->bigendian = bigendian;
}


Input::~Input()
{

}


bool Input::isClosed()
{
    return closed;
}


bool Input::isEOF()
{
    if( closed)
        return true;
    else
        return eof;
}


bool Input::isBigendian()
{
    return bigendian;
}
