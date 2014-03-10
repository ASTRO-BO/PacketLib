/***************************************************************************
                          OutputPacketStream.h  -  description
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
 
#ifndef _OUTPUTPACKETSTREAM_H_H
#define _OUTPUTPACKETSTREAM_H_H

#include "PacketLibDefinition.h"
#include "PacketStream.h"
#include "Output.h"

namespace PacketLib
{

///	\brief This class represents generic output of strean if packet.
class OutputPacketStream : public PacketStream
{
public:

    OutputPacketStream();

    OutputPacketStream(const char* fileNameConfig);

    /// Generate the output ByteStream and write to the output.
    void writePacket(Packet* p) throw(PacketExceptionIO*);

    /// Write a ByteStream to the output.
    void writePacket(ByteStreamPtr bs) throw(PacketExceptionIO*);

    void setOutput(Output* out);

protected:

    Output* out;
};

}
#endif
