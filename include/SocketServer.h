/***************************************************************************
                          SocketServer.h  -  description
                             -------------------
    begin                : Thu May 16 2002
    copyright            : (C) 2002, 2013 by Andrea Bulgarelli
    email                : bulgarelli@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/

#ifndef _SOCKETSERVER_H
#define _SOCKETSERVER_H

#include "Socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>

namespace PacketLib
{

///	\brief This class represents generic client socket.
class SocketServer : public Socket
{
public:
    SocketServer (bool bigendian);
 
    SocketServer (bool bigendian,  int port );

    virtual ~SocketServer();

    bool bind ( const int port ) throw(PacketExceptionIO*);
    bool listen() const throw(PacketExceptionIO*);

    /// Client initialization

    void set_non_blocking ( const bool );

    bool accept ( SocketServer& ) throw(PacketExceptionIO*);

};
}
#endif
