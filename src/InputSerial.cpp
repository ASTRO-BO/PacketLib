/***************************************************************************
                          InputSerial.cpp  -  description
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

#include "InputSerial.h"
#include <sstream>

using namespace PacketLib;


InputSerial::InputSerial(bool bg) : Input(bg)
{
    serial = new Serial();
}



InputSerial::~InputSerial()
{
    delete serial;
}


bool InputSerial::open( char** parameters ) throw(PacketExceptionIO*)
{
    flag   = atoi( parameters[1] );
    device = parameters[0];
    //cout << "SSSSS: " << O_NONBLOCK << endl;
    serial->open((char*)device.c_str(), O_NONBLOCK);
    serial->dump();
    serial->close();
    serial->open((char*)device.c_str(), flag);
    closed = false;
    return true;
}

void InputSerial::openDevice(const std::vector<std::string>& parameters) throw(PacketExceptionIO*)
{
	std::istringstream ss(parameters[1]);
	ss >> flag;
    device = parameters[0];

    serial->open((char*)device.c_str(), O_NONBLOCK);
    serial->dump();
    serial->close();
    serial->open((char*)device.c_str(), flag);

    closed = false;
}


void InputSerial::close()  throw(PacketExceptionIO*)
{
    serial->close();
    closed = true;
}



ByteStreamPtr InputSerial::readByteStream(dword n_byte) throw(PacketExceptionIO*)
{
    //cout << "waiting " << n_byte << endl;
    ByteStreamPtr bs;
    byte* buff = new byte[n_byte];
    dword current = 0;
    if(!closed)
    {
        while(current != n_byte)
        {
            int readed = serial->read((void*) &buff[current], n_byte - current );
            //cout << "readed: " << readed << endl;
            current += readed;
            if( current  == 0 )
            {
                bs = ByteStreamPtr(new ByteStream(0, bigendian));
                break;
            }
        }
        if(current != 0)
            bs = ByteStreamPtr(new ByteStream(buff, n_byte, bigendian));
    }
    else
        return 0;

    //for(int i=0; i<n_byte; i++)
    //printf("%d: %x\n", i, buff[i]);

    if(bs->size() == 0)
        return 0;
    return bs;
}



char* InputSerial::readString() throw(PacketExceptionIO*)
{
    /*    char* c;
        if(!closed)
            c = file->getLine();
        else
            return 0;
        closed = file->isClosed();
        eof = file->isEOF();
        return c;
    */
    return 0;
}
