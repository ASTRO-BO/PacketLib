/***************************************************************************
                          SocketClient.h  -  description
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

// Definition of the SocketClient class

#ifndef SocketClient_class
#define SocketClient_class

#include "Socket.h"
#include "ByteStream.h"

namespace PacketLib {

//##ModelId=3EADC12400C3
//##Documentation
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/SocketClient.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: SocketClient.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.2 $
//##	\brief This class represents generic client socket.
class SocketClient : public Socket
{
    public:

        //##ModelId=3EADC14400E1
        SocketClient ( bool bigendian, std::string host, int port );

};
}
#endif
