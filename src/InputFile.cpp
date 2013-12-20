/***************************************************************************
                          InputFile.cpp  -  description
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

#include "InputFile.h"

using namespace PacketLib;

InputFile::InputFile(bool bg) : Input(bg)
{
    file = new File(bg, 0);
}


InputFile::~InputFile()
{
    cout << "InputFile::~InputFile()" << endl;
    delete file;
}


bool InputFile::open( char** parameters ) throw(PacketExceptionIO*)
{
    file->open(parameters[0], (char*)"r");
    filename = parameters[0];
    closed = false;
    eof = file->isEOF();
    return true;
}


void InputFile::close()  throw(PacketExceptionIO*)
{
    file->close();
    closed = true;
}


ByteStreamPtr InputFile::readByteStream(dword n_byte) throw(PacketExceptionIO*)
{
    ByteStreamPtr bs;
    if(!closed)
        bs = file->getNByte(n_byte);
    else
        return 0;
    closed = file->isClosed();
    eof = file->isEOF();
    if(bs->getDimension() == 0) return 0;
    return bs;
}


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
