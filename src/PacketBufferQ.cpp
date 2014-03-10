/***************************************************************************
 PacketBufferQ.cpp  -  A FIFO buffer class for Packets
 -------------------
    copyright            : (C) 2013-2014 Andrea Zoli
    email                : zoli@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/
#include "Packet.h"
#include "PacketBufferQ.h"
#include "InputFile.h"

namespace PacketLib
{

PacketBufferQ::PacketBufferQ(const string& configFile, const string& inputFile)
{
	_ips = new InputPacketStream(configFile.c_str());
	_ips->createStreamStructure();
	_in = (Input*) new InputFile(_ips->isBigEndian());
	char** param = new char*[2];
	param[0] = (char*) inputFile.c_str();
	param[1] = 0;
	_in->open(param);
	_ips->setInput(_in);
	delete param;
}

PacketBufferQ::~PacketBufferQ()
{
	delete _ips;

	if(_in)
		_in->close();
}

void PacketBufferQ::load()
{
	ByteStreamPtr packetPtr = _ips->readPacket();
	int counter=0;
	while(packetPtr != 0)
	{
		push(packetPtr);
		packetPtr = _ips->readPacket();
		counter++;
	}
}

void PacketBufferQ::load(int first, int last)
{
	int counter = 0;
	ByteStreamPtr packetPtr;

	// skip elements preceeding first
	while(counter < first) {
		packetPtr = _ips->readPacket();
		if(packetPtr == 0) break;
		counter++;
	}

	// enqueue elements from first to last
	do {
		packetPtr = _ips->readPacket();
		if(packetPtr == 0) break;
		queue.push(packetPtr);
		counter++;
	}
	while(counter <= last);
}

}
