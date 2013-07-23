/***************************************************************************
                          SourceDataField.h  -  description
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

#ifndef SOURCEDATAFIELD_H_INCLUDED_F4BDC5A4
#define SOURCEDATAFIELD_H_INCLUDED_F4BDC5A4

#include "PacketLibDefinition.h"
#include "PartOfPacket.h"

namespace PacketLib {

//##ModelId=3C0F6C190376
//##Documentation
//##	$Date: 2012/06/08 15:14:29 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/SourceDataField.h,v 1.10 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Id: SourceDataField.h,v 1.10 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Revision: 1.10 $
//##	\brief A generic source data field.
class SourceDataField : public PartOfPacket
{
    public:

        //##ModelId=3EADC1440383
        SourceDataField(const char* sdfName = 0);
	
	virtual ~SourceDataField();

        //##ModelId=3EADC1450058
        //##Documentation
        //## Gets the total max dimension in bytes of source data field
        virtual dword getMaxDimension() = 0;

        //##ModelId=3EADC1450316
        //##Documentation
        //## Gets the total max dimension in bytes of source data field for each block
        //## \param nbloc Number of block
        virtual dword getMaxDimension(word nblock);

        //##ModelId=3C9AEC090051
        //##Documentation
        //## Loads the field form .packet file. See PartOfPacket class.
        virtual bool loadFields(InputText& fp) throw(PacketException*) = 0 ;

        //##ModelId=3C301E8A0081
        //##Documentation
        //## \return true if this source data field is compounded of blocks.
        virtual bool isBlock();

        //##ModelId=3C347EA003C8
        //##Documentation
        //## \return true if the dimension of eache block is fixed.
        virtual bool isFixed();

        //##Documentation
        //## \return true if the packet is structured as a recursive block
        virtual bool isRBlock() { return rblock; };        

        //##ModelId=3C35EF40001F
        //##Documentation
        //## \return true is the number of block is fixed.
        virtual bool isNumberOfBlockFixed(word rblockIndex = 0);

        //##ModelId=3C35EF4303B7
        //##Documentation
        //## \return Returns the max number of block for this source data field.
        virtual word getMaxNumberOfBlock(word rblockIndex = 0);

        //##ModelId=3EADC147006C
        //##Documentation
        //## \return Returns the max number of elements for each block.
        //## \param nblock Number of block.
        virtual word getMaxNumberOfElements(word nblock);

        //##ModelId=3EADC1480173
        //##Documentation
        //## Gets the current dimension (in byte) of the source data field.
        virtual dword getDimension();

        //##ModelId=3EADC1490095
        //##Documentation
        //## Gets the current dimension (in byte) for a single block.
        //# \param block Number of block.
        virtual dword getDimension(word block);

        //##ModelId=3C35EF3C01C8
        //##Documentation
        //## Gets the index of field in the data field header that contains the number of block in the
        //## source data field.
        virtual word getIndexOfNBlock(word rblockIndex = 0);

        //##ModelId=3C9AEC0A01AD
        //##Documentation
        //## Sets the number of real data block for the current packet.
        virtual void setNumberOfRealDataBlock(word value, word rblockIndex = 0) throw (PacketException*);

        //##ModelId=3C9AEC0B006F
        virtual word getSubFromNBlock(word rblockIndex = 0);

        //##ModelId=3C9AEC0B011F
        //##Documentation
        //## \return Returns the number of real data block for the current packet.
        virtual word getNumberOfRealDataBlock(word rblockIndex = 0);

        //##ModelId=3C9AEC0B01CE
        //##Documentation
        //## Gets a field of the source data field.
        //## \param index The number of field in the source data field.
        //## \return The field.
        virtual Field* getFields(word index) = 0;

        //##ModelId=3C9AEC0C022B
        //##Documentation
        //## Gets a field of the source data field.
        //## \param block The block that contains the field
        //## \param index The number of field in the source data field (into the block).
        //## \return The field.
        virtual Field* getFields(word block, word index);

        //##ModelId=3EADC14B025B
        //##Documentation
        //## Gets a field value of the source data field.
        //## \param index The number of field in the source data field.
        //## \return The value of field.
        virtual word getFieldValue(word index) = 0;

        //##ModelId=3EADC14D000C
        //##Documentation
        //## Gets a field value of the source data field.
        //## \param block The block that contains the field.
        //## \param index The number of field in the source data field (into the block).
        //## \return The value of field.
        virtual word getFieldValue(word block, word index);
	
        //##ModelId=3EADC14D000C
        //##Documentation
        //## Gets a field value of the source data field of PTC=5, PFC=1. See comments on PartOfPacket for more details..
        //## \param block The block that contains the field.
        //## \param index The number of field in the source data field (into the block).
        //## \return The value of field.
        virtual float getFieldValue_5_1(word block, word index);
	
	virtual float getFieldValue_5_1(word index) {
		return PartOfPacket::getFieldValue_5_1(index);
	}
	
        //##ModelId=3EADC14D000C
        //##Documentation
        //## Set a field value of the source data field of PTC=5, PFC=1. See comments on PartOfPacket for more details..
        //## \param block The block that contains the field.
        //## \param index The number of field in the source data field (into the block).
	//## \param value The float
        virtual void setFieldValue_5_1(word block, word index, float value);
	
	virtual void setFieldValue_5_1(word index, float value) {
		PartOfPacket::setFieldValue_5_1(index, value);
	}
		
        //##ModelId=3EADC14D000C
        //##Documentation
        //## Gets a field value of the source data field of PTC=4, PFC=14. See comments on PartOfPacket for more details..
        //## \param block The block that contains the field.
        //## \param index The number of field in the source data field (into the block).
        //## \return The value of field.
        virtual signed long getFieldValue_4_14(word block, word index);
	
	virtual signed long getFieldValue_4_14(word index) {
		return PartOfPacket::getFieldValue_4_14(index);
	}

        //##ModelId=3EADC14D000C
        //##Documentation
        //## Set a field value of the source data field of PTC=4, PFC=14. See comments on PartOfPacket for more details..
        //## \param block The block that contains the field.
        //## \param index The number of field in the source data field (into the block).
	//## \param value The data to be set
        virtual void setFieldValue_4_14(word block, word index, signed long value);
	
	virtual void setFieldValue_4_14(word index, signed long value) {
		PartOfPacket::setFieldValue_4_14(index, value);
	}
	
	virtual signed long getFieldValue_4_13(word block, word index);	
	
	virtual signed long getFieldValue_4_13(word index) {
		return PartOfPacket::getFieldValue_4_13(index);
	}
	
	virtual void setFieldValue_4_13(word block, word index, signed long value) throw(PacketException*);
	
	virtual void setFieldValue_4_13(word index, signed long value) throw(PacketException*) {
		PartOfPacket::setFieldValue_4_13(index, value);
	}	
	
	virtual unsigned long getFieldValue_3_14(word block, word index); 
	
	virtual unsigned long getFieldValue_3_14(word index) {
		return PartOfPacket::getFieldValue_3_14(index);
	}
	
	virtual void setFieldValue_3_14(word block, word index, unsigned long value);
	
	virtual void setFieldValue_3_14(word index, unsigned long value) {
		PartOfPacket::setFieldValue_3_14(index, value);
	}
	
	virtual void setFieldValue_3_13(word block, word index, unsigned long value) throw(PacketException*);
	
	virtual void setFieldValue_3_13(word index, unsigned long value) throw(PacketException*) {
		PartOfPacket::setFieldValue_3_13(index, value);
	}

	virtual unsigned long getFieldValue_3_13(word block, word index);
	
	virtual unsigned long getFieldValue_3_13(word index) {
		return PartOfPacket::getFieldValue_3_13(index);
	}

        //##ModelId=3EADC14F0099
        //##Documentation
        //## Sets a field value of the source data field.
        //## \param index The number of field in the source data field.
        //## \param value The value must be setted.
        virtual void setFieldValue(word index, word value) = 0;

        //##ModelId=3EADC1510112
        //##Documentation
        //## Sets a field value of the source data field.
        //## \param block The block that contains the field.
        //## \param index The number of field in the source data field (into the block).
        //## \param value The value must be setted.
        virtual void setFieldValue(word block, word index, word value);

        //##ModelId=3EADC1540055
        //##Documentation
        //## Returns the number of fields for each block.
        virtual word getNumberOfFields(word block);

        //##ModelId=3EADC1550280
        //##Documentation
        //## Returns the total number of fields for the source data field.
        virtual word getNumberOfFields();

        //##ModelId=3EADC1560258
        //##Documentation
        //## Sets the number of real elements for each block.
        //## \param block Number of block.
        //## \value value The value must be setted.
        virtual void setNumberOfRealElement(word block, word value);

        //##ModelId=3C9AFF7A0170
        //##Documentation
        //## Returns the number of real elements for each block.
        virtual word getNumberOfRealElement(word block);

        //##ModelId=3EADC1590035
        bool get_reset_output_stream() const;

        //##ModelId=3EADC15A0015
        void set_reset_output_stream(bool value);
	
	char* printInHexadecimal();

    protected:
        //##ModelId=3C347EEA00C1
        //##Documentation
        //## This attribute indicates if the source data field is structured in block
        bool isblock;

        //##ModelId=3C347EF002A8
        //##Documentation
        //## Indicates if the dimension of block is fixed or variable
        bool fixed;

        //##Documentation
        //## Indicates if the source data field is a recoursive block structure
        bool rblock;        

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
        
        //##ModelId=405AA86B01A5
        word* indexOfNBlock;

        //##ModelId=405AA86B01C4
        //##Documentation
        //## for variable block, valore da sommare per ottenere il numero di eventi (blocchi) reali.
        word *subFromNBlock;

        //##ModelId=3EADC1440130
        bool reset_output_stream;

};

}
#endif                           /* SOURCEDATAFIELD_H_INCLUDED_F4BDC5A4 */
