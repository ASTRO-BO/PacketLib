/***************************************************************************
                          Socket.cpp  -  description
                             -------------------
    begin                : Thu May 16 2002
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

#include "Socket.h"

#include "Socket.h"
#include "PacketLibDemo.h"
#include "string.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>

using namespace PacketLib;


Socket::Socket(bool bigendian) : Device(bigendian),  m_sock ( -1 )
{

    memset ( &m_addr, 0, sizeof ( m_addr ) );

}



Socket::~Socket()
{
    if ( is_valid() )
        ::close ( m_sock );
}



bool Socket::create() throw(PacketExceptionIO*)
{
    m_sock = socket ( AF_INET,
                      SOCK_STREAM,
                      0 );
    closed = false;
    if ( ! is_valid() )
        throw new PacketExceptionIO("Socket: it is impossible to create a socket");

    // TIME_WAIT - argh
    int on = 1;
    if ( setsockopt ( m_sock, SOL_SOCKET, SO_REUSEADDR, ( const char* ) &on, sizeof ( on ) ) == -1 )
        throw new PacketExceptionIO("Socket: it is impossible to create a socket");

    return true;

}



bool Socket::close() throw(PacketExceptionIO*)
{

    ::close(m_sock);
    closed = true;
    return true;

}



bool Socket::send ( ByteStreamPtr b ) const throw(PacketExceptionIO*)
{
    byte* stream = b->getOutputStream();
    //MSG_NOSIGNAL
    int status = ::send ( m_sock, stream, b->size(),  MSG_DONTROUTE);
    b->endOutputStream();
    if ( status == -1 )
    {
        throw new PacketExceptionIO("Socket: no send data");
    }
    else
    {
        return true;
    }
}



ByteStreamPtr Socket::recv (word dim, int & status ) throw(PacketExceptionIO*)
{
    //ByteStreamPtr b = new ByteStream(dim, bigendian);
    byte* stream = (byte*) new byte[dim];
    /*byte* temp = (byte*) new byte[1];
    int i;
    for(i=0; i< dim; i++)
    {
        status = ::recv ( m_sock, temp, 1, 0 );
          stream[i] = *temp;
    } */

    status = ::recv ( m_sock, stream, dim, 0 );

    /*if(!bigendian)
    {
        word dim =  b->size();
        for(word i = 0; i< dim; i+=2) {
            if((dim - i) != 1) { //per dimensioni dispari
                byte btemp = b->stream[i];
            b->stream[i] = b->stream[i+1];
          b->stream[i+1] = btemp;
            }
        }
    } */

    if ( status == -1 )
    {
        throw new PacketExceptionIO("Socket: no recv data - status = -1");
//        std::cout << "status == -1   errno == " << errno << "  in Socket::recv\n";
    }
    else if ( status == 0 )
    {
        throw new PacketExceptionIO("Socket: no recv data - status = 0");
    }
    else
    {
        ByteStreamPtr b = ByteStreamPtr(new ByteStream(stream, dim, bigendian, false));
        return b;
    }

}


//##ModelId=3DA3E60000E6
bool Socket::connect ( const std::string host, const int port ) throw(PacketExceptionIO*)
{
    DEMORET0;
    if ( ! is_valid() )
        throw new PacketExceptionIO("Socket connect: socket not valid");

    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons ( port );

    int status = inet_pton ( AF_INET, host.c_str(), &m_addr.sin_addr );

    if ( errno == EAFNOSUPPORT )
        throw new PacketExceptionIO("Socket connect: EAFNOSUPPORT error");

    status = ::connect ( m_sock, ( sockaddr * ) &m_addr, sizeof ( m_addr ) );

    if ( status == 0 )
        return true;
    else
        throw new PacketExceptionIO("Socket connect: status = 0");
}
