/***************************************************************************
 PacketBufferV.cpp  -  A FIFO buffer class for Packets
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
#include "PacketBufferV.h"
#include "InputFile.h"

namespace PacketLib
{

PacketBufferV::PacketBufferV(const string& configFile, const string& inputFile)
	: currentIndex(0), currentIndexBS(0)
{
	_ips = new InputPacketStream(configFile.c_str());
	_ips->createStreamStructure();
	_in = (Input*) new InputFile(_ips->isBigEndian());
	char** param = (char**) new char*[2];
	param[0] = (char*) inputFile.c_str();
	param[1] = 0;
	_in->open(param);
	_ips->setInput(_in);
//	delete param;
}

PacketBufferV::~PacketBufferV()
{
}

void PacketBufferV::load()
{
	int counter = 0;

	Packet* p = _ips->readPacket();
	while(p != 0)
	{
		ByteStreamPtr packetPtr = p->getInputStream();
		vec.push_back(packetPtr);

		p = _ips->readPacket();
		counter++;
	}
}

void PacketBufferV::load(int first, int last)
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
		vec.push_back(packetPtr);

		p = _ips->readPacket();
		counter++;
	}
}

ByteStreamPtr PacketBufferV::getNext()
{
	if(currentIndex >= vec.size())
		currentIndex = 0;
	return vec[currentIndex++];
}



ByteStreamPtr PacketBufferV::getByteStream(int index, dword sizeB) {

	ByteStreamPtr stream = vec[index];
	dword sizep = sizeB;
	if(!sizep) sizep = _ips->getPacketDimension(stream);
	bool bigendian = _ips->isBigEndian();
	return ByteStreamPtr(new ByteStream(stream, sizep, bigendian));

}

ByteStreamPtr PacketBufferV::getNextByteStream(dword sizeB) {

	if(currentIndexBS >= size())
		currentIndexBS = 0;
	return getByteStream(currentIndexBS++, sizeB);

}

bool PacketBufferV::isBigendian() {
	return _ips->isBigEndian();
}


}

