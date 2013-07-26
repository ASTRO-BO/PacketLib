/***************************************************************************
                          SDFBVBlock.h  -  description
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
#ifndef SDFBVBLOCK_H_INCLUDED_B71C5D6D
#define SDFBVBLOCK_H_INCLUDED_B71C5D6D

#include "PacketLibDefinition.h"
#include "SDFBVBlockFixed.h"
#include "SDFBVBlockVariable.h"

namespace PacketLib
{

//##Documentation
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/SDFBVBlock.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: SDFBVBlock.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.2 $
//##	\brief Class wich represents a single block with a fixed part and with a variable part.
class SDFBVBlock : public PartOfPacket
{
public:

    //##ModelId=3EADC14203A4
    //##D
    SDFBVBlockFixed fixed;

    //##ModelId=3EADC14203AB
    SDFBVBlockVariable* variables;

    //##ModelId=3EADC14203B1
    word getNumberOfFields();

    //##ModelId=3EADC14203B2
    Field* getFields(word index);

    //##ModelId=3EADC14203B7
    //##Documentation
    //##
    word getFieldValue(word index);

    void setFieldValue(word index, word value);

    //##ModelId=3EADC14203BB
    dword getDimension();

    //##ModelId=3EADC14203BD
    //##Documentation
    //## Total max dimension in bytes of block
    dword getMaxDimension();

    //##ModelId=3EADC14203BF
    bool setOutputStream(ByteStream* os, dword first);

    //##ModelId=3EADC14203C6
    ByteStream* generateStream(bool bigendian);

    //##ModelId=3EADC1430127
    virtual word getNumberOfRealElement();

    //##ModelId=3EADC143012C
    virtual void setNumberOfRealElement(word value);

    virtual word getMaxNumberOfElements();

    SDFBVBlockFixed* getFixedPart();

    SDFBVBlockVariable* getElement(word nelement);

};

}
#endif                           /* SDFBVBLOCK_H_INCLUDED_B71C5D6D */
