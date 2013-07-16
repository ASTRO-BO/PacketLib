/***************************************************************************
                          SDFBlockFixed.h  -  description
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
#ifndef SDFBLOCKFIXED_H_INCLUDED_B199A478
#define SDFBLOCKFIXED_H_INCLUDED_B199A478

#include "PacketLibDefinition.h"
#include "SourceDataField.h"
#include "SDFBFBlock.h"
#include "ConfigurationFile.h"
#include "Field.h"
#include "ByteStream.h"
#include "PacketException.h"
#include "PacketExceptionFileFormat.h"

namespace PacketLib {

//##Documentation
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/SDFBlockFixed.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: SDFBlockFixed.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.2 $
//##	\brief Represents a source data field structured with blocks but the number of
//## fields for each block are fixed. Layout 2 (see the Interface Control Document).
class SDFBlockFixed : public SourceDataField
{
    public:
        //##ModelId=3EADC1430039
        virtual bool loadFields(InputText& fp) throw(PacketException*);

        //##ModelId=3EADC143003F
        SDFBlockFixed();

        //##ModelId=3EADC1430041
        virtual ~SDFBlockFixed();

        //##ModelId=3EADC1430043
        virtual Field* getFields(word index);

        //##ModelId=3EADC1430047
        virtual word getNumberOfFields();

        //##ModelId=3EADC143004A
        virtual bool setByteStream(ByteStream* s);

        //##ModelId=3EADC143004F
        //##Documentation
        //## Prints the value of each field of this part of packet.
        virtual char** printValue(char* addString = "");

        //##ModelId=3EADC1430054
	//##Documentation
	//## Get the number of bytes of this part of packet.
        virtual word getDimension();

        //##ModelId=3EADC1430057
	//## Get the number of bytes of a block.
        virtual word getDimension(word block);

        //##ModelId=3EADC143005C
        virtual word getMaxDimension();

        //##ModelId=3EADC143005E
        virtual word getMaxDimension(word nblock);

        //##ModelId=3EADC1430063
        //##Documentation
        //## Prints the structure of this part of packet.
        virtual string* printStructure();

        //##ModelId=3EADC1430065
        virtual Field* getFields(word block, word index);

        //##ModelId=3EADC143006D
        virtual word getFieldValue(word index);

        //##ModelId=3EADC1430072
        virtual word getFieldValue(word block, word index);
	
	//##Documentation
	//## Get a block
	//## \param nblock The index of the block
	virtual SDFBFBlock * getBlock(word nblock);

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
        //## \param index Represent the index in the list.
        //## \param value The value must be setted.
        virtual void setFieldValue(word block, word index, word value);

        //##ModelId=3EADC143008D
        virtual bool setOutputStream(ByteStream* os, word first);

        //##ModelId=3EADC1430094
        virtual ByteStream* generateStream(bool bigendian);

        //##ModelId=3EADC1430099
        //##Documentation
        //## Returns the number of fields for each block.
        virtual word getNumberOfFields(word block);

    private:
        //##ModelId=3EADC143002B
        SDFBFBlock *block;

	//##ModelId=3EADC1430032
        ByteStream* tempBlock;
};

}
#endif                           /* SDFBLOCKFIXED_H_INCLUDED_B199A478 */
