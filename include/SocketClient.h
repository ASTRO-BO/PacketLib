/***************************************************************************
                          SocketClient.h  -  description
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


#ifndef _SOCKETCLIENT_H
#define _SOCKETCLIENT_H

#include "Socket.h"
#include "ByteStream.h"

namespace PacketLib
{

///	\brief This class represents generic client socket.
class SocketClient : public Socket
{
public:

    SocketClient ( bool bigendian, std::string host, int port );

};
}
#endif
