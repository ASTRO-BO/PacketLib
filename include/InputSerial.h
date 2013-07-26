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

#ifndef INPUTSERIAL_H
#define INPUTSERIAL_H

#include "Input.h"
#include "PacketExceptionIO.h"
#include "Serial.h"

namespace PacketLib
{

//##ModelId=3EADC12202FD
//## $Date: 2005/03/09 10:57:50 $
//## $Header: /home/repository/cvs/gtb/PacketLib/include/InputSerial.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//## $Id: InputSerial.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//## $Revision: 1.2 $
//## \brief This class represent a File input for IO system.
class InputSerial : public Input
{
public:
    //##ModelId=3EADC1280365
    InputSerial(bool bigendian);

    //##ModelId=3EADC1280368
    ~InputSerial();

    //##ModelId=3EADC1280369
    virtual bool open( char** parameters ) throw(PacketExceptionIO*);

    //##ModelId=3EADC128036F
    virtual void close() throw(PacketExceptionIO*);

    //##ModelId=3EADC1280371
    virtual ByteStream* readByteStream(int n_byte) throw(PacketExceptionIO*);

    //##ModelId=3EADC1280377
    virtual char* readString() throw(PacketExceptionIO*);

    //##ModelId=3EADC128037A
    virtual int getType()
    {
        return 0;
    };

protected:

    //##ModelId=3EADC128035A
    Serial* serial;

    //##ModelId=3EADC1280361
    char*  device;
    int  flag;

};
}
#endif
