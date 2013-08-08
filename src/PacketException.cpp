/***************************************************************************
                          PacketException.cpp  -  description
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

#include "PacketException.h"

using namespace PacketLib;


PacketException::PacketException(const char* error, int code)
{
    this->error = new string(error);
    this->errorcode = code;
}



PacketException::~PacketException()
{
    delete error;
}


/// Read property of char* error. 
const char* PacketException::geterror()
{
    return error->c_str();
}



void PacketException::add(const char* err)
{
    *error = err + *error;
}

int PacketException::geterrorcode() const
{
    return errorcode;
}



void PacketException::seterrorcode(int errorcode)
{
    this->errorcode = errorcode;
}
