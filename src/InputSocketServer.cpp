/***************************************************************************
                          InputSocketServer.cpp  -  description
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

#include "InputSocketServer.h"
#include <sstream>

using namespace PacketLib;


InputSocketServer::InputSocketServer(bool bg) : Input(bg)
{
    socketserver = 0;
    new_sock =  0;
}



InputSocketServer::~InputSocketServer()
{
    delete socketserver;
}


bool InputSocketServer::open( char** parameters ) throw(PacketExceptionIO*)
{
    port = atoi(parameters[0]);
    socketserver = new SocketServer(bigendian, port);

    new_sock = new SocketServer(bigendian);
    accepted = false;

    closed = false;
    return true;
}

void InputSocketServer::openDevice(const std::vector<std::string>& parameters) throw(PacketExceptionIO*)
{
	std::istringstream ss(parameters[0]);
	ss >> port;
    socketserver = new SocketServer(bigendian, port);

    new_sock = new SocketServer(bigendian);
    accepted = false;

    closed = false;
}

void InputSocketServer::close() throw(PacketExceptionIO*)
{
    socketserver->close();
    closed = true;
    accepted = false;
}



ByteStreamPtr InputSocketServer::readByteStream(dword n_byte) throw(PacketExceptionIO*)
{
    int status = 0;
    if(!accepted)
    {
        socketserver->listen();
        socketserver->accept ( *new_sock );
        accepted = true;
        eof = false;
    }

    ByteStreamPtr bl = new_sock->recv(n_byte, status);
    if(status == 0)
    {
        accepted = false;
        eof = true;
        return 0;
    }
    else
        return bl;
}



char* InputSocketServer::readString() throw(PacketExceptionIO*)
{
    throw new PacketExceptionIO("Method not implemented");
}
