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

PacketBufferQ::PacketBufferQ(string configFile, string inputFile)
{
	_ips = new InputPacketStream(realpath(configFile.c_str(), NULL));
	_ips->createStreamStructure();
	_in = (Input*) new InputFile(_ips->isBigEndian());
	char** param = new char*[2];
	param[0] = (char*) realpath(inputFile.c_str(), NULL);
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
	int counter = 0;

	Packet* p = _ips->readPacket();
	while(p != 0)
	{
		ByteStreamPtr packetPtr = p->getInputStream();
		push(packetPtr);

		p = _ips->readPacket();
		counter++;
	}
}

void PacketBufferQ::load(int first, int last)
{
	int counter = 0;

	// skip elements preceeding first
	Packet* p = _ips->readPacket();
	while(p && counter < first) {
		p = _ips->readPacket();
		counter++;
	}

	// envec elements from first to last
	while(p && counter <= last)
	{
		ByteStreamPtr packetPtr = p->getInputStream();
		push(packetPtr);

		p = _ips->readPacket();
		counter++;
	}
}

}
