/***************************************************************************
                          PacketStream.h  -  description
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001 by Andrea Bulgarelli
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
#ifndef PacketStream_h_h
#define PacketStream_h_h

#include "PacketLibDefinition.h"
#include "Packet.h"
#include "PacketException.h"
#include "PlVersion.h"

namespace PacketLib {

//##ModelId=3C0F6C19036A
//##Documentation
//##	$Date: 2012/06/08 15:14:29 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/PacketStream.h,v 1.16 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Id: PacketStream.h,v 1.16 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Revision: 1.16 $
//##	\brief Stream of byte with packets.
class PacketStream
{
    public:

        //##ModelId=3EADC13A0371
        PacketStream(const char* fileNameConfig) ;

        //##ModelId=3EADC13A03D1
        PacketStream();

        //##ModelId=3EADC13B0004
        ~PacketStream();

        //##ModelId=3EADC13B0020
        void setFileNameConfig(const char* f);

        //##ModelId=3EADC13B0085
        //##Documentation
        //## This method creates the structure of the stream.
        //## The structure of the stream is represented with the pachetReference and the collection of type of packet.
        //## Each packet has the collection of field and the collection of identifier
        bool createStreamStructure() throw(PacketException*);

        //##ModelId=3EADC13B00A5
        //##Documentation
        //## Return a packet of index passed as parameters.
        Packet* getPacketType(int index);

        //##ModelId=3EADC13B0111
        static char* packetLibVersion() {
			    return (char*) "PacketLib version: 1.3.9 - June 2012";
				};

        //##ModelId=3EADC13B0143
        bool isBigEndian();

        //##ModelId=3EADC13B0164
        bool thereIsPrefix();

        //##ModelId=3EADC13B0187
        word getNumberOfPacketType();

        //##ModelId=3EADC13B01AA
        //##Documentation
        //## Gets the dimension (in bytes) of the prefix of all the packets of the stream
        word getPrefixDimension() const;

        //##ModelId=3EADC13B01E2
        //##Documentation
        //## Gets the dimension (in bytes) of the header of all the packets of the stream
        word getHeaderDimension() const;

	//##ModelId=3EADC13A0243
        PacketHeader* headerReference;

        //##ModelId=3EADC13A024F
        char* filenameConfig;
	
	char* pathFileNameConfig;

    protected:

	//##ModelId=3EADC13A0283
        //##Documentation
        //## List of packet.
        Packet** packetType;

        //##ModelId=3EADC13A0292
        //##Documentation
        //## Numbers of type of packet presents
        byte numberOfPacketType;

        //##ModelId=3EADC13A02D5
        //##Documentation
        //## Indicates if there is a prefix.
        bool prefix;

        //##ModelId=3EADC13A0319
        //##Documentation
        //## Indicates if the machine is bigendian.
        bool bigendian;

	//##ModelId=3EADC13A0360
        //##Documentation
        //## Indicates the dimension of prefix.
        word dimPrefix;

};

}
#endif
