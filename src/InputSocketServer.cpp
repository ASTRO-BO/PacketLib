/***************************************************************************
                          InputSocket.cpp  -  description
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

#include "InputSocketServer.h"

using namespace PacketLib;

//##ModelId=3DBFBFBF00B9
InputSocketServer::InputSocketServer(bool bg) : Input(bg)
{
    socketserver = 0;
    new_sock =  0;
}


//##ModelId=3DBFBFBF00BB
InputSocketServer::~InputSocketServer()
{
    delete socketserver;
}


//##ModelId=3DBFBFBF00F0
bool InputSocketServer::open( char** parameters ) throw(PacketExceptionIO*)
{
    port = atoi(parameters[0]);
    socketserver = new SocketServer(bigendian, port);

    new_sock = new SocketServer(bigendian);
    accepted = false;

    closed = false;
    return true;
}


//##ModelId=3DBFBFBF00F3
void InputSocketServer::close() throw(PacketExceptionIO*)
{
    socketserver->close();
    closed = true;
    accepted = false;
}


//##ModelId=3DBFBFBF00F5
ByteStream* InputSocketServer::readByteStream(int n_byte) throw(PacketExceptionIO*)
{
    int status = 0;
    if(!accepted)
    {
        socketserver->listen();
        socketserver->accept ( *new_sock );
        accepted = true;
        eof = false;
    }

    ByteStream* bl = new_sock->recv(n_byte, status);
    if(status == 0)
    {
        accepted = false;
        eof = true;
        return 0;
    }
    else
        return bl;
}


//##ModelId=3DBFBFBF0122
char* InputSocketServer::readString() throw(PacketExceptionIO*)
{
    throw new PacketExceptionIO("Method not implemented");
}
