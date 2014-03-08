/***************************************************************************
                          SourceDataField.h  -  description
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
 
#ifndef _SourceDataField_H
#define _SourceDataField_H
#include "PacketException.h"
#include "PacketExceptionFileFormat.h"
#include "SDFBlock.h"

namespace PacketLib
{

///	\brief Class which represents the source data field of Layout 4 (see the Interface Control Document).
class SourceDataField : public PartOfPacket
{
public:

    SourceDataField(PartOfPacket* pop = 0);

    virtual ~SourceDataField();
	


    virtual bool loadFields(InputText& fp) throw(PacketException*);

     /// Get a block of number nblock of the group of blocks of the rblock
    /// with the index rBlockIndex.
    /// \param nblock the number of the block
    /// \param rBlockIndex the number of the rblock
    virtual SDFBlock* getBlock(word nblock, word rBlockIndex);
	
	///Get the fixed part of the source data field
	virtual ByteStreamPtr getFixedPart() { return block[0].fixed.getByteStream(); };
	
	///Get the variable part of the source data field
	//virtual ByteStreamPtr getVariablePart();
    
    /// Returns a pointer of a field in the fixed part of this source data field.
    /// \param index Represent the index in the list.
    virtual Field* getFields(word index);

    
    /// Returns the value of a field in the fixed part of this source data field.
    /// \param index Represent the index in the list.
    virtual word getFieldValue(word index);

    
    /// Sets the value of a field in the fixed part of this source data field.
    /// \param index Represent the index in the list.
    /// \param value The value must be set.
    virtual void setFieldValue(word index, word value);

    
    /// Returns the number of fields.
    virtual word getNumberOfFields();

    virtual dword getMaxDimension();

    virtual dword getDimension();
	
	virtual dword getDimensionFixedPart();

	//onlySections = false
    virtual bool setByteStream(ByteStreamPtr s, int decodeType);

    virtual bool setOutputStream(ByteStreamPtr os, dword first);

    virtual ByteStreamPtr generateStream(bool bigendian);

    
    /// Set the number of blocks (the number of times that a block of a
    /// determinated type is repeated) for each type of rblock present.
    /// \param number The number of blocks
    /// \param rBlockIndex The number of rblock
    void setNumberOfRealDataBlock(word number, word rblockIndex = 0) throw (PacketException*);

    
    /// Get the number of blocks (the number of times that a block of a
    /// determinated type is repeated) for each type of rblock present.
    /// \param rBlockIndex The number of rblock
    word getNumberOfRealDataBlock(word rblockIndex = 0);

    
    /// Prints the value of each field of this part of packet
    virtual char** printValue(char* addString = "");

    virtual void printValueStdout();

    
    /// Prints the structure of this part of packet
    virtual string* printStructure();

    /// return the related RBBlock structure.
    SDFBlock* getBBlock()
    {
        return block;
    }
	
	bool get_reset_output_stream() const;
	
    void set_reset_output_stream(bool value);
	
	char* printInHexadecimal();
	
	/// \return true if the packet is structured as a recursive block
    virtual bool isRBlock()
    {
        return rblock;
    };

protected:

    SDFBlock* block;


    
    /// The number of rblock
    int numberOfRBlocks;

    
    /// for variable block, number of level of headers in which is present the field
    /// with the number of blocks of the variable part
    word* headerLevelOfNBlockIndex;

    char** rblockFilename;

    bool* rBlockVariable;

    
    /// The max number of blocks
    word nblockmax;
	
	/// MANAGEMENT OF BLOCKS
	
    /// Represents the type of number of block. If true the number of blocks
    /// are fixed, if false the number of blocks are variable
    bool* numberOfBlockFixed;
	
    /// Represents the number of blocks (if numberOfBlockFixed is true) or max
    /// number of blocks (if numberOfBlockFixed is false) in the structure of
    /// source data field. This variable not represent the effective number of
    /// block into the stream of data.
    word* maxNumberOfBlock;
	
    /// Real number of blocks.
    word* numberOfRealDataBlock;
	
    word* indexOfNBlock;
	
    /// for variable block, valore da sommare per ottenere il numero di eventi (blocchi) reali.
    word *subFromNBlock;
	
    bool reset_output_stream;

	/// Indicates if the source data field is a recoursive block structure
    bool rblock;
	

};

}

#endif /* SourceDataField_H_HEADER_INCLUDED_89D3066E */
