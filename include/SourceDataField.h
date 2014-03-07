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

#ifndef _SOURCEDATAFIELD_H
#define _SOURCEDATAFIELD_H

#include "PacketLibDefinition.h"
#include "PartOfPacket.h"

namespace PacketLib
{

///	\brief A generic source data field.
class SourceDataField : public PartOfPacket
{
public:

    SourceDataField(const char* sdfName = 0);

    virtual ~SourceDataField();
	
	/// Sets the stream of byte. This method assigns the value of stream for each field of part of packet
    virtual bool setByteStream(ByteStreamPtr s, int decodeType) { PartOfPacket::setByteStream(s); return true; };

    /// Gets the total max dimension in bytes of source data field
    virtual dword getMaxDimension() = 0;

    /// Gets the total max dimension in bytes of source data field for each block
    /// \param nbloc Number of block
    virtual dword getMaxDimension(word nblock);

    /// Loads the field form .packet file. See PartOfPacket class.
    virtual bool loadFields(InputText& fp) throw(PacketException*) = 0 ;

    /// \return true if this source data field is compounded of blocks.
    virtual bool isBlock();

    /// \return true if the dimension of eache block is fixed.
    virtual bool isFixed();

    /// \return true if the packet is structured as a recursive block
    virtual bool isRBlock()
    {
        return rblock;
    };

    /// \return true is the number of block is fixed.
    virtual bool isNumberOfBlockFixed(word rblockIndex = 0);

    /// \return Returns the max number of block for this source data field.
    virtual word getMaxNumberOfBlock(word rblockIndex = 0);

    /// \return Returns the max number of elements for each block.
    /// \param nblock Number of block.
    virtual word getMaxNumberOfElements(word nblock);

    /// Gets the current dimension (in byte) of the source data field.
    virtual dword getDimension();
	
	virtual dword getDimensionFixedPart() = 0;

    /// Gets the current dimension (in byte) for a single block.
    /// \param block Number of block.
    virtual dword getDimension(word block);

    /// Gets the index of field in the data field header that contains the number of block in the
    /// source data field.
    virtual word getIndexOfNBlock(word rblockIndex = 0);

    /// Sets the number of real data block for the current packet.
    virtual void setNumberOfRealDataBlock(word value, word rblockIndex = 0) throw (PacketException*);

    virtual word getSubFromNBlock(word rblockIndex = 0);

    /// \return Returns the number of real data block for the current packet.
    virtual word getNumberOfRealDataBlock(word rblockIndex = 0);

    /// Gets a field of the source data field.
    /// \param index The number of field in the source data field.
    /// \return The field.
    virtual Field* getFields(word index) = 0;

    /// Gets a field of the source data field.
    /// \param block The block that contains the field
    /// \param index The number of field in the source data field (into the block).
    /// \return The field.
    virtual Field* getFields(word block, word index);

    /// Gets a field value of the source data field.
    /// \param index The number of field in the source data field.
    /// \return The value of field.
    virtual word getFieldValue(word index) = 0;

    /// Gets a field value of the source data field.
    /// \param block The block that contains the field.
    /// \param index The number of field in the source data field (into the block).
    /// \return The value of field.
    virtual word getFieldValue(word block, word index);

    /// Gets a field value of the source data field of PTC=5, PFC=1. See comments on PartOfPacket for more details..
    /// \param block The block that contains the field.
    /// \param index The number of field in the source data field (into the block).
    /// \return The value of field.
    virtual float getFieldValue_5_1(word block, word index);

    virtual float getFieldValue_5_1(word index)
    {
        return PartOfPacket::getFieldValue_5_1(index);
    }

    /// Set a field value of the source data field of PTC=5, PFC=1. See comments on PartOfPacket for more details..
    /// \param block The block that contains the field.
    /// \param index The number of field in the source data field (into the block).
    /// \param value The float
    virtual void setFieldValue_5_1(word block, word index, float value);

    virtual void setFieldValue_5_1(word index, float value)
    {
        PartOfPacket::setFieldValue_5_1(index, value);
    }

    /// Gets a field value of the source data field of PTC=4, PFC=14. See comments on PartOfPacket for more details..
    /// \param block The block that contains the field.
    /// \param index The number of field in the source data field (into the block).
    /// \return The value of field.
    virtual signed long getFieldValue_4_14(word block, word index);

    virtual signed long getFieldValue_4_14(word index)
    {
        return PartOfPacket::getFieldValue_4_14(index);
    }


    /// Set a field value of the source data field of PTC=4, PFC=14. See comments on PartOfPacket for more details..
    /// \param block The block that contains the field.
    /// \param index The number of field in the source data field (into the block).
    /// \param value The data to be set
    virtual void setFieldValue_4_14(word block, word index, signed long value);

    virtual void setFieldValue_4_14(word index, signed long value)
    {
        PartOfPacket::setFieldValue_4_14(index, value);
    }

    virtual signed long getFieldValue_4_13(word block, word index);

    virtual signed long getFieldValue_4_13(word index)
    {
        return PartOfPacket::getFieldValue_4_13(index);
    }

    virtual void setFieldValue_4_13(word block, word index, signed long value) throw(PacketException*);

    virtual void setFieldValue_4_13(word index, signed long value) throw(PacketException*)
    {
        PartOfPacket::setFieldValue_4_13(index, value);
    }

    virtual unsigned long getFieldValue_3_14(word block, word index);

    virtual unsigned long getFieldValue_3_14(word index)
    {
        return PartOfPacket::getFieldValue_3_14(index);
    }

    virtual void setFieldValue_3_14(word block, word index, unsigned long value);

    virtual void setFieldValue_3_14(word index, unsigned long value)
    {
        PartOfPacket::setFieldValue_3_14(index, value);
    }

    virtual void setFieldValue_3_13(word block, word index, unsigned long value) throw(PacketException*);

    virtual void setFieldValue_3_13(word index, unsigned long value) throw(PacketException*)
    {
        PartOfPacket::setFieldValue_3_13(index, value);
    }

    virtual unsigned long getFieldValue_3_13(word block, word index);

    virtual unsigned long getFieldValue_3_13(word index)
    {
        return PartOfPacket::getFieldValue_3_13(index);
    }

    /// Sets a field value of the source data field.
    /// \param index The number of field in the source data field.
    /// \param value The value must be set.
    virtual void setFieldValue(word index, word value) = 0;

    /// Sets a field value of the source data field.
    /// \param block The block that contains the field.
    /// \param index The number of field in the source data field (into the block).
    /// \param value The value must be set.
    virtual void setFieldValue(word block, word index, word value);

    /// Returns the number of fields for each block.
    virtual word getNumberOfFields(word block);

    /// Returns the total number of fields for the source data field.
    virtual word getNumberOfFields();

    /// Sets the number of real elements for each block.
    /// \param block Number of block.
    /// \value value The value must be set.
    virtual void setNumberOfRealElement(word block, word value);

    /// Returns the number of real elements for each block.
    virtual word getNumberOfRealElement(word block);

    bool get_reset_output_stream() const;

    void set_reset_output_stream(bool value);

    char* printInHexadecimal();

protected:
    /// This attribute indicates if the source data field is structured in block
    bool isblock;

    /// Indicates if the dimension of block is fixed or variable
    bool fixed;

    /// Indicates if the source data field is a recoursive block structure
    bool rblock;

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

};

}
#endif                           /* SOURCEDATAFIELD_H_INCLUDED_F4BDC5A4 */
