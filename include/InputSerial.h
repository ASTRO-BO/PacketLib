/***************************************************************************
                          InputSerial.h  -  description
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

#ifndef _INPUTSERIAL_H
#define _INPUTSERIAL_H

#include "Input.h"
#include "PacketExceptionIO.h"
#include "Serial.h"

namespace PacketLib
{

/// \brief This class represent a File input for IO system.
class InputSerial : public Input
{
public:
    InputSerial(bool bigendian);

    ~InputSerial();

    virtual bool open( char** parameters ) throw(PacketExceptionIO*);

    virtual void close() throw(PacketExceptionIO*);

    virtual ByteStreamPtr readByteStream(int n_byte) throw(PacketExceptionIO*);

    virtual char* readString() throw(PacketExceptionIO*);

    virtual int getType()
    {
        return 0;
    };

protected:

    Serial* serial;

    char*  device;
    int  flag;

};
}
#endif
