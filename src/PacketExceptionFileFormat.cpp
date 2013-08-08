/***************************************************************************
                          PacketExceptionFileFormat.cpp  -  description
                             -------------------
    begin                : Tue Jan 15 2002
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

#include "PacketExceptionFileFormat.h"

using namespace PacketLib;


PacketExceptionFileFormat::PacketExceptionFileFormat(const char* error) : PacketException(error)
{
}



PacketExceptionFileFormat::~PacketExceptionFileFormat()
{

}
