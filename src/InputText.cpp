/***************************************************************************
                          InputText.cpp  -  description
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

#include "InputText.h"

using namespace PacketLib;


InputText::InputText()
{
    eof = true;
    closed = true;
}



InputText::~InputText()
{
}



bool InputText::isClosed()
{
    return closed;
}



bool InputText::isEOF()
{
    if( closed)
        return true;
    else
        return eof;
}
