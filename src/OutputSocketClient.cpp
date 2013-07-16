/***************************************************************************
                          OutputSocket.cpp  -  description
                             -------------------
    begin                : Mon May 20 2002
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

#include "OutputSocketClient.h"

using namespace PacketLib;

//##ModelId=3DBFBFC001F5
OutputSocketClient::OutputSocketClient(bool bigendian) : Output(bigendian)
{
    socketclient = 0;
    host = 0;
}


//##ModelId=3DBFBFC00230
OutputSocketClient::~OutputSocketClient()
{
    delete socketclient;
    delete host;
}


//##ModelId=3DBFBFC00232
void OutputSocketClient::close() throw(PacketExceptionIO*)
{
    socketclient->close();
}


//##ModelId=3DBFBFC00262
bool OutputSocketClient::open(char** argv) throw(PacketExceptionIO*)
{
    host = argv[0];
    port = atoi(argv[1]);
    socketclient = new SocketClient(bigendian, host, port);
    isclosed = false;
    return true;
}


//##ModelId=3DBFBFC00265
bool OutputSocketClient::writeByteStream(ByteStream* b) throw(PacketExceptionIO*)
{
    if(!isclosed)
        socketclient->send(b);
    else
        return false;
    isclosed = socketclient->isClosed();
    return true;
}


//##ModelId=3DBFBFC00268
bool OutputSocketClient::writeString(const char* str) throw(PacketExceptionIO*)
{
    throw new PacketExceptionIO("Method not implemented");
}
