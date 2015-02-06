/***************************************************************************
 PacketBufferQ.h  -  A FIFO buffer class for Packets
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
#ifndef _PACKETBUFFERQ_H
#define _PACKETBUFFERQ_H

#include <string>
#include <queue>
#include "PacketLibDefinition.h"
#include "InputPacketStream.h"
#include "Input.h"

namespace PacketLib {

/// A FIFO queue of raw packets.
class PacketBufferQ {

public:
	PacketBufferQ(string configFile, string inputFile);

	~PacketBufferQ();

	/// Load all the tmInputFile packets into the queue.
	void load();

	/// Load a subset of packets into the queue.
	/// \param first The first packet.
	/// \param last The last packet.
	void load(int first, int last);

	/// Push a raw packet to the queue.
	/// \param rawPacket The raw packet pointer.
	void push(ByteStreamPtr rawPacket)
	{
		queue.push(rawPacket);
	}

	/// Pop a raw packet from the queue.
	/// \return The raw packet pointer.
	ByteStreamPtr pop()
	{
		if(queue.size() == 0)
			return 0;

		ByteStreamPtr elem = queue.front();
		queue.pop();
		return elem;
	}

	/// Return the size of the queue.
	/// \return The size of the queue.
	int size()
	{
		return queue.size();
	}

private:

	std::queue<ByteStreamPtr> queue;

	InputPacketStream* _ips;
	Input* _in;
};

}

#endif
