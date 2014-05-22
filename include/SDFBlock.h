/***************************************************************************
                          SDFBlock.h  -  description
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
 
#ifndef _SDFBlock_H
#define _SDFBlock_H
#include "PacketException.h"
#include "PartOfPacket.h"
#include <string>

namespace PacketLib
{


class SDFBlockType
{

public:

    SDFBlockType();

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
class SDFBlock : public PartOfPacket
{
public:

    SDFBlock();
    virtual ~SDFBlock();

    virtual bool loadFields(InputText& fp) throw(PacketException*);

    virtual void setPreviousPop(PartOfPacket* pop)
    {
        previous = pop;
    };

    /// Get a block of number nblock of the group of blocks of the rblock
    /// with the inndex rBlockIndex.
    /// \param nblock the number of the block
    /// \param rBlockIndex the number of the rblock
    virtual SDFBlock* getBlock(word nblock, word rBlockIndex);

    virtual dword sizeMax();

    virtual dword size();

    /// Set the number of blocks (the number of times that a block of a
    /// determinated type is repeated) for each type of rblock present.
    /// \param number The number of blocks
    /// \param rBlockIndex The number of rblock
    virtual void setNumberOfBlocks(word number, word rblockIndex = 0) throw (PacketException*);

    /// Get the number of blocks (the number of times that a block of a
    /// determinate type is repeated) for each type of rblock present.
    /// \param rBlockIndex The number of rblock
    virtual word getNumberOfBlocks(word rblockIndex = 0);

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

    virtual bool setByteStream(ByteStreamPtr s, int decodeType);

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
	
	virtual word getFieldIndex(string fieldname) {
		return fixed.getFieldIndex(fieldname);
	}

    /// Returns the value of a field in the list of fields of the fixed part.
	/// See ParfOfPacket doc for more details
    /// \param index Represent the index in the list.
    virtual  inline word getFieldValue(word index)
    {
        return fixed.getFieldValue(index);
    };
	
	/// Returns the value of a field in the list of fields of the fixed part.
	/// See ParfOfPacket doc for more details
    /// \param index Represent the index in the list.
	virtual inline signed short getFieldValue_16i(word index)
	{
		return fixed.getFieldValue_16i(index);
	}
	
	/// Returns the value of a field in the list of fields of the fixed part.
	/// See ParfOfPacket doc for more details
    /// \param index Represent the index in the list.
	virtual inline word getFieldValue_16ui(word index) {
		return fixed.getFieldValue_16ui(index);
	}
	
	/// Returns the value of a field in the list of fields of the fixed part.
	/// See ParfOfPacket doc for more details
    /// \param index Represent the index in the list.
	virtual inline signed long getFieldValue_32i(word index) {
		return fixed.getFieldValue_32i(index);
	}

	/// Returns the value of a field in the list of fields of the fixed part.
	/// See ParfOfPacket doc for more details
    /// \param index Represent the index in the list.
	virtual inline unsigned long getFieldValue_32ui(word index)
	{
		return fixed.getFieldValue_32ui(index);
	}
	
	/// Returns the value of a field in the list of fields of the fixed part.
	/// See ParfOfPacket doc for more details
    /// \param index Represent the index in the list.
	virtual inline float getFieldValue_32f(word index)
	{
		return fixed.getFieldValue_32f(index);
	}
	
	/// Returns the value of a field in the list of fields of the fixed part.
	/// See ParfOfPacket doc for more details
    /// \param index Represent the index in the list.
	virtual inline double getFieldValue_64f(word index)
	{
		return fixed.getFieldValue_64f(index);
	}

    /// Sets the value of a field in the list of fields of the fixed part of this block.
	/// See ParfOfPacket doc for more details
    /// \param index Represent the index in the list.
    /// \param value The value must be set.
    virtual  inline void setFieldValue(word index, word value)
    {
        fixed.setFieldValue(index, value);
    };

    /// Sets the value of a field in the list of fields of the fixed part of this block.
	/// See ParfOfPacket doc for more details
    /// \param index Represent the index in the list.
    /// \param value The value must be set.
	virtual void setFieldValue_16i(word index, signed short value)
	{
        fixed.setFieldValue_16i(index, value);
    };
	
    /// Sets the value of a field in the list of fields of the fixed part of this block.
	/// See ParfOfPacket doc for more details
    /// \param index Represent the index in the list.
    /// \param value The value must be set.
	virtual void setFieldValue_16ui(word index, word value)
	{
        fixed.setFieldValue_16ui(index, value);
    };
	
    /// Sets the value of a field in the list of fields of the fixed part of this block.
	/// See ParfOfPacket doc for more details
    /// \param index Represent the index in the list.
    /// \param value The value must be set.
    virtual void setFieldValue_32i(word index, signed long value)
	{
        fixed.setFieldValue_32i(index, value);
    };
	
    /// Sets the value of a field in the list of fields of the fixed part of this block.
	/// See ParfOfPacket doc for more details
    /// \param index Represent the index in the list.
    /// \param value The value must be set.
    virtual void setFieldValue_32ui(word index, unsigned long value)
	{
        fixed.setFieldValue_32ui(index, value);
    };
	
    /// Sets the value of a field in the list of fields of the fixed part of this block.
	/// See ParfOfPacket doc for more details
    /// \param index Represent the index in the list.
    /// \param value The value must be set.
    virtual void setFieldValue_32f(word index, float value)
    {
        fixed.setFieldValue_32f(index, value);
    };
	
    /// Sets the value of a field in the list of fields of the fixed part of this block.
	/// See ParfOfPacket doc for more details
    /// \param index Represent the index in the list.
    /// \param value The value must be set.
    virtual void setFieldValue_64f(word index, double value)
	{
        fixed.setFieldValue_64f(index, value);
    };
	
    /// Returns the number of fields of this block (fixed and variable part).
    virtual inline word getNumberOfFields()
    {
        return getTotalNumberOfFields();
    };
	
	/// Returns the value of a field in the list of fields of this part of packet.
	/// The value returned is interpreted as a unsigned integer of less of equal 16 bits dimension
	/// (depends by the size of the field in bits)
    /// \param fieldname Represent the name of the field.
    virtual word getFieldValue(string fieldname);
	
	/// Returns the value of a field in the list of fields of this part of packet.
	/// The value returned is interpreted as a 16 bit signed integer.
    /// \param fieldname Represent the name of the field.
	virtual signed short getFieldValue_16i(string fieldname);
	
	/// Returns the value of a field in the list of fields of this part of packet.
	/// The value returned is interpreted as a 16 bit unsigned integer.
    /// \param fieldname Represent the name of the field.
	virtual word getFieldValue_16ui(string fieldname);
	
	/// Returns the value of a field in the list of fields of this part of packet.
    /// The value returned is interpreted as a 32 bit signed integer.
    /// This corresponds with the PTC=4, PFC = 14.
    /// \param fieldname Represent the name of the field.
    virtual signed long getFieldValue_32i(string fieldname);
	
    /// Returns the value of a field in the list of fields of this part of packet.
    /// The value returned is interpreted as a 32 bit unsigned integer.
    /// This corresponds with the PTC=3, PFC = 14.
    /// \param fieldname Represent the name of the field.
    virtual unsigned long getFieldValue_32ui(string fieldname);
	
    /// Returns the value of a field in the list of fields of this part of packet.
    /// The value returned is interpreted as a real single precision (IEEE 754).
    /// This corresponds with the PTC=5, PFC = 1 <=> float or 32f
    /// \param fieldname Represent the name of the field.
    virtual float getFieldValue_32f(string fieldname);
    
    /// Returns the value of a field in the list of fields of this part of packet.
    /// The value returned is interpreted as a real double precision (IEEE 754).
    /// This corresponds with the PTC=5, PFC = 2. <=> double or 64f
    /// \param fieldname Represent the name of the field.
    virtual double getFieldValue_64f(string fieldname);
	
	///Documentation
    /// Sets the value of a field in the list of fields of this part of packet. Remember that
    /// if a predefined value is specified in the .stream, this method has not effect and the
    /// value contained in the .stream is used.
    /// \param fieldname Represent the name of the field.
    /// \param value The value must be set.
    virtual void setFieldValue(string fieldname, word value);
	
	/// Sets the value of a field. The value is interpreted as a 16 bit signed integer.
    /// \param fieldname Represent the name of the field.
    /// \param value The 16 bit signed integer value.
	virtual void setFieldValue_16i(string fieldname, signed short value);
	
	/// Sets the value of a field. The value is interpreted as a 16 bit unsigned integer (word).
    /// \param fieldname Represent the name of the field.
    /// \param value The 16 bit unsigned integer value.
	virtual void setFieldValue_16ui(string fieldname, word value);
	
    /// Sets the value of a field. The value is interpreted as a 32 bit signed integer.
    ///	---------------------------------
    /// This corresponds with the PTC=4, PFC = 14.
    /// See setFieldValue(word index, word value) for general considerations.
    /// \param fieldname Represent the name of the field.
    /// \param value The 32 bit signed integer value.
    virtual void setFieldValue_32i(string fieldname, signed long value);
	
    /// Sets the value of a field. The value is interpreted as a 32 bit unsigned integer.
    /// This corresponds with the PTC=3, PFC = 14.
    /// See setFieldValue(word index, word value) for general considerations.
    /// \param fieldname Represent the name of the field.
    /// \param value The 32 bit unsigned integer value.
    virtual void setFieldValue_32ui(string fieldname, unsigned long value);
	
	/// Set the value of a field. The value is interpreted as a real single
    /// precision (IEEE 754).
    /// This corresponds with the PTC=5, PFC = 1.
    /// See setFieldValue(word index, word value) for general considerations.
    /// \param fieldname Represent the name of the field.
    /// \param value The real single precision value
    virtual void setFieldValue_32f(string fieldname, float value);
    
    /// Set the value of a field. The value is interpreted as a real double
    /// precision (IEEE 754).
    /// This corresponds with the PTC=5, PFC = 2.
    /// See setFieldValue(word index, word value) for general considerations.
    /// \param fieldname Represent the name of the field.
    /// \param value The real double precision value
    virtual void setFieldValue_64f(string fieldname, double value);

    /// Returns the number of fields of the overall block
    virtual word getTotalNumberOfFields();

    /// Prints the value of each field of this part of packet
    virtual char** printValue(char* addString = "");

    virtual void printValueStdout();

    /// Prints the structure of this part of packet
    virtual std::string* printStructure();

    virtual bool hasFixedPart()
    {
        return type->fixedPresent;
    }

    virtual bool hasVariablePart()
    {
        return type->variablePresent;
    }

	/// Return 'the number of rblock types' defined for this rblock. The value is loaded from the config files.
    virtual word getNumberOfTypes()
	{
		return type->numberOfRBlocks;
	}

    PartOfPacket fixed;

protected:

    virtual word getCurrentNumberOfBlocks();

    SDFBlock* block;

    /// Real number of blocks.
    word* numberOfRealDataBlock;

    /// An index that represent an unique index for each block of a particular rblock.
    word ID;

    /// An index that represent the type of rblock (starting from 0). This index
    /// is unique into a rblock container.
    word rBlockType;

    bool reset_output_stream;

    ByteStreamPtr tempBlock1;

    SDFBlockType* type;

    static long counter;

};

}

#endif /* SDFBlock_H_HEADER_INCLUDED_806B7DA0 */
