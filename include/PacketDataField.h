/***************************************************************************
                          PacketDataField.h  -  description
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001 by Andrea Bulgarelli
    email                : bulgarelli@bo.iasf.cnr.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/
#ifndef PacketDataField_h_h
#define PacketDataField_h_h

#include "PacketLibDefinition.h"
#include "PacketExceptionFileFormat.h"
#include "SourceDataField.h"
#include "DataFieldHeader.h"
#include "Field.h"

namespace PacketLib
{

//##ModelId=3C0F6C190357
//##Documentation
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/PacketDataField.h,v 1.3 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: PacketDataField.h,v 1.3 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.3 $
//##	\brief Represent the data field of the packet.
class PacketDataField : public PartOfPacket
{

public:
    //##ModelId=3EADC13801BA
    //##Documentation
    //##Constructor
    PacketDataField();

    //##ModelId=3EADC13801EB
    ~PacketDataField();

    //##ModelId=3EADC138021F
    //##Documentation
    //## Returns the number of events data block in the source data field.
    //## Returns 0 if there aren't blocks.
    word getNumberOfRealDataBlock();

    //##ModelId=3EADC1380256
    //##Documentation
    //## Sets the number of data block presents in the source data field.
    //## If the number is up of the max number of data block allowed, the
    //## number of real data blocks is set with the max number of blocks.
    void setNumberOfRealDataBlock(word number);

    //##ModelId=3EADC1380316
    //##Documentation
    //## Total dimension in bytes of data field.
    dword getDimension();

    //##ModelId=3EADC138034F
    //##Documentation
    //## Total max dimension in bytes of data field.
    dword getMaxDimension();

    //##ModelId=3EADC138038B
    //##Documentation
    //## Creates the outputstream ByteStream for the generation of the output stream
    virtual bool setOutputStream(ByteStream* os, word first);


    //##ModelId=3EADC1390165
    virtual ByteStream* generateStream(bool bigendian);

    //##Documentation
    //## Represents the data field header.
    DataFieldHeader *dataFieldHeader;

    //##Documentation
    //## Represents the source data field.
    SourceDataField *sourceDataField;

    //##Documentation
    //## The tail of the packet. It should be a Packet Error Control section.
    PartOfPacket* tail;

};

}
#endif
