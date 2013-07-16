/***************************************************************************
                          InputText.cpp  -  description
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

#include "InputText.h"

using namespace PacketLib;

//##ModelId=3AA6490E015C
InputText::InputText()
{
    eof = true;
    closed = true;
}


//##ModelId=3AA6490E016F
InputText::~InputText()
{
}


//##ModelId=3DC55A8F0075
bool InputText::isClosed()
{
    return closed;
}


//##ModelId=3DC55A8F00E8
bool InputText::isEOF()
{
    if( closed)
        return true;
    else
        return eof;
}
