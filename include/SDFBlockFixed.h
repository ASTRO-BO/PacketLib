/***************************************************************************
                          SDFBlockFixed.h  -  description
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
 
#ifndef _SDFBLOCKFIXED_H 
#define _SDFBLOCKFIXED_H

#include "PacketLibDefinition.h"
#include "SourceDataField.h"
#include "SDFBFBlock.h"
#include "ConfigurationFile.h"
#include "Field.h"
#include "ByteStream.h"
#include "PacketException.h"
#include "PacketExceptionFileFormat.h"

namespace PacketLib
{

///	\brief Represents a source data field structured with blocks but the number of
/// fields for each block are fixed. Layout 2 (see the Interface Control Document).
class SDFBlockFixed : public SourceDataField
{
public:
    virtual bool loadFields(InputText& fp) throw(PacketException*);

    SDFBlockFixed();

    virtual ~SDFBlockFixed();

    virtual Field* getFields(word index);

    virtual word getNumberOfFields();

    virtual bool setByteStream(ByteStream* s);

    /// Prints the value of each field of this part of packet.
    virtual char** printValue(char* addString = "");

    /// Get the number of bytes of this part of packet.
    virtual dword getDimension();

    /// Get the number of bytes of a block.
    virtual dword getDimension(word block);

    virtual dword getMaxDimension();

    virtual dword getMaxDimension(word nblock);

     /// Prints the structure of this part of packet.
    virtual string* printStructure();

    virtual Field* getFields(word block, word index);

    virtual word getFieldValue(word index);

    virtual word getFieldValue(word block, word index);

    /// Get a block
    /// \param nblock The index of the block
    virtual SDFBFBlock * getBlock(word nblock);

    /// Sets the value of a field in the list of fields of this part of packet. Remember that
    /// if a predefined value is specified in the .stream, this method has not effect and the
    /// value contained in the .stream is used.
    /// \param index Represent the index in the list.
    /// \param value The value must be set.
    virtual void setFieldValue(word index, word value);

    /// Sets the value of a field in the list of fields of this part of packet. Remember that
    /// if a predefined value is specified in the .stream, this method has not effect and the
    /// value contained in the .stream is used.
    /// \param index Represent the index in the list.
    /// \param value The value must be set.
    virtual void setFieldValue(word block, word index, word value);

    virtual bool setOutputStream(ByteStream* os, dword first);

    virtual ByteStream* generateStream(bool bigendian);

    /// Returns the number of fields for each block.
    virtual word getNumberOfFields(word block);

private:
    SDFBFBlock *block;

    ByteStream* tempBlock;
};

}
#endif                           /* SDFBLOCKFIXED_H_INCLUDED_B199A478 */
