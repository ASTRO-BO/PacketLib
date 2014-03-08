/***************************************************************************
                          PacketDataField.cpp  -  description
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
 
#include "PacketDataField.h"

using namespace PacketLib;


PacketDataField::PacketDataField() : PartOfPacket("Packet Data Field")
{
    dataFieldHeader = (DataFieldHeader*) new DataFieldHeader();
    tail = new PartOfPacket();
    sourceDataField = 0;
};


PacketDataField::~PacketDataField()
{
    delete dataFieldHeader;
    delete sourceDataField;
    delete tail;
}



dword PacketDataField::getDimension()
{
    if(sourceDataField != 0)
        return dataFieldHeader->getDimension() + sourceDataField->getDimension() + tail->getDimension();
    else
        return dataFieldHeader->getDimension() + tail->getDimension();
}



dword PacketDataField::getMaxDimension()
{
    if(sourceDataField != 0)
        return dataFieldHeader->getDimension() + sourceDataField->getMaxDimension() + tail->getDimension();
    else
        return dataFieldHeader->getDimension() + tail->getDimension();
}







bool PacketDataField::setOutputStream(ByteStreamPtr os, word first)
{
    outputstream = ByteStreamPtr(new ByteStream((os->stream + first), getDimension(), os->isBigendian()));
    dataFieldHeader->setOutputStream(os, first);
    word sdfstart = first + dataFieldHeader->getDimension();
    sourceDataField->setOutputStream(os, sdfstart);
    word tailstart = sdfstart;
    if(sourceDataField != 0)
        tailstart += sourceDataField->getDimension();
    if(tail->getDimension() != 0)
        tail->setOutputStream(os, tailstart);
    return true;
}



ByteStreamPtr PacketDataField::generateStream(bool bigendian)
{
    dataFieldHeader->generateStream(bigendian);
    sourceDataField->generateStream(bigendian);
    tail->generateStream(bigendian);
    return outputstream;
}
