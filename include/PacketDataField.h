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

    /// Returns the number of events data block in the source data field.
    /// Returns 0 if there aren't blocks.
    word getNumberOfRealDataBlock();

    /// Sets the number of data block presents in the source data field.
    /// If the number is up of the max number of data block allowed, the
    /// number of real data blocks is set with the max number of blocks.
    void setNumberOfRealDataBlock(word number);

    /// Total dimension in bytes of data field.
    dword getDimension();

    /// Total max dimension in bytes of data field.
    dword getMaxDimension();

    /// Creates the outputstream ByteStream for the generation of the output stream
    virtual bool setOutputStream(ByteStream* os, word first);


    virtual ByteStream* generateStream(bool bigendian);

    /// Represents the data field header.
    DataFieldHeader *dataFieldHeader;

    /// Represents the source data field.
    SourceDataField *sourceDataField;

    /// The tail of the packet. It should be a Packet Error Control section.
    PartOfPacket* tail;

};

}
#endif
