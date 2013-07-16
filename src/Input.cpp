/***************************************************************************
                          Input.cpp  -  description
                             -------------------
    begin                : Sat Oct 26 2002
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

#include "Input.h"

using namespace PacketLib;

//##ModelId=3DBFBFBC01EB
Input::Input(bool bigendian)
{
    eof = true;
    closed = true;
    this->bigendian = bigendian;
}


//##ModelId=3DBFBFBC01ED
Input::~Input()
{

}


//##ModelId=3DBFBFBC025B
bool Input::isClosed()
{
    return closed;
}


//##ModelId=3DBFBFBC025D
bool Input::isEOF()
{
    if( closed)
        return true;
    else
        return eof;
}


//##ModelId=3DBFBFBC025F
bool Input::isBigendian()
{
    return bigendian;
}
