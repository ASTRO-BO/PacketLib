/***************************************************************************
                          Output.h  -  description
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001, 2013 by Andrea Bulgarelli
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
 
#ifndef _OUTPUT_H
#define _OUTPUT_H

#include "PacketLibDefinition.h"
#include "ByteStream.h"
#include "PacketExceptionIO.h"

namespace PacketLib
{

///	\brief This class represents generic type of output.
class Output
{
public:
    Output(bool bigendian);

    virtual void close() throw(PacketExceptionIO*) = 0;

    virtual bool open(char** parameters) throw(PacketExceptionIO*) = 0;

    virtual bool isClosed();

    virtual bool isBigendian();

    virtual bool writeByteStream(ByteStream* b) throw(PacketExceptionIO*) = 0;

    virtual bool writeString(const char* str) throw(PacketExceptionIO*) = 0;

    virtual int getType() = 0;

protected:

    bool isclosed;

    bool bigendian;
};

}
#endif                           /* OUTPUT_H_HEADER_INCLUDED_D25155A3 */
