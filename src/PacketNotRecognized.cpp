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


bool PacketNotRecognized::createPacketType(char* fileName, bool prefix, word dimprefix) throw (PacketException*)
{
	packetID = 0;
    if(header->loadHeader(fileName))
    {
        name = new char [22];
        name[0] = 'P';
        name[1] = 'a';
        name[2] = 'c';
        name[3] = 'k';
        name[4] = 'e';
        name[5] = 't';
        name[6] = ' ';
        name[7] = 'n';
        name[8] = 'o';
        name[9] = 't';
        name[10] = ' ';
        name[11] = 'R';
        name[12] = 'e';
        name[13] = 'c';
        name[14] = 'o';
        name[15] = 'g';
        name[16] = 'n';
        name[17] = 'i';
        name[18] = 'z';
        name[19] = 'e';
        name[20] = 'd';
        name[21] = '\0';
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
