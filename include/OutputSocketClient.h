/***************************************************************************
                          OutputSocketClient.h  -  description
                             -------------------
    begin                : Mon May 20 2002
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

#ifndef OUTPUTSOCKET_H
#define OUTPUTSOCKET_H

#include "Output.h"
#include "SocketClient.h"

namespace PacketLib {

//##ModelId=3EADC12300AB
//##Documentation
//##	$Date: 2012/06/08 15:14:29 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/OutputSocketClient.h,v 1.3 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Id: OutputSocketClient.h,v 1.3 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Revision: 1.3 $
//##	\brief This class represents generic type of output. The output must be a file.
class OutputSocketClient : public Output
{
    public:

        //##ModelId=3EADC12A0305
        OutputSocketClient(bool bigendian);

        //##ModelId=3EADC12A0309
        virtual ~OutputSocketClient();

        //##ModelId=3EADC12A030B
        virtual void close() throw(PacketExceptionIO*);

        //##ModelId=3EADC12A030E
        virtual bool open(char** parameters) throw(PacketExceptionIO*);

        //##ModelId=3EADC12A0314
        virtual bool writeByteStream(ByteStream* b) throw(PacketExceptionIO*);

        //##ModelId=3EADC12A031A
        virtual bool writeString(const char* str) throw(PacketExceptionIO*);

        //##ModelId=3EADC12A0320
        virtual int getType() { return 2; };

    protected:

	//##ModelId=3EADC12A02F1
        SocketClient* socketclient;

        //##ModelId=3EADC12A02F9
        char* host;

        //##ModelId=3EADC12A02FF
        int port;
};

}
#endif
