/***************************************************************************
                          SDFBlockVariable.h  -  description
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
#ifndef SDFBLOCKVARIABLE_H_INCLUDED_97700169
#define SDFBLOCKVARIABLE_H_INCLUDED_97700169

#include "PacketLibDefinition.h"
#include "SourceDataField.h"
#include "SDFBVBlock.h"
#include "ConfigurationFile.h"
#include "Field.h"
#include "ByteStream.h"

namespace PacketLib {

//##Documentation
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/SDFBlockVariable.h,v 1.3 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: SDFBlockVariable.h,v 1.3 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.3 $
//##	\brief Represents a source data field structered with blocks and with the number
//## of fields for each block variable. Layout 3 (see the Interface Control Document).
class SDFBlockVariable : public SourceDataField
{
    public:
        //##ModelId=3EADC14300BA
        virtual bool loadFields(InputText& fp) throw(PacketException*);

        //##ModelId=3EADC14300C0
        SDFBlockVariable();

        //##ModelId=3EADC14300C1
        virtual ~SDFBlockVariable();

        //##ModelId=3EADC14300C3
        virtual Field* getFields(word index);

        //##ModelId=3EADC14300C9
        virtual Field* getFields(word block, word index);

        //##ModelId=3EADC14300D1
        virtual word getNumberOfFields();

        //##ModelId=3EADC14300D4
        virtual bool setByteStream(ByteStream* s);

        //##ModelId=3EADC14300D9
        virtual word getDimension();

        //##ModelId=3EADC14300DB
        virtual word getDimension(word nblock);

        //##ModelId=3EADC14300E0
        //##Documentation
        //## Gets the total max dimension in bytes of source data field
        virtual word getMaxDimension();

        //##ModelId=3EADC14300E2
        virtual word getMaxDimension(word nblock);

        //##ModelId=3EADC14300E7
        //##Documentation
        //## Prints the value of each field of this part of packet
        virtual char** printValue(char* addString = "");

        //##ModelId=3EADC14300ED
        //##Documentation
        //## Prints the structure of this part of packet
        virtual string* printStructure();

        //##ModelId=3EADC14300EF
        virtual word getMaxNumberOfElements(word nblock);

        //##ModelId=3EADC14300F4
        //##Documentation
        //## Returns the number of fields for each block
        virtual word getNumberOfFields(word block);

        //##ModelId=3EADC14300FA
        virtual word getFieldValue(word index);

        //##ModelId=3EADC14300FF
        virtual word getFieldValue(word block, word index);

	//##Documentation
        //## Sets the value of a field in the list of fields of this part of packet. Remember that
	//## if a predefined value is specified in the .stream, this method has not effect and the 
	//## value contained in the .stream is used.
        //## \param index Represent the index in the list.
        //## \param value The value must be setted.
        virtual void setFieldValue(word index, word value);

	//##Documentation
        //## Sets the value of a field in the list of fields of this part of packet. Remember that
	//## if a predefined value is specified in the .stream, this method has not effect and the 
	//## value contained in the .stream is used.
	//## \param block The index of block.
        //## \param index Represent the index in the list.
        //## \param value The value must be setted.
        virtual void setFieldValue(word block, word index, word value);

        //##ModelId=3EADC143011A
        virtual bool setOutputStream(ByteStream* os, word first);

        //##ModelId=3EADC1430122
        virtual ByteStream* generateStream(bool bigendian);

        //##ModelId=3EADC1430127
	//##Documentation
	//## Get the number of elements for each block
	//## \param block The index of the blocks.
        virtual word getNumberOfRealElement(word block);

        //##ModelId=3EADC143012C
	//##Documentation
	//## Set the number of elements for each block.
	//## \param block The index of the block.
	//## \param value The number of elements.
        virtual void setNumberOfRealElement(word block, word value);
	
	//##Documentation
	//## Get a block
	//## \param nblock The index of the block.	
	virtual SDFBVBlock* getBlock(word block);

    private:
        //##ModelId=3EADC14300AD
        SDFBVBlock* blocks;

	      //##ModelId=3EADC14300B3
        ByteStream* tempBlock;
};

}
#endif                           /* SDFBLOCKVARIABLE_H_INCLUDED_97700169 */
