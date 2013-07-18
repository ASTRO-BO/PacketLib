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
#ifndef SDFRBBLOCK_H_HEADER_INCLUDED_806B7DA0
#define SDFRBBLOCK_H_HEADER_INCLUDED_806B7DA0
#include "PacketException.h"
#include "PartOfPacket.h"


namespace PacketLib {

//##ModelId=405AD49C00E5
class SDFRBBlock : public PartOfPacket
{
  public:

    SDFRBBlock();

    virtual bool loadFields(InputText& fp) throw(PacketException*);

    virtual void setPreviousPop(PartOfPacket* pop) {
      previous = pop;
    };

    //##Documentation
    //## Get a block of number nblock of the group of blocks of the rblock 
    //## with the inndex rBlockIndex.
    //## \param nblock the number of the block
    //## \param rBlockIndex the number of the rblock
    virtual SDFRBBlock* getBlock(word nblock, word rBlockIndex);

    virtual word getMaxDimension();

    virtual word getDimension();

    //##Documentation
    //## Set the number of blocks (the number of times that a block of a
    //## determinated type is repeated) for each type of rblock present.
    //## \param number The number of blocks
    //## \param rBlockIndex The number of rblock
    virtual void setNumberOfRealDataBlock(word number, word rblockIndex = 0) throw (PacketException*);

    //##Documentation
    //## Get the number of blocks (the number of times that a block of a
    //## determinated type is repeated) for each type of rblock present.
    //## \param rBlockIndex The number of rblock
    virtual word getNumberOfRealDataBlock(word rblockIndex = 0);

    virtual void setRBlockType(word rb) { rBlockType = rb; };

    virtual inline word getRBlockType() { return rBlockType; };

    virtual void setID(word id) { ID = id; };

    virtual inline word getID() { return ID; };

    virtual bool setOutputStream(ByteStream* os, word first);

    virtual ByteStream* generateStream(bool bigendian);

    virtual bool setByteStream(ByteStream* s);

    //##ModelId=3C187751015F
    //##Documentation
    //## Returns a pointer of a field in the list of fields of the fixed part.
    //## \param index Represent the index in the list.
    virtual  inline  Field* getFields(word index) {
        return fixed.getFields(index);
    };

    //##ModelId=3EADC13D0294
    //##Documentation
    //## Returns the value of a field in the list of fields of the fixed part.
    //## \param index Represent the index in the list.
    virtual  inline word getFieldValue(word index) {
        return fixed.getFieldValue(index);
    };

    //##ModelId=3EADC13E0246
    //##Documentation
    //## Sets the value of a field in the list of fields of the fixed part.
    //## \param index Represent the index in the list.
    //## \param value The value must be setted.
    virtual  inline void setFieldValue(word index, word value) {
        fixed.setFieldValue(index, value);
    };

    //##ModelId=3C187751018C
    //##Documentation
    //## Returns the number of fields of this block (fixed and variable part).
    virtual inline word getNumberOfFields() {
      return getTotalNumberOfFields();
    };

    //##Documentation
    //## Returns the number of fields of the overall block
    virtual word getTotalNumberOfFields();

    //##Documentation
    //## Prints the value of each field of this part of packet
    virtual char** printValue(char* addString = "");

    //##Documentation
    //## Prints the structure of this part of packet
    virtual string* printStructure();    

    PartOfPacket fixed;
  protected:

    virtual word getCurrentNumberOfBlocks();

    //##ModelId=405AD4BD00C2
    SDFRBBlock* block;



    //##Documentation
    //## The number of rblock
    int numberOfRBlocks;

    //MANAGEMENT OF BLOCKS

    //##ModelId=405AA86B0129
    //##Documentation
    //## Represents the type of number of block. If true the number of blocks
    //## are fixed, if false the number of blocks are variable
    bool* numberOfBlockFixed;

    //##ModelId=405AA86B0197
    //##Documentation
    //## Represents the number of blocks (if numberOfBlockFixed is true) or max
    //## number of blocks (if numberOfBlockFixed is false) in the structure of
    //## source data field. This variable not represent the effective number of
    //## block into the stream of data.
    word* maxNumberOfBlock;

    //##ModelId=405AA86B01B4
    //##Documentation
    //## Real number of blocks.
    word* numberOfRealDataBlock;

    //##Documentation
    //## for variable block, number of level of headers in which is present the field
    //## with the number of blocks of the variable part
    word* headerLevelOfNBlockIndex;
    
    //##ModelId=405AA86B01A5
    word* indexOfNBlock;

    //##ModelId=405AA86B01C4
    //##Documentation
    //## for variable block, valore da sommare per ottenere il numero di eventi (blocchi) reali.
    word *subFromNBlock;    
    
    //##Documentation
    //## apply an operator during the calculation of the number of blocks
    //## 0 -> nothing
    //## 1 -> / divide for 2
    byte* operatorType;

    char** rblockFilename;

    //##Documentation
    //## Indicates if an rblock has a fixed or variable number of blocks
    bool* rBlockVariable;

    //##Documentation
    //## The max number of blocks
    word nblockmax;                                                    

    //##Documentation
    //## Fixed part present
    bool fixedPresent;

    //##Documentation
    //## Variable part present
    bool variablePresent;

    //##Documentation
    //## An index that represent the type of rblock (starting from 0). This index
    //## is unique into a rblock container.
    word rBlockType;

    //##Documentation
    //## An index that represent an unique index for each block of a particular rblock.
    word ID;

    //##ModelId=3EADC1440130
    bool reset_output_stream;

    ByteStream* tempBlock;  

};

}

#endif /* SDFRBBLOCK_H_HEADER_INCLUDED_806B7DA0 */
