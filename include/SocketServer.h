/***************************************************************************
                          SocketServer.h  -  description
                             -------------------
    begin                : Thu May 16 2002
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

#ifndef SocketServer_class
#define SocketServer_class

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

//##ModelId=3EADC12400D3
//##Documentation
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/SocketServer.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: SocketServer.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.2 $
//##	\brief This class represents generic client socket.
class SocketServer : public Socket
{
public:
    //##ModelId=3EADC14400F1
    SocketServer (bool bigendian);
    //##ModelId=3EADC14400F5
    SocketServer (bool bigendian,  int port );

    //##ModelId=3EADC14400FC
    virtual ~SocketServer();

    //##ModelId=3EADC14400FE
    bool bind ( const int port ) throw(PacketExceptionIO*);
    //##ModelId=3EADC1440103
    bool listen() const throw(PacketExceptionIO*);

    // Client initialization

    //##ModelId=3EADC1440106
    void set_non_blocking ( const bool );

    //##ModelId=3EADC1440109
    bool accept ( SocketServer& ) throw(PacketExceptionIO*);

};
}
#endif
