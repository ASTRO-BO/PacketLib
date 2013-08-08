/***************************************************************************
                          Socket.h  -  description
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

#ifndef _SOCKET_H
#define _SOCKET_H

#include "Device.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include "ByteStream.h"
#include "PacketExceptionIO.h"

const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 5;
const int MAXRECV = 500;

namespace PacketLib
{

///	\brief This class represents generic socket.
class Socket : public Device
{
public:
    Socket(bool bigendian);

    virtual ~Socket();


    virtual bool is_valid() const
    {
        return m_sock != -1;
    }

    /// Data Transimission
    virtual bool send ( ByteStream* b ) const throw(PacketExceptionIO*) ;

    virtual ByteStream* recv (word dim, int & status) throw(PacketExceptionIO*) ;

    virtual bool connect ( const std::string host, const int port ) throw(PacketExceptionIO*);

    virtual bool create() throw(PacketExceptionIO*) ;

    virtual bool close() throw(PacketExceptionIO*);

protected:

    int m_sock;

    sockaddr_in m_addr;

};
}
#endif
