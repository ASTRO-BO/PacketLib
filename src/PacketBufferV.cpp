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
	char** param = new char*[2];
	param[0] = (char*) inputFile.c_str();
	param[1] = 0;
	_in->open(param);
	_ips->setInput(_in);
	delete param;
}

PacketBufferV::~PacketBufferV()
{
}

void PacketBufferV::load()
{
	ByteStreamPtr packetPtr = _ips->readPacket();
	int counter=0;
	while(packetPtr != 0)
	{
		vec.push_back(packetPtr);
		packetPtr = _ips->readPacket();
		counter++;
	}
}

void PacketBufferV::load(int first, int last)
{
	int counter = 0;
	ByteStreamPtr packetPtr;

	// skip elements preceeding first
	while(counter < first) {
		packetPtr = _ips->readPacket();
		if(packetPtr == 0) break;
		counter++;
	}
	

	// envec elements from first to last
	do {
		packetPtr = _ips->readPacket();
		if(packetPtr == 0) break;
		vec.push_back(packetPtr);
		counter++;
	}
	while(counter <= last);
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

