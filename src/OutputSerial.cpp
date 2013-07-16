/***************************************************************************
                          OutputSerial.cpp  -  description
                             -------------------
    begin                : Mon Apr 29 2002
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

#include "OutputSerial.h"

using namespace PacketLib;

//##ModelId=3DA3E57C02A8
OutputSerial::OutputSerial(bool bigendian) : Output(bigendian)
{
    serial = new Serial();
}


//##ModelId=3DA3E57C02DA
OutputSerial::~OutputSerial()
{
    delete serial;
}


//##ModelId=3DA3E57C02DC
void OutputSerial::close()  throw(PacketExceptionIO*)
{
    serial->close();
    isclosed = true;
}


//##ModelId=3DA3E57C0317
bool OutputSerial::open(char** parameters) throw(PacketExceptionIO*)
{
 	flag   = atoi( parameters[1] );
	device = parameters[0];
    	serial->open( device, flag );
    	isclosed = false;
    	return true;
}


//##ModelId=3DA3E57C0348
bool OutputSerial::writeByteStream(ByteStream* b) throw(PacketExceptionIO*)
{
    byte* buff = b->getStream();
    unsigned n_byte = b->getDimension();

    if(!isclosed)
    	 if( serial->write( buff, n_byte ) > 0 )
    	 	return true;
    	 else
	 		return false;
	else
		return false; 
}


//##ModelId=3DA3E57C0384
bool OutputSerial::writeString(const char* str) throw(PacketExceptionIO*)
{
 /*   if(!isclosed)
        file->writeString(str);
    else
        return false;
    isclosed = file->isClosed();*/
    return false;
}
