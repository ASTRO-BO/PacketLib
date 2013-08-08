/***************************************************************************
                          InputTextFile.h  -  description
                             -------------------
    begin                : Mon Mar 4 2002
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

#ifndef _INPUTTEXTFILE_H
#define _INPUTTEXTFILE_H

#include "InputText.h"
#include "File.h"
#include "PacketExceptionIO.h"
#include "MemoryBuffer.h"

namespace PacketLib
{

///	\brief This class represents generic type of input. The input must be a input text file.
class InputTextFile : public InputText
{
public:

    InputTextFile();

    virtual ~InputTextFile();

    // parameters[0] is the name of file
    virtual bool open(char** parameters) throw(PacketExceptionIO*);

    virtual void close() throw(PacketExceptionIO*) ;

    virtual char* getInputTextName()
    {
        return file.getFileName();
    };

    virtual char* getLine() throw(PacketExceptionIO*);

    virtual char* getLine(const char* s) throw(PacketExceptionIO*);

    virtual char* getLastLineRead();

    virtual long getpos();

    virtual bool memBookmarkPos();

    virtual int setFirstPos();

    virtual bool setLastBookmarkPos();

    virtual long setpos(long offset) throw(PacketExceptionIO*);

    virtual bool fchdir() throw(PacketExceptionIO*);

protected:

    File file;

private:

    /// for caching mechanism
    static MemoryBuffer** listOfBuffers;
    static int nListOfBuffers;
    MemoryBuffer* buffer;
    bool usebuffer;

};

}

#endif
