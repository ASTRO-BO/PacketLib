/***************************************************************************
                          InputFile.cpp  -  description
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

#include "InputFile.h"

using namespace PacketLib;

//##ModelId=3DBFBFBD00D2
InputFile::InputFile(bool bg) : Input(bg)
{
    file = new File(bg, 0);
}


//##ModelId=3DBFBFBD00D4
InputFile::~InputFile()
{
    cout << "InputFile::~InputFile()" << endl;
    delete file;
}


//##ModelId=3DBFBFBD00D5
bool InputFile::open( char** parameters ) throw(PacketExceptionIO*)
{
    file->open(parameters[0], (char*)"r");
    filename = parameters[0];
    closed = false;
    eof = file->isEOF();
    return true;
}


//##ModelId=3DBFBFBD00D8
void InputFile::close()  throw(PacketExceptionIO*)
{
    file->close();
    closed = true;
}


//##ModelId=3DBFBFBD0104
ByteStream* InputFile::readByteStream(int n_byte) throw(PacketExceptionIO*)
{
    ByteStream* bs;
    if(!closed)
        bs = file->getNByte(n_byte);
    else
        return 0;
    closed = file->isClosed();
    eof = file->isEOF();
    if(bs->getDimension() == 0) return 0;
    return bs;
}


//##ModelId=3DBFBFBD0107
char* InputFile::readString() throw(PacketExceptionIO*)
{
    char* c;
    if(!closed)
        c = file->getLine();
    else
        return 0;
    closed = file->isClosed();
    eof = file->isEOF();
    return c;
}
