/***************************************************************************
                          Socket.h  -  description
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

#ifndef SOCKET_H
#define SOCKET_H

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

namespace PacketLib {

//##ModelId=3EADC12400B5
//##Documentation
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/Socket.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: Socket.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.2 $
//##	\brief This class represents generic socket.
class Socket : public Device
{
    public:
        //##ModelId=3EADC14400C0
        Socket(bool bigendian);

        //##ModelId=3EADC14400C2
        virtual ~Socket();

        //##ModelId=3EADC14400C4

        virtual bool is_valid() const { return m_sock != -1; }

        //##ModelId=3EADC14400C8
				//##Documentation
				//## Data Transimission
        virtual bool send ( ByteStream* b ) const throw(PacketExceptionIO*) ;

        //##ModelId=3EADC14400CC
        virtual ByteStream* recv (word dim, int & status) throw(PacketExceptionIO*) ;

        //##ModelId=3EADC14400D0
        virtual bool connect ( const std::string host, const int port ) throw(PacketExceptionIO*);

        //##ModelId=3EADC14400D5
        virtual bool create() throw(PacketExceptionIO*) ;

        //##ModelId=3EADC14400D7
        virtual bool close() throw(PacketExceptionIO*);

    protected:

        //##ModelId=3EADC14400BC
        int m_sock;

        //##ModelId=3EADC14400BE
        sockaddr_in m_addr;

};
}
#endif
