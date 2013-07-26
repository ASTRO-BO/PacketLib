/***************************************************************************
                          Output.h  -  description
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001 by Andrea Bulgarelli
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
#ifndef OUTPUT_H_HEADER_INCLUDED_D25155A3
#define OUTPUT_H_HEADER_INCLUDED_D25155A3

#include "PacketLibDefinition.h"
#include "ByteStream.h"
#include "PacketExceptionIO.h"

namespace PacketLib
{

//##ModelId=3C51317202D1
//##Documentation
//##	$Date: 2012/06/08 15:14:29 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/Output.h,v 1.3 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Id: Output.h,v 1.3 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Revision: 1.3 $
//##	\brief This class represents generic type of output.
class Output
{
public:
    //##ModelId=3EADC12A0144
    Output(bool bigendian);

    //##ModelId=3C5131A3033F
    virtual void close() throw(PacketExceptionIO*) = 0;

    //##ModelId=3C5131A30373
    virtual bool open(char** parameters) throw(PacketExceptionIO*) = 0;

    //##ModelId=3C5131A3038E
    virtual bool isClosed();

    //##ModelId=3EADC12A0193
    virtual bool isBigendian();

    //##ModelId=3C5131B30382
    virtual bool writeByteStream(ByteStream* b) throw(PacketExceptionIO*) = 0;

    //##ModelId=3EADC12A01E3
    virtual bool writeString(const char* str) throw(PacketExceptionIO*) = 0;

    //##ModelId=3EADC12A0223
    virtual int getType() = 0;

protected:

    //##ModelId=3EADC12A00EE
    bool isclosed;

    //##ModelId=3EADC12A0119
    bool bigendian;
};

}
#endif                           /* OUTPUT_H_HEADER_INCLUDED_D25155A3 */
