/***************************************************************************
                          SDFRBBlock.h  -  description
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
 
#ifndef _SDFRBBLOCK_H
#define _SDFRBBLOCK_H
#include "PacketException.h"
#include "PartOfPacket.h"


namespace PacketLib
{


class SDFRBBlockType
{

public:

    SDFRBBlockType();

    bool loadType(InputText& fp) throw(PacketException*);

    /// the name of the InputFile
    char* name;

    /// Fixed part present
    bool fixedPresent;

    /// Variable part present
    bool variablePresent;


    char** rblockFilename;

    /// The number of rblock
    int numberOfRBlocks;

    //MANAGEMENT OF BLOCKS

    /// Represents the type of number of block. If true the number of blocks
    /// are fixed, if false the number of blocks are variable
    bool* numberOfBlockFixed;

    /// Represents the number of blocks for each rblock (for each data type)
    /// (if numberOfBlockFixed is true) or max
    /// number of blocks (if numberOfBlockFixed is false) in the structure of
    /// source data field. 
    /// This value is read from .packet configuration file.
    /// This variable not represent the effective number of
    /// block into the stream of data.
    word* maxNumberOfBlock;

    /// for variable block, number of level of headers in which is present the field
    /// with the number of blocks of the variable part
    word* headerLevelOfNBlockIndex;

    word* indexOfNBlock;

    /// for variable block, valore da sommare per ottenere il numero di eventi (blocchi) reali.
    word* subFromNBlock;

    /// apply an operator during the calculation of the number of blocks
    /// 0 -> nothing
    /// 1 -> / divide for 2
    byte* operatorType;

    /// Indicates if an rblock has a fixed or variable number of blocks
    bool* rBlockVariable;

    /// The max number of blocks for all rblocks (it is the sum of all maxNumberOfBlock values)
    /// regardless the rblock type (data type)
    word nblockmax;




};

///The core of the variable packet structure
class SDFRBBlock : public PartOfPacket
{
public:

    SDFRBBlock();
    virtual ~SDFRBBlock();

    virtual bool loadFields(InputText& fp) throw(PacketException*);

    virtual void setPreviousPop(PartOfPacket* pop)
    {
        previous = pop;
    };

    /// Get a block of number nblock of the group of blocks of the rblock
    /// with the inndex rBlockIndex.
    /// \param nblock the number of the block
    /// \param rBlockIndex the number of the rblock
    virtual SDFRBBlock* getBlock(word nblock, word rBlockIndex);

    virtual dword getMaxDimension();

    virtual dword getDimension();

    /// Set the number of blocks (the number of times that a block of a
    /// determinated type is repeated) for each type of rblock present.
    /// \param number The number of blocks
    /// \param rBlockIndex The number of rblock
    virtual void setNumberOfRealDataBlock(word number, word rblockIndex = 0) throw (PacketException*);

    /// Get the number of blocks (the number of times that a block of a
    /// determinate type is repeated) for each type of rblock present.
    /// \param rBlockIndex The number of rblock
    virtual word getNumberOfRealDataBlock(word rblockIndex = 0);

    virtual void setRBlockType(word rb)
    {
        rBlockType = rb;
    };

    virtual inline word getRBlockType()
    {
        return rBlockType;
    };

    virtual void setID(word id)
    {
        ID = id;
    };

    virtual inline word getID()
    {
        return ID;
    };

    virtual bool setOutputStream(ByteStreamPtr os, dword first);

    virtual ByteStreamPtr generateStream(bool bigendian);

    virtual bool setByteStream(ByteStreamPtr s);

    virtual ByteStreamPtr getByteStream()
    {
        return stream;
    }

    /// Returns a pointer of a field in the list of fields of the fixed part.
    /// \param index Represent the index in the list.
    virtual  inline  Field* getFields(word index)
    {
        return fixed.getFields(index);
    };

    /// Returns the value of a field in the list of fields of the fixed part.
    /// \param index Represent the index in the list.
    virtual  inline word getFieldValue(word index)
    {
        return fixed.getFieldValue(index);
    };

    /// Sets the value of a field in the list of fields of the fixed part.
    /// \param index Represent the index in the list.
    /// \param value The value must be set.
    virtual  inline void setFieldValue(word index, word value)
    {
        fixed.setFieldValue(index, value);
    };

    /// Returns the number of fields of this block (fixed and variable part).
    virtual inline word getNumberOfFields()
    {
        return getTotalNumberOfFields();
    };

    /// Returns the number of fields of the overall block
    virtual word getTotalNumberOfFields();

    /// Prints the value of each field of this part of packet
    virtual char** printValue(char* addString = "");

    virtual void printValueStdout();

    /// Prints the structure of this part of packet
    virtual string* printStructure();

    PartOfPacket fixed;

protected:

    virtual word getCurrentNumberOfBlocks();

    SDFRBBlock* block;

    /// Real number of blocks.
    word* numberOfRealDataBlock;

    /// An index that represent an unique index for each block of a particular rblock.
    word ID;

    /// An index that represent the type of rblock (starting from 0). This index
    /// is unique into a rblock container.
    word rBlockType;

    bool reset_output_stream;

    ByteStreamPtr tempBlock1;

    SDFRBBlockType* type;

    static long counter;

};

}

#endif /* SDFRBBLOCK_H_HEADER_INCLUDED_806B7DA0 */
