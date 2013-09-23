/***************************************************************************
                          InputSocketServer.h  -  description
                             -------------------
    begin                : Sat Oct 26 2002
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

#ifndef _INPUTSOCKET_H
#define _INPUTSOCKET_H

#include "Input.h"
#include "PacketExceptionIO.h"
#include "SocketServer.h"

namespace PacketLib
{

///	\brief This class represent a Socket Server input for IO system.
class InputSocketServer : public Input
{
public:
    InputSocketServer(bool bigendian);

    ~InputSocketServer();

    virtual bool open( char** parameters ) throw(PacketExceptionIO*);

    virtual void close() throw(PacketExceptionIO*);

    virtual ByteStream* readByteStream(dword n_byte) throw(PacketExceptionIO*);


    virtual char* readString() throw(PacketExceptionIO*);

    virtual int getType()
    {
        return 1;
    };

protected:

    SocketServer* socketserver;

    int port;

    bool accepted;

private:

    SocketServer* new_sock;

};
}
#endif
