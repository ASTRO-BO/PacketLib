/***************************************************************************
                          InputSocket.h  -  description
                             -------------------
    begin                : Sat Oct 26 2002
    copyright            : (C) 2002 by Andrea Bulgarelli
    email                : bulgarelli@bo.iasf.cnr.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/

#ifndef INPUTSOCKET_H
#define INPUTSOCKET_H

#include "Input.h"
#include "PacketExceptionIO.h"
#include "SocketServer.h"

namespace PacketLib
{

//##ModelId=3EADC1220343
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/InputSocketServer.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: InputSocketServer.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.2 $
//##	\brief This class represent a Socket Server input for IO system.
class InputSocketServer : public Input
{
public:
    //##ModelId=3EADC1290227
    InputSocketServer(bool bigendian);

    //##ModelId=3EADC129022D
    ~InputSocketServer();

    //##ModelId=3EADC129022E
    virtual bool open( char** parameters ) throw(PacketExceptionIO*);

    //##ModelId=3EADC1290235
    virtual void close() throw(PacketExceptionIO*);

    //##ModelId=3EADC1290237
    virtual ByteStream* readByteStream(int n_byte) throw(PacketExceptionIO*);

    //##ModelId=3EADC129023E
    virtual char* readString() throw(PacketExceptionIO*);

    //##ModelId=3EADC1290240
    virtual int getType()
    {
        return 1;
    };

protected:

    //##ModelId=3EADC1290208
    SocketServer* socketserver;

    //##ModelId=3EADC1290211
    int port;

    //##ModelId=3EADC1290217
    bool accepted;

private:

    //##ModelId=3EADC129021D
    SocketServer* new_sock;

};
}
#endif
