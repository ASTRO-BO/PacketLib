/***************************************************************************
                          PacketStream.h  -  description
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001, 2013 by Andrea Bulgarelli
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
 
#ifndef _PACKETSTREAM_H_H
#define _PACKETSTREAM_H_H

#include "PacketLibDefinition.h"
#include "Packet.h"
#include "PacketException.h"
#include "PlVersion.h"

namespace PacketLib
{

///	\brief Stream of byte with packets.
class PacketStream
{
public:

    PacketStream(const char* fileNameConfig) ;

    PacketStream();

    ~PacketStream();

    void setFileNameConfig(const char* f);

    /// This method creates the structure of the stream.
    /// The structure of the stream is represented with the pachetReference and the collection of type of packet.
    /// Each packet has the collection of field and the collection of identifier
    bool createStreamStructure() throw(PacketException*);

    /// Return a packet of index passed as parameters.
    Packet* getPacketType(int index);

    static char* packetLibVersion()
    {
        return (char*) "PacketLib version: 1.3.9 - June 2012";
    };

    bool isBigEndian();

    bool thereIsPrefix();

    word getNumberOfPacketType();

    /// Gets the dimension (in bytes) of the prefix of all the packets of the stream
    word getPrefixDimension() const;

    /// Gets the dimension (in bytes) of the header of all the packets of the stream
    word getHeaderDimension() const;

    PacketHeader* headerReference;

    char* filenameConfig;

    char* pathFileNameConfig;

protected:

    /// List of packet.
    Packet** packetType;

    /// Numbers of type of packet presents
    byte numberOfPacketType;

   /// Indicates if there is a prefix.
    bool prefix;

    /// Indicates if the machine is bigendian.
    bool bigendian;

    /// Indicates the dimension of prefix.
    word dimPrefix;
	
	/// The dimension of the header
	word dimHeader;

};

}
#endif
