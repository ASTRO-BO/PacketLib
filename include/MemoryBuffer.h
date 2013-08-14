/***************************************************************************
                          MemoryBuffer.h  -  description
                             -------------------
    begin                : Fri Apr 12 2002
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

#ifndef _MEMORYBUFFER_H
#define _MEMORYBUFFER_H

#include "PacketLibDefinition.h"
#include "PacketExceptionIO.h"
#include "PacketException.h"

namespace PacketLib
{

///	\brief Class that represent an FIFO structure of char*
class MemoryBuffer
{
public:
    MemoryBuffer();

    ~MemoryBuffer();

    /// Write property of char** buffer.
    void setbuffer( char* _newVal) throw(PacketException*);;

    void setbuffer( char* _newVal, dword index) throw(PacketException*);

    /// Read property of char** buffer.
    char* getbuffer();

    bool getEOF();

    char* getlastbuffer();

    char* getbuffer(dword index);

    void readRewind();

    void writeRewind();

    dword getBufferDimension();

    bool loadBuffer(char* filename) throw(PacketExceptionIO*);

    bool saveBuffer(char* filename) throw(PacketExceptionIO*);

    void freebuffer();

    void setName(char* name);

    char* getName()
    {
        return bufferName;
    };

    int getpos();

    bool memBookmarkPos();

    bool setLastBookmarkPos();

    long setpos(int index);

    void printBuffer();

private:

    int bookmarkpos;

    dword dim;

    char** buffer;

    dword indexwrite;

    dword indexread;

    char* currentpwd;

    char* bufferName;

    bool eof;
};

}
#endif
