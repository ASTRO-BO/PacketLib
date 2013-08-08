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

    /// \return The index of packet type if it's recognized. 0 if packet isn't recogniezed.
    /// \param prefix A ByteStream that contains the prefix of packet (if present).
    /// \param packetHeader A ByteStream that contains the packet header.
    /// \param packetDataField A ByteStream that contains the packet data field.
    int detPacketType(ByteStream* prefix, ByteStream* packetHeader, ByteStream* packetDataField);

   /// \return The index of packet type if it's recognized. 0 if packet isn't recogniezed.
    /// \param prefix A ByteStream that contains the prefix of packet (if present).
    /// \param packet A ByteStream that contains the packet.
    int detPacketType(ByteStream* prefix, ByteStream* packet);

    /// This method sets the generic input of the stream
    /// \param in An input.
    void setInput(Input* in);

    /// This method read a telemetry packet
    /// \pre The setInput method must be invocated
    /// \return A pointer telemetry packet. Make attention: the object returned is one of the TM packet object of the array of this object. Don't delete it!
    Packet* readPacket() throw(PacketExceptionIO*);

protected:

    Input* in;

};

}
#endif
