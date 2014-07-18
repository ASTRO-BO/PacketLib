/***************************************************************************
                          OutputSocketClient.cpp  -  description
                             -------------------
    begin                : Mon May 20 2002
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

#include "OutputSocketClient.h"
#include <sstream>

using namespace PacketLib;


OutputSocketClient::OutputSocketClient(bool bigendian) : Output(bigendian), host("")
{
    socketclient = 0;
}



OutputSocketClient::~OutputSocketClient()
{
    delete socketclient;
}


void OutputSocketClient::close() throw(PacketExceptionIO*)
{
    socketclient->close();
}


bool OutputSocketClient::open(char** argv) throw(PacketExceptionIO*)
{
    host = argv[0];
    port = atoi(argv[1]);
    socketclient = new SocketClient(bigendian, host, port);
    isclosed = false;
    return true;
}

void OutputSocketClient::openDevice(const std::vector<std::string>& parameters) throw(PacketExceptionIO*)
{
    host = parameters[0];
	std::istringstream ss(parameters[1]);
	ss >> port;
    socketclient = new SocketClient(bigendian, host, port);
    isclosed = false;
}

bool OutputSocketClient::writeByteStream(ByteStreamPtr b) throw(PacketExceptionIO*)
{
    if(!isclosed)
        socketclient->send(b);
    else
        return false;
    isclosed = socketclient->isClosed();
    return true;
}



bool OutputSocketClient::writeString(const char* str) throw(PacketExceptionIO*)
{
    throw new PacketExceptionIO("Method not implemented");
}
