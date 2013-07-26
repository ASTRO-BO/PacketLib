/***************************************************************************
                          Input.h  -  description
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

#ifndef INPUT_H
#define INPUT_H

#include "PacketExceptionIO.h"
#include "ByteStream.h"

namespace PacketLib
{

//##ModelId=3EADC12202F0
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/Input.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: Input.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.2 $
//##	\brief This class represent a generic input for IO system.
class Input
{
public:

    //##ModelId=3EADC1280336
    Input(bool bigendian);

    //##ModelId=3EADC1280338
    virtual ~Input();

    //##ModelId=3EADC128033A
    virtual bool open( char** parameters ) throw(PacketExceptionIO*) = 0;

    //##ModelId=3EADC128033E
    virtual ByteStream* readByteStream(dword n_byte) throw(PacketExceptionIO*) = 0;

    //##ModelId=3EADC1280341
    virtual char* readString() throw(PacketExceptionIO*) = 0;

    //##ModelId=3EADC1280344
    virtual void close( ) throw(PacketExceptionIO*) = 0;

    //##ModelId=3EADC1280347
    virtual int getType() = 0;

    //##ModelId=3EADC1280349
    virtual bool isClosed();

    //##ModelId=3EADC128034B
    virtual bool isEOF();

    //##ModelId=3EADC128034E
    virtual bool isBigendian();

protected:

    //##ModelId=3EADC128032F
    bool eof;

    //##ModelId=3EADC1280331
    bool closed;

    //##ModelId=3EADC1280333
    bool bigendian;

};
}
#endif
