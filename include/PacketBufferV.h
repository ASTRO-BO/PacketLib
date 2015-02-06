/***************************************************************************
 PacketBufferV.h  -  An array buffer class for Packets
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
#ifndef _PACKETBUFFERV_H
#define _PACKETBUFFERV_H

#include <string>
#include <vector>
#include "PacketLibDefinition.h"
#include "ByteStream.h"
#include "InputPacketStream.h"
#include "Input.h"

namespace PacketLib {

/// An array of raw packets.
class PacketBufferV {

public:

	PacketBufferV(string configFile, string inputFile);

	~PacketBufferV();

	/// Load all the tmInputFile packets into the vector.
	void load();

	/// Load a subset of packets into the vector.
	/// \param first The first packet.
	/// \param last The last packet.
	void load(int first, int last);

	/// Get a raw packet.
	/// \index the index of the packet.
	ByteStreamPtr get(int index)
	{
		return vec[index];
	}

	ByteStreamPtr getByteStream(int index, dword sizeB = 0);

	ByteStreamPtr getNextByteStream(dword sizeB = 0);

	/// Get a raw packet (cyclic vector)
	ByteStreamPtr getNext();

	/// Return the size of the vector.
	/// \return The size of the vector.
	int size()
	{
		return vec.size();
	}

	bool isBigendian();

private:

	std::vector<ByteStreamPtr> vec;
	unsigned int currentIndex;
	long currentIndexBS;

	InputPacketStream* _ips;
	Input* _in;
};

}

#endif
