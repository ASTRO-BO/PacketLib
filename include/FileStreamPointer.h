/***************************************************************************
                          FileStreamPointer.h  -  description
                             -------------------
    begin                : Mon Jan 14 2002
    copyright            : (C) 2002, 2013 by Andrea Bulgarelli
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

#ifndef _FILESTREAMPOINTER_H
#define _FILESTREAMPOINTER_H

namespace PacketLib
{

///ModelId=3C87743F0230
///	$Date: 2005/08/02 15:07:13 $
///	$Header: /home/repository/cvs/gtb/PacketLib/include/FileStreamPointer.h,v 1.3 2005/08/02 15:07:13 bulgarelli Exp $
///	$Id: FileStreamPointer.h,v 1.3 2005/08/02 15:07:13 bulgarelli Exp $
///	$Revision: 1.3 $
///	\brief This class represent a pointer into a file of byte
class FileStreamPointer
{
public:

    FileStreamPointer();

    ~FileStreamPointer();

public:

    /// Type of packet. This is the index in the list of packetType attribute of InputPacketStream class
    int typeOfPacket;

    /// Pointer of the start position into the file (FileStream)
    long pointerStart;

    /// A global index of this pointer into the full list of pointers
    long index;

    /// The name of the found packet
    char* nameOfPacket;

    /// Pointer of the end position into the file (FileStream)
    long pointerEnd;

};

}

#endif
