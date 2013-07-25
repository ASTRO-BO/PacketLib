/***************************************************************************
                          InputFile.h  -  description
                             -------------------
    begin                : Sat Oct 26 2002
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

#ifndef INPUTFILE_H
#define INPUTFILE_H

#include "Input.h"
#include "PacketExceptionIO.h"
#include "File.h"

namespace PacketLib {

//##ModelId=3EADC12202FD
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/InputFile.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: InputFile.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.2 $
//##	\brief This class represent a File input for IO system.
class InputFile : public Input
{
    public:
        //##ModelId=3EADC1280365
        InputFile(bool bigendian);

        //##ModelId=3EADC1280368
        ~InputFile();

        //##ModelId=3EADC1280369
        virtual bool open( char** parameters ) throw(PacketExceptionIO*);

        //##ModelId=3EADC128036F
        virtual void close() throw(PacketExceptionIO*);

        //##ModelId=3EADC1280371
        virtual ByteStream* readByteStream(dword n_byte) throw(PacketExceptionIO*);

        //##ModelId=3EADC1280377
        virtual char* readString() throw(PacketExceptionIO*);

        //##ModelId=3EADC128037A
        virtual int getType() { return 0; };

    protected:

	//##ModelId=3EADC128035A
        File* file;

        //##ModelId=3EADC1280361
        char* filename;

};
}
#endif
