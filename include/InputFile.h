/***************************************************************************
                          InputFile.h  -  description
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

#ifndef _INPUTFILE_H
#define _INPUTFILE_H

#include "Input.h"
#include "PacketExceptionIO.h"
#include "File.h"

namespace PacketLib
{

///	\brief This class represent a File input for IO system.
class InputFile : public Input
{
public:
    InputFile(bool bigendian);

    ~InputFile();

    virtual bool open( char** parameters ) throw(PacketExceptionIO*);

	/// parameters[0] = filename
    virtual void openDevice(const std::vector<std::string>& parameters) throw(PacketExceptionIO*);

    virtual void close() throw(PacketExceptionIO*);

    virtual ByteStreamPtr readByteStream(dword n_byte) throw(PacketExceptionIO*);

    virtual char* readString() throw(PacketExceptionIO*);

    virtual int getType()
    {
        return 0;
    };
    
    virtual dword setpos(long offset) throw(PacketExceptionIO*);

protected:

    File* file;

    std::string filename;

};
}
#endif
