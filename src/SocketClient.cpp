/***************************************************************************
                          SocketClient.cpp  -  description
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

#include "SocketClient.h"
#include "PacketExceptionIO.h"

using namespace PacketLib;


SocketClient::SocketClient ( bool bigendian, std::string host, int port ) : Socket(bigendian)
{
    if ( ! Socket::create() )
    {
        throw PacketExceptionIO ( "Could not create client socket." );
    }

    if ( ! Socket::connect ( host, port ) )
    {
        throw PacketExceptionIO ( "Could not bind to port." );
    }

}
