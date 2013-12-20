/***************************************************************************
                          Input.h  -  description
                             -------------------
    begin                : Sat Oct 26 2002
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

#ifndef _INPUT_H
#define _INPUT_H

#include "PacketExceptionIO.h"
#include "ByteStream.h"

namespace PacketLib
{

/// 	\brief This class represent a generic input for IO system.
class Input
{
public:

    Input(bool bigendian);

    virtual ~Input();

    virtual bool open( char** parameters ) throw(PacketExceptionIO*) = 0;

    virtual ByteStreamPtr readByteStream(dword n_byte) throw(PacketExceptionIO*) = 0;

    virtual char* readString() throw(PacketExceptionIO*) = 0;

    virtual void close( ) throw(PacketExceptionIO*) = 0;

    virtual int getType() = 0;

   virtual bool isClosed();

    virtual bool isEOF();

    virtual bool isBigendian();

protected:

    bool eof;

    bool closed;


    bool bigendian;

};
}
#endif
