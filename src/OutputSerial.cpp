/***************************************************************************
                          OutputSerial.cpp  -  description
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

#include "OutputSerial.h"

using namespace PacketLib;


OutputSerial::OutputSerial(bool bigendian) : Output(bigendian)
{
    serial = new Serial();
}



OutputSerial::~OutputSerial()
{
    delete serial;
}



void OutputSerial::close()  throw(PacketExceptionIO*)
{
    serial->close();
    isclosed = true;
}



bool OutputSerial::open(char** parameters) throw(PacketExceptionIO*)
{
    flag   = atoi( parameters[1] );
    device = parameters[0];
    serial->open( device, flag );
    isclosed = false;
    return true;
}



bool OutputSerial::writeByteStream(ByteStreamPtr b) throw(PacketExceptionIO*)
{
    byte* buff = b->getStream();
    unsigned n_byte = b->size();

    if(!isclosed)
        if( serial->write( buff, n_byte ) > 0 )
            return true;
        else
            return false;
    else
        return false;
}



bool OutputSerial::writeString(const char* str) throw(PacketExceptionIO*)
{
    /*   if(!isclosed)
           file->writeString(str);
       else
           return false;
       isclosed = file->isClosed();*/
    return false;
}
