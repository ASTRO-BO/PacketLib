/***************************************************************************
                          SDFBlockVariable.h  -  description
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
 
#ifndef _SDFBLOCKVARIABLE_H
#define _SDFBLOCKVARIABLE_H

#include "PacketLibDefinition.h"
#include "SourceDataField.h"
#include "SDFBVBlock.h"
#include "ConfigurationFile.h"
#include "Field.h"
#include "ByteStream.h"

namespace PacketLib
{

///	\brief Represents a source data field structered with blocks and with the number
/// of fields for each block variable. Layout 3 (see the Interface Control Document).
class SDFBlockVariable : public SourceDataField
{
public:
    virtual bool loadFields(InputText& fp) throw(PacketException*);

    SDFBlockVariable();

    virtual ~SDFBlockVariable();

    virtual Field* getFields(word index);

  
    virtual Field* getFields(word block, word index);

  
    virtual word getNumberOfFields();


    virtual bool setByteStream(ByteStreamPtr s);


    virtual dword getDimension();


    virtual dword getDimension(word nblock);


    /// Gets the total max dimension in bytes of source data field
    virtual dword getMaxDimension();


    virtual dword getMaxDimension(word nblock);


    /// Prints the value of each field of this part of packet
    virtual char** printValue(char* addString = "");

    /// Prints the structure of this part of packet
    virtual string* printStructure();


    virtual word getMaxNumberOfElements(word nblock);

    /// Returns the number of fields for each block
    virtual word getNumberOfFields(word block);


    virtual word getFieldValue(word index);


    virtual word getFieldValue(word block, word index);


    /// Sets the value of a field in the list of fields of this part of packet. Remember that
    /// if a predefined value is specified in the .stream, this method has not effect and the
    /// value contained in the .stream is used.
    /// \param index Represent the index in the list.
    /// \param value The value must be set.
    virtual void setFieldValue(word index, word value);

    /// Sets the value of a field in the list of fields of this part of packet. Remember that
    /// if a predefined value is specified in the .stream, this method has not effect and the
    /// value contained in the .stream is used.
    /// \param block The index of block.
    /// \param index Represent the index in the list.
    /// \param value The value must be set.
    virtual void setFieldValue(word block, word index, word value);


    virtual bool setOutputStream(ByteStreamPtr os, dword first);


    virtual ByteStreamPtr generateStream(bool bigendian);


    /// Get the number of elements for each block
    /// \param block The index of the blocks.
    virtual word getNumberOfRealElement(word block);

 
    /// Set the number of elements for each block.
    /// \param block The index of the block.
    /// \param value The number of elements.
    virtual void setNumberOfRealElement(word block, word value);


    /// Get a block
    /// \param nblock The index of the block.
    virtual SDFBVBlock* getBlock(word block);

private:

    SDFBVBlock* blocks;

    ByteStreamPtr tempBlock;
};

}
#endif                           /* SDFBLOCKVARIABLE_H_INCLUDED_97700169 */
