/***************************************************************************
                          PacketDataField.h  -  description
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001, 2013 by Andrea Bulgarelli
    email                : bulgarelli@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/
 
#ifndef _PACKETDATAFIELD_H_H
#define _PACKETDATAFIELD_H_H

#include "PacketLibDefinition.h"
#include "PacketExceptionFileFormat.h"
#include "SourceDataField.h"
#include "DataFieldHeader.h"
#include "Field.h"

namespace PacketLib
{

///	\brief Represent the data field of the packet.
class PacketDataField : public PartOfPacket
{

public:
    ///Constructor
    PacketDataField();

    ~PacketDataField();

    /// Total dimension in bytes of data field.
    dword size();

    /// Total max dimension in bytes of data field.
    dword sizeMax();

    /// Creates the outputstream ByteStream for the generation of the output stream
    virtual bool setOutputStream(ByteStreamPtr os, dword first);

    virtual ByteStreamPtr generateStream(bool bigendian);

	DataFieldHeader* getPacketDataFieldHeader() { return dataFieldHeader; };
	
	SourceDataField* getPacketSourceDataField() { return sourceDataField; };
	
	PartOfPacket* getPacketTail() { return tail; };
	
	void setPacketSourceDataField(SourceDataField* sdf) { this->sourceDataField = sdf; };
	
protected:
	
    /// Represents the data field header.
    DataFieldHeader *dataFieldHeader;

    /// Represents the source data field.
    SourceDataField *sourceDataField;

    /// The tail of the packet. It should be a Packet Error Control section.
    PartOfPacket* tail;

};

}
#endif
