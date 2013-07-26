/***************************************************************************
                          OutputFile.h  -  description
                             -------------------
    begin                : Mon Apr 29 2002
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

#ifndef OUTPUTFILE_H
#define OUTPUTFILE_H

#include "Output.h"
#include "File.h"

namespace PacketLib
{

//##ModelId=3EADC123008A
//##Documentation
//##	$Date: 2012/06/08 15:14:29 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/OutputFile.h,v 1.3 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Id: OutputFile.h,v 1.3 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Revision: 1.3 $
//##	\brief This class represents generic type of output. The output must be a file.
class OutputFile : public Output
{

public:

    //##ModelId=3EADC12A0254
    OutputFile(bool bigendian);

    //##ModelId=3EADC12A0259
    virtual ~OutputFile();

    //##ModelId=3EADC12A025B
    virtual void close() throw(PacketExceptionIO*);

    //##ModelId=3EADC12A025D
    virtual bool open(char** parameters) throw(PacketExceptionIO*);

    //##ModelId=3EADC12A0263
    virtual bool writeByteStream(ByteStream* b) throw(PacketExceptionIO*);

    //##ModelId=3EADC12A0269
    virtual bool writeString(const char* str) throw(PacketExceptionIO*);

    //##ModelId=3EADC12A026F
    virtual int getType()
    {
        return 0;
    };

protected:

    //##ModelId=3EADC12A0245
    File* file;

    //##ModelId=3EADC12A024E
    char* filename;

};

}

#endif
