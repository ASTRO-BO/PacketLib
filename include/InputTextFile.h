/***************************************************************************
                          InputTextFile.h  -  description
                             -------------------
    begin                : Mon Mar 4 2002
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

#ifndef INPUTTEXTFILE_H
#define INPUTTEXTFILE_H

#include "InputText.h"
#include "File.h"
#include "PacketExceptionIO.h"
#include "MemoryBuffer.h"

namespace PacketLib
{

//##ModelId=3C87743F02B2
//##Documentation
//##	$Date: 2012/06/08 15:14:29 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/InputTextFile.h,v 1.4 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Id: InputTextFile.h,v 1.4 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Revision: 1.4 $
//##	\brief This class represents generic type of input. The input must be a input text file.
class InputTextFile : public InputText
{
public:

    //##ModelId=3AA64922006A
    InputTextFile();

    //##ModelId=3AA64922007E
    virtual ~InputTextFile();

    //##ModelId=3AA64922009C
    // parameters[0] is the name of file
    virtual bool open(char** parameters) throw(PacketExceptionIO*);

    //##ModelId=3AA6492200F6
    virtual void close() throw(PacketExceptionIO*) ;

    virtual char* getInputTextName()
    {
        return file.getFileName();
    };

    //##ModelId=3AA64922011E
    virtual char* getLine() throw(PacketExceptionIO*);

    //##ModelId=3AA64922013C
    virtual char* getLine(const char* s) throw(PacketExceptionIO*);

    //##ModelId=3AA649220196
    virtual char* getLastLineRead();

    //##ModelId=3AA6492201BE
    virtual long getpos();

    //##ModelId=3AA6492201DC
    virtual bool memBookmarkPos();

    //##ModelId=3AA64922020E
    virtual int setFirstPos();

    virtual bool setLastBookmarkPos();

    //##ModelId=3AA64922025E
    virtual long setpos(long offset) throw(PacketExceptionIO*);

    //##ModelId=3EADC12903E4
    virtual bool fchdir() throw(PacketExceptionIO*);

protected:

    File file;

private:

    //for caching mechanism
    static MemoryBuffer** listOfBuffers;
    static int nListOfBuffers;
    MemoryBuffer* buffer;
    bool usebuffer;

};

}

#endif
