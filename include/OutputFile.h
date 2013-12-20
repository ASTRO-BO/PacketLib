/***************************************************************************
                          OutputFile.h  -  description
                             -------------------
    begin                : Mon Apr 29 2002
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

#ifndef _OUTPUTFILE_H
#define _OUTPUTFILE_H

#include "Output.h"
#include "File.h"

namespace PacketLib
{

///	\brief This class represents generic type of output. The output must be a file.
class OutputFile : public Output
{

public:

    OutputFile(bool bigendian);

    virtual ~OutputFile();

    virtual void close() throw(PacketExceptionIO*);

    virtual bool open(char** parameters) throw(PacketExceptionIO*);

    virtual bool writeByteStream(ByteStreamPtr b) throw(PacketExceptionIO*);

    virtual bool writeString(const char* str) throw(PacketExceptionIO*);

    virtual int getType()
    {
        return 0;
    };

protected:

    File* file;

    char* filename;

};

}

#endif
