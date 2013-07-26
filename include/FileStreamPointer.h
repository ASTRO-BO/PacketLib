/***************************************************************************
                          FileStreamPointer.h  -  description
                             -------------------
    begin                : Mon Jan 14 2002
    copyright            : (C) 2002 by Andrea Bulgarelli
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

#ifndef FILESTREAMPOINTER_H
#define FILESTREAMPOINTER_H

namespace PacketLib
{

//##ModelId=3C87743F0230
//##	$Date: 2005/08/02 15:07:13 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/FileStreamPointer.h,v 1.3 2005/08/02 15:07:13 bulgarelli Exp $
//##	$Id: FileStreamPointer.h,v 1.3 2005/08/02 15:07:13 bulgarelli Exp $
//##	$Revision: 1.3 $
//##	\brief This class represent a pointer into a file of byte
class FileStreamPointer
{
public:

    //##ModelId=3C877441011B
    FileStreamPointer();

    //##ModelId=3C877441011C
    ~FileStreamPointer();

public:

    //##ModelId=3C87744100FD
    //##Documentation
    //## Type of packet. This is the index in the list of packetType attribute of InputPacketStream class
    int typeOfPacket;

    //##ModelId=3C8774410107
    //##Documentation
    //## Pointer of the start position into the file (FileStream)
    long pointerStart;

    //##ModelId=3C8774410108
    //##Documentation
    //## A global index of this pointer into the full list of pointers
    long index;

    //##ModelId=3C8774410111
    //##Documentation
    //## The name of the found packet
    char* nameOfPacket;

    //##ModelId=3C8774410112
    //##Documentation
    //## Pointer of the end position into the file (FileStream)
    long pointerEnd;

};

}

#endif
