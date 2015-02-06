/***************************************************************************
                          PacketNotRecognized.cpp  -  description
                             -------------------
    begin                : Mon Jan 21 2002
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

#include "PacketNotRecognized.h"
#include "PacketHeader.h"

using namespace PacketLib;

void PacketNotRecognized::createPacketType(pugi::xml_node node, int plPhysicalIndex, int plSize)
{
	packetID = 0;
	header->loadHeader(node, plPhysicalIndex, plSize);
	name = "Packet not Recognized\0";
}


bool PacketNotRecognized::createPacketType(char* fileName, bool prefix, word dimprefix) throw (PacketException*)
{
	packetID = 0;
    if(header->loadHeader(fileName))
    {
		name = "Packet not Recognized\0";
        return true;
    }
    else
    {
        PRINTDEBUG("ERROR: Packet header section not found");
        return false;
    }
}



PacketNotRecognized::PacketNotRecognized(bool bigendian) : Packet(bigendian)
{
    dataField->setPacketSourceDataField(0);
}


PacketNotRecognized::~PacketNotRecognized()
{
    //	cout << "PacketNotRecognized deleted" << endl;
}



bool PacketNotRecognized::setPacketValue(ByteStreamPtr prefix, ByteStreamPtr packetHeader, ByteStreamPtr packetDataField, int decodeType)
{
    /// It reads and sets the packet header 
    if(!header->setByteStream(packetHeader))
        return false;

    dataField->getPacketDataFieldHeader()->memByteStream(packetDataField);

    this->prefix = prefix;

    return true;
}
