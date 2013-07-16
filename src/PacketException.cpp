/***************************************************************************
                          PacketException.cpp  -  description
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

#include "PacketException.h"

using namespace PacketLib;

//##ModelId=3AA649E10191
PacketException::PacketException(const char* error, int code)
{
    this->error = new string(error);
    this->errorcode = code;
}


//##ModelId=3AA649E1019B
PacketException::~PacketException()
{
    delete error;
}


/** Read property of char* error. */
//##ModelId=3AA649E1019D
const char* PacketException::geterror()
{
    return error->c_str();
}


/** No descriptions */
//##ModelId=3AA649E1019F
void PacketException::add(const char* err)
{
    *error = err + *error;
}

int PacketException::geterrorcode() const {
  return errorcode;
}


    //##ModelId=3DEE784300CF
void PacketException::seterrorcode(int errorcode) {
  this->errorcode = errorcode;
}
