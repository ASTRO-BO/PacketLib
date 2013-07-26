/***************************************************************************
                          SocketServer.cpp  -  description
                             -------------------
    begin                : Thu May 16 2002
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

#include "SocketServer.h"
#include <errno.h>
#include <fcntl.h>

using namespace PacketLib;

//##ModelId=3DA3E6000230
SocketServer::SocketServer (bool bigendian, int port ) : Socket(bigendian)
{
    if ( ! create() )
    {
        throw PacketExceptionIO ( "Could not create server socket." );
    }

    if ( ! bind ( port ) )
    {
        throw PacketExceptionIO ( "Could not bind to port." );
    }
}


//##ModelId=3DA3E60001F5
SocketServer::SocketServer (bool bigendian) : Socket(bigendian)
{

};

//##ModelId=3DA3E6000262
SocketServer::~SocketServer()
{

}


//##ModelId=3DA3E6000264
bool SocketServer::bind ( const int port ) throw(PacketExceptionIO*)
{

    if ( ! is_valid() )
    {
        return false;
    }

    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = INADDR_ANY;
    m_addr.sin_port = htons ( port );

    int bind_return = ::bind ( m_sock,
                               ( struct sockaddr * ) &m_addr,
                               sizeof ( m_addr ) );

    if ( bind_return == -1 )
    {
        throw new PacketExceptionIO("SocketServer: bind return -1");
    }

    return true;
}


//##ModelId=3DA3E600029E
bool SocketServer::listen() const  throw(PacketExceptionIO*)
{
    if ( ! is_valid() )
    {
        return false;
    }

    int listen_return = ::listen ( m_sock, MAXCONNECTIONS );

    if ( listen_return == -1 )
    {
        throw new PacketExceptionIO("SocketServer: listen return -1.");
    }

    return true;
}


//##ModelId=3DA3E60002D0
bool SocketServer::accept ( SocketServer& new_socket ) throw(PacketExceptionIO*)
{
    int addr_length = sizeof ( m_addr );
    new_socket.m_sock = ::accept ( m_sock, ( sockaddr * ) &m_addr, ( socklen_t * ) &addr_length );

    if ( new_socket.m_sock <= 0 )
        throw new PacketExceptionIO("SocketServer: accept error.");
    else
        return true;
}


//##ModelId=3DA3E60002A0
void SocketServer::set_non_blocking ( const bool b )
{

    int opts;

    opts = fcntl ( m_sock,
                   F_GETFL );

    if ( opts < 0 )
    {
        return;
    }

    if ( b )
        opts = ( opts | O_NONBLOCK );
    else
        opts = ( opts & ~O_NONBLOCK );

    fcntl ( m_sock,
            F_SETFL,opts );

}
