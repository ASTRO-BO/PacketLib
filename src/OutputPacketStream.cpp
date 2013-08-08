/***************************************************************************
                          OutputPacketStream.cpp  -  description
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
 
#include "OutputPacketStream.h"

using namespace PacketLib;


OutputPacketStream::OutputPacketStream() : PacketStream()
{
    out = 0;
}



OutputPacketStream::OutputPacketStream(const char* fileNameConfig) : PacketStream(fileNameConfig)
{
    out = 0;
}


bool OutputPacketStream::writePacket(Packet* p) throw(PacketExceptionIO*)
{
    ByteStream* bs;
    try
    {
        bs = p->getOutputStream();
        if(out == 0)
            throw new PacketExceptionIO("No output set..");
        out->writeByteStream(bs);
        delete bs;
        return true;
    }
    catch(PacketExceptionIO* e)
    {
        e->add(" - ");
        e->add("OutputPacketStream::writePacket");
        throw e;
    }
}



void OutputPacketStream::setOutput(Output* out)
{
    this->out = out;
}
