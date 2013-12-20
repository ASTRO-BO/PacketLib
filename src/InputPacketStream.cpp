/***************************************************************************
                          InputPacketStream.cpp  -  description
                             -------------------
    begin                : Sun Oct 27 2002
    copyright            : (C) 2002, 2013 by Andrea Bulgarelli
    email                : bulgarelli@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "InputPacketStream.h"

using namespace PacketLib;


InputPacketStream::InputPacketStream() : PacketStream()
{
    in = 0;
}



InputPacketStream::InputPacketStream(const char* fileNameConfig) : PacketStream(fileNameConfig)
{
    in = 0;
}



InputPacketStream::~InputPacketStream()
{

}


int InputPacketStream::detPacketType(ByteStreamPtr prefix, ByteStreamPtr packetHeader, ByteStreamPtr packetDataField)
{
    ///  Iterate through list and output each element.
    ///  The packetType 0 is the packet not recognized
    for (int i = 1; i<numberOfPacketType; i++)
    {
        Packet* p = getPacketType(i);
        if(p->verifyPacketValue(prefix, packetHeader, packetDataField))
            return i;
    }
    return 0;
}



int InputPacketStream::detPacketType(ByteStreamPtr prefix, ByteStreamPtr packet)
{
    /// Iterate through list and output each element.
    /// The packetType 0 is the packet not recognized
    for (dword i = 1; i<numberOfPacketType; i++)
    {
        Packet* p = getPacketType(i);
        if(p->verifyPacketValue(prefix, packet))
            return i;
    }
    return 0;
}


int InputPacketStream::detPacketType(byte* packet)
{
    /// Iterate through list and output each element.
    /// The packetType 0 is the packet not recognized
    for (dword i = 1; i<numberOfPacketType; i++)
    {
        Packet* p = getPacketType(i);
        if(p->verifyPacketValue(packet))
            return i;
    }
    return 0;
}

void InputPacketStream::setInput(Input* in)
{
    this->in = in;
}



Packet* InputPacketStream::readPacket() throw(PacketExceptionIO*)
{
    unsigned dimHeader = getHeaderDimension();
    unsigned dimPrefix = getPrefixDimension();
    ByteStreamPtr b0, b1, b2;
    dword pl, dim, pindex;
    try
    {
        if(in == 0)
            throw new PacketExceptionIO("no input set.");
        b0 = in->readByteStream(dimPrefix);
        if(b0 == 0 && dimPrefix != 0)
        {
            if(!in->isEOF())
                throw new PacketExceptionIO("it is impossible to read the prefix.");
            else
                return 0;
        }
        b1 = in->readByteStream(dimHeader);
        if(b1 == 0)
        {
            if(!in->isEOF())
                throw new PacketExceptionIO("it is impossible to read the header.");
            else
                return 0;
        }
        if(b1->getDimension() != dimHeader)
        {
            if(b1->getDimension() != 0)
                pindex = 0;
            else
                throw new PacketExceptionIO("it is impossible to read the full header.");
        }
        else
        {
            headerReference->setByteStream(b1);
            pl = headerReference->getPacketLength();
            b2 = in->readByteStream(pl);
            if(b2 == 0)
            {
                if(!in->isEOF())
                    throw new PacketExceptionIO("it is impossible to read the data field.");
                else
                    return 0;
            }
            dim= b2->getDimension();
            if(dim != pl)
            {
                if(dim != 0)
                    pindex = 0;
                else
                    throw new PacketExceptionIO("it is impossible to read the full data field.");
            }
            else
                pindex = detPacketType(b0, b1, b2);
        }
        Packet* p = packetType[pindex];
        if(!p->setPacketValue(b0, b1, b2)) //gli stream diventano del packet
            throw new PacketExceptionIO("it is impossible to resolve the packet.");
        return p;
    }
    catch(PacketExceptionIO* e)
    {
        e->add(" - ");
        e->add("InputPacketStream::readPacket(): ");
        throw e;
    }
}

dword InputPacketStream::getPacketDimension(byte* stream) {
		dword dimPre = 0;
		if(prefix)
			dimPre += dimPrefix;
		//ByteStreamPtr prefix = new ByteStream(stream, dimPre, bigendian);

		dword dim = 0;
		dword dimHeader = headerReference->getDimension();
		dim += dimHeader;
		ByteStreamPtr tempHeader = ByteStreamPtr(new ByteStream());
		tempHeader->setStream(stream+dimPre, dimHeader, bigendian);
		headerReference->setByteStream(tempHeader);
		dim += headerReference->getPacketLength();
		return dim;
}

Packet* PacketLib::InputPacketStream::decodePacket(byte* stream) {

	int index = detPacketType(stream);
	if(index > 0) {
		Packet* p = getPacketType(index);
		p->setPacketValue(stream);
		return p;
	}
	else
		return 0;

}
