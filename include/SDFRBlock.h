/***************************************************************************
                          SDFNoBlockFixed.h  -  description
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
#ifndef SDFRBLOCK_H_HEADER_INCLUDED_89D3066E
#define SDFRBLOCK_H_HEADER_INCLUDED_89D3066E
#include "SourceDataField.h"
#include "PacketException.h"
#include "PacketExceptionFileFormat.h" 
#include "SDFRBBlock.h"

namespace PacketLib {

//##ModelId=3C347FA20329
//##Documentation
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/SDFRBlock.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: SDFRBlock.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.2 $
//##	\brief Class which represents the source data field of Layout 4 (see the Interface Control Document).
class SDFRBlock : public SourceDataField
{
  public:

    SDFRBlock(PartOfPacket* pop = 0);

    virtual ~SDFRBlock();

    virtual bool loadFields(InputText& fp) throw(PacketException*);

    //##Documentation
    //## Get a block of number nblock of the group of blocks of the rblock 
    //## with the index rBlockIndex.
    //## \param nblock the number of the block
    //## \param rBlockIndex the number of the rblock    
    virtual SDFRBBlock* getBlock(word nblock, word rBlockIndex);

    //##Documentation
    //## Returns a pointer of a field in the fixed part of this source data field.
    //## \param index Represent the index in the list.
    virtual Field* getFields(word index);

    //##Documentation
    //## Returns the value of a field in the fixed part of this source data field.
    //## \param index Represent the index in the list.
    virtual word getFieldValue(word index);

    //##Documentation
    //## Sets the value of a field in the fixed part of this source data field.
    //## \param index Represent the index in the list.
    //## \param value The value must be setted.
    virtual void setFieldValue(word index, word value);    

    //##ModelId=3C187751018C
    //##Documentation
    //## Returns the number of fields.
    virtual word getNumberOfFields();                

    virtual dword getMaxDimension();
    
    virtual dword getDimension();

    virtual bool setByteStream(ByteStream* s);

    virtual bool setOutputStream(ByteStream* os, dword first);

    virtual ByteStream* generateStream(bool bigendian);

    //##Documentation
    //## Set the number of blocks (the number of times that a block of a
    //## determinated type is repeated) for each type of rblock present.
    //## \param number The number of blocks
    //## \param rBlockIndex The number of rblock
    void setNumberOfRealDataBlock(word number, word rblockIndex = 0) throw (PacketException*);

    //##Documentation
    //## Get the number of blocks (the number of times that a block of a
    //## determinated type is repeated) for each type of rblock present.
    //## \param rBlockIndex The number of rblock
    word getNumberOfRealDataBlock(word rblockIndex = 0);

    //##Documentation
    //## Prints the value of each field of this part of packet
    virtual char** printValue(char* addString = "");
    
    virtual void printValueStdout();

    //##Documentation
    //## Prints the structure of this part of packet
    virtual string* printStructure();    
    
  protected:

    //##ModelId=405AD4BD00C2
    SDFRBBlock* block;
    

    //##Documentation
    //## The number of rblock
    int numberOfRBlocks;

    //##Documentation
    //## for variable block, number of level of headers in which is present the field
    //## with the number of blocks of the variable part    
    word* headerLevelOfNBlockIndex;

    char** rblockFilename;

    bool* rBlockVariable;

    //##Documentation
    //## The max number of blocks
    word nblockmax;

};

}

#endif /* SDFRBLOCK_H_HEADER_INCLUDED_89D3066E */
