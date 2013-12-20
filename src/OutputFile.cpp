/***************************************************************************
                          OutputFile.cpp  -  description
                             -------------------
    begin                : Mon Apr 29 2002
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

#include "OutputFile.h"

using namespace PacketLib;


OutputFile::OutputFile(bool bigendian) : Output(bigendian)
{
    file = new File(bigendian, 0);
}



OutputFile::~OutputFile()
{
    delete file;
}



void OutputFile::close()  throw(PacketExceptionIO*)
{
    file->close();
    isclosed = true;
}



bool OutputFile::open(char** parameters) throw(PacketExceptionIO*)
{
    file->open(parameters[0], "w");
    filename = parameters[0];
    isclosed = false;
    return true;
}



bool OutputFile::writeByteStream(ByteStreamPtr b) throw(PacketExceptionIO*)
{
    if(!isclosed)
        file->writeByteStream(b);
    else
        return false;
    isclosed = file->isClosed();
    return true;
}



bool OutputFile::writeString(const char* str) throw(PacketExceptionIO*)
{
    if(!isclosed)
        file->writeString(str);
    else
        return false;
    isclosed = file->isClosed();
    return true;
}
