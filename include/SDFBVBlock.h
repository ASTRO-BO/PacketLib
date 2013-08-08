/***************************************************************************
                          SDFBVBlock.h  -  description
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
 
#ifndef _SDFBVBLOCK_H
#define _SDFBVBLOCK_H

#include "PacketLibDefinition.h"
#include "SDFBVBlockFixed.h"
#include "SDFBVBlockVariable.h"

namespace PacketLib
{

///	\brief Class wich represents a single block with a fixed part and with a variable part.
class SDFBVBlock : public PartOfPacket
{
public:

    SDFBVBlockFixed fixed;

    SDFBVBlockVariable* variables;

    word getNumberOfFields();

    Field* getFields(word index);

    word getFieldValue(word index);

    void setFieldValue(word index, word value);

    dword getDimension();

     /// Total max dimension in bytes of block
    dword getMaxDimension();

    bool setOutputStream(ByteStream* os, dword first);

    ByteStream* generateStream(bool bigendian);

    virtual word getNumberOfRealElement();

    virtual void setNumberOfRealElement(word value);

    virtual word getMaxNumberOfElements();

    SDFBVBlockFixed* getFixedPart();

    SDFBVBlockVariable* getElement(word nelement);

};

}
#endif                           /* SDFBVBLOCK_H_INCLUDED_B71C5D6D */
