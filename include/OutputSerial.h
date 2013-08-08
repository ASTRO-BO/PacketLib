/***************************************************************************
                          OutputSerial.h  -  description
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

#ifndef _OUTPUTSERIAL_H
#define _OUTPUTSERIAL_H

#include "Output.h"
#include "Serial.h"

namespace PacketLib
{

///	\brief This class represents generic type of output. The output must be a serial port.
class OutputSerial : public Output
{

public:

    OutputSerial(bool bigendian);

    virtual ~OutputSerial();

    virtual void close() throw(PacketExceptionIO*);

    virtual bool open(char** parameters) throw(PacketExceptionIO*);

    virtual bool writeByteStream(ByteStream* b) throw(PacketExceptionIO*);

    virtual bool writeString(const char* str) throw(PacketExceptionIO*);

    virtual int getType()
    {
        return 0;
    };

protected:


    char* device;
    Serial* serial;
    int	flag;

};

}

#endif
