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
#include <iomanip>

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

		if(dimPrefix)
	        b0 = in->readByteStream(dimPrefix);
		else
			b0 = 0;
        if(b0 == 0 && dimPrefix != 0)
        {
            if(!in->isEOF())
                throw new PacketExceptionIO("it is impossible to read the prefix.");
            else
                return 0;
        }
        b1 = in->readByteStream(dimHeader);

#ifdef DEBUG
		std::cout << "b1 size: " << dimHeader << endl;
		std::cout << "b1 (header): " << endl;
		std::cout << std::internal << std::setfill('0');
		for(unsigned int i=0; i<dimHeader; i++)
			std::cout << std::hex << std::setw(2) << (int)b1->stream[i] << " ";
		std::cout << std::dec << std::endl;
#endif
        if(b1 == 0)
        {
            if(!in->isEOF())
                throw new PacketExceptionIO("it is impossible to read the header.");
            else
                return 0;
        }
        if(b1->size() != dimHeader)
        {
            if(b1->size() != 0)
                pindex = 0;
            else
                throw new PacketExceptionIO("it is impossible to read the full header.");
        }
        else
        {
            headerReference->setByteStream(b1);
            pl = headerReference->getPacketLength();
            b2 = in->readByteStream(pl);
#ifdef DEBUG
			std::cout << "b2 size: " << pl << endl;
			std::cout << "b2 (packet): " << endl;
			std::cout << std::internal << std::setfill('0');
			for(unsigned int i=0; i<pl; i++)
				std::cout << std::hex << std::setw(2) << (int)b2->stream[i] << " ";
			std::cout << std::dec << std::endl;
#endif
            if(b2 == 0)
            {
                if(!in->isEOF())
                    throw new PacketExceptionIO("it is impossible to read the data field.");
                else
                    return 0;
            }
            dim= b2->size();
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


		if(!p->decode(b0, b1, b2)) //gli stream diventano del packet
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




