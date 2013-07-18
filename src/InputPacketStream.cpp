/***************************************************************************
                          InputPacketStream.cpp  -  description
                             -------------------
    begin                : Sun Oct 27 2002
    copyright            : (C) 2002 by Andrea Bulgarelli
    email                : bulgarelli@tesre.bo.cnr.it
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

//##ModelId=3DA3E5730122
InputPacketStream::InputPacketStream() : PacketStream()
{
    in = 0;
}


//##ModelId=3DA3E57400AA
InputPacketStream::InputPacketStream(const char* fileNameConfig) : PacketStream(fileNameConfig)
{
    in = 0;
}


//##ModelId=3DA3E5740118
InputPacketStream::~InputPacketStream()
{

}


//##ModelId=3C3AB71401AE
int InputPacketStream::detPacketType(ByteStream* prefix, ByteStream* packetHeader, ByteStream* packetDataField)
{
    // Iterate through list and output each element.
    // Il packetType 0 e' il packet not recognized
    for (int i = 1; i<numberOfPacketType; i++)
    {
        Packet* p = getPacketType(i);
        if(p->verifyPacketValue(prefix, packetHeader, packetDataField))
            return i;
    }
    return 0;
}


//##ModelId=3DA3E57500D2
int InputPacketStream::detPacketType(ByteStream* prefix, ByteStream* packet)
{
    // Iterate through list and output each element.
    // Il packetType 0 e' il packet not recognized
    for (int i = 1; i<numberOfPacketType; i++)
    {
        Packet* p = getPacketType(i);
        if(p->verifyPacketValue(prefix, packet))
            return i;
    }
    return 0;
}


//##ModelId=3DBFBFBD03D4
void InputPacketStream::setInput(Input* in)
{
    this->in = in;
}


//##ModelId=3DBFBFBE00C8
Packet* InputPacketStream::readPacket() throw(PacketExceptionIO*)
{
    unsigned dimHeader = getHeaderDimension();
    unsigned dimPrefix = getPrefixDimension();
    ByteStream* b1 = 0, *b2 = 0, *b0 = 0;
    word pl, dim, pindex;
    try
    {
        if(in == 0)  
            throw new PacketExceptionIO("no input set.");
        b0 = in->readByteStream(dimPrefix);
        if(b0 == 0 && dimPrefix != 0) {
	    if(!in->isEOF())
            	throw new PacketExceptionIO("it is impossible to read the prefix.");
	    else
	    	return 0;
	}
        b1 = in->readByteStream(dimHeader);
        if(b1 == 0) {
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
            /*for(int i=0; i<7; i++) {
            Field* f = headerReference->getFields(i);
                    cout << f->name << endl;
                    cout << f->value << endl;

            } */
            pl = headerReference->getPacketLength();
            b2 = in->readByteStream(pl);
            if(b2 == 0) {
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
