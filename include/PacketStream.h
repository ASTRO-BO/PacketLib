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
	
	/// get a Packet* from a ByteStream
	/// \pre the prefix has been removed
	/// \param packet the stream that contains the source packet without the prefix
	/// \param decodeType (0) do not decode anything (1) decode only sections (prefix, header, data field header, source data field fixed part, source data field variable part) (2) decode blocks (all sections + all blocks of the ‘source data field variable part’)
    Packet* getPacket(ByteStreamPtr stream) throw(PacketException*);
	
	/// \return The index of packet type if it's recognized. 0 if packet isn't recognized.
    /// \param prefix A ByteStream that contains the prefix of packet (if present).
    /// \param packetHeader A ByteStream that contains the packet header.
    /// \param packetDataField A ByteStream that contains the packet data field.
    int detPacketType(ByteStreamPtr prefix, ByteStreamPtr packetHeader, ByteStreamPtr packetDataField);
	
    /// \return The index of packet type if it's recognized. 0 if packet isn't recognized.
    /// \param prefix A ByteStream that contains the prefix of packet (if present).
    /// \param packet A ByteStream that contains the packet.
    int detPacketType(ByteStreamPtr prefix, ByteStreamPtr packet);
	
    ///It returns the index of the packet type contained in the stream. The stream* contains also the prefix (if present)
    /// \return The index of packet type if it's recognized. 0 if packet isn't recognized.
    /// \param packet A ByteStream pointer that contains the packet.
    int detPacketType(ByteStreamPtr packet);
	
	///It returns the total dimension of the packet contained in the stream (without prefix). The stream* contains also the prefix (if present)
	///\param The stream with the prefix (if present)
    dword getPacketDimension(ByteStreamPtr stream);

    void setFileNameConfig(const char* f);

    /// This method creates the structure of the stream.
    /// The structure of the stream is represented with the pachetReference and the collection of type of packet.
    /// Each packet has the collection of field and the collection of identifier
    bool createStreamStructure() throw(PacketException*);

    /// Return a packet of index passed as parameters.
    Packet* getPacketType(int index);

    static char* packetLibVersion()
    {
        return (char*) "PacketLib version: 3.4.0 - June 2012";
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
