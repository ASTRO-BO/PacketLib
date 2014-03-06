/***************************************************************************
                          InputPacketStream.h  -  description
                             -------------------
    begin                : Sun Oct 27 2002
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

#ifndef _INPUTPACKETSTREAM_H
#define _INPUTPACKETSTREAM_H

#include "PacketStream.h"
#include "Input.h"
#include "PacketExceptionIO.h"

namespace PacketLib
{

/// \brief This class represents the stream of byte in input that contains the packets. The input object must be deleted by its creator.
class InputPacketStream : public PacketStream
{
public:

    InputPacketStream();

    InputPacketStream(const char* fileNameConfig);

    ~InputPacketStream();

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

    /// This method sets the generic input of the stream
    /// \param in An input.
    void setInput(Input* in);

    /// This method read a telemetry packet
    /// \pre The setInput method must be invocated
    /// \param bDecode if true decode the method will decode the data fields.
    /// \return A pointer telemetry packet. Make attention: the object returned is one of the TM packet object of the array of this object. Don't delete it!
    Packet* readPacket(int decodeType = 2) throw(PacketExceptionIO*);

	/// get a Packet* from a ByteStream
	/// \pre the prefix has been removed
	/// \param packet the stream that contains the source packet without the prefix
	/// \param decodeType (0) do not decode anything (1) decode only sections (prefix, header, data field header, source data field fixed part, source data field variable part) (2) decode blocks (all sections + all blocks of the ‘source data field variable part’)
    Packet* getPacket(ByteStreamPtr packet, int decodeType = 2) throw(PacketException*);

protected:

    Input* in;

};

}
#endif
