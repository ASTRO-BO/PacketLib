/***************************************************************************
                          SourceDataField  -  description
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001, 2014 by Andrea Bulgarelli
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
 
#include "SourceDataField.h"

using namespace PacketLib;

SourceDataField::SourceDataField(PartOfPacket* pop) 
{
    rblock = true;
    block = NULL;
    previous = pop;
	
	indexOfNBlock = new word(1);
    subFromNBlock = new word(1);
    maxNumberOfBlock = new word(1);
    numberOfRealDataBlock = new word(1);
    numberOfBlockFixed = new bool(1);
    indexOfNBlock[0] = 0;
    subFromNBlock[0] = 0;
    maxNumberOfBlock[0] = 0;
    numberOfRealDataBlock[0] = 0;
    numberOfBlockFixed[0] = false;
	
    reset_output_stream = true;
}

SourceDataField::~SourceDataField()
{
	delete indexOfNBlock;
    delete subFromNBlock;
    delete maxNumberOfBlock;
    delete numberOfRealDataBlock;
    delete numberOfBlockFixed;
	
    delete[] block;

}

bool SourceDataField::loadFields(InputText& fp) throw(PacketException*)
{
    try
    {
        numberOfRBlocks = 1;
        rblockFilename = new char* [numberOfRBlocks];
        numberOfBlockFixed[0] = true;
        maxNumberOfBlock[0] = 1;
        numberOfRealDataBlock[0] = 1;
        indexOfNBlock[0] = 0;
        subFromNBlock[0] = 0;
        rblockFilename[0]= (char*)"Source Data Field";
        nblockmax = 1;
        block = (SDFBlock*) new SDFBlock[nblockmax];
        block[0].setPreviousPop(previous);
        block[0].setRBlockType(0);
        block[0].setID(0);
        block[0].loadFields(fp);
        fp.setpos(0);
        /// It gets the [Identifiers] section
        fp.getLine("[Identifiers]");
        return true;
    }
    catch(PacketExceptionIO* e)
    {
        e->add(" - ");
        e->add("Configuration file: ");
        throw e;
    }
}

char* SourceDataField::printInHexadecimal()
{
    dword dim = getDimension();
    ByteStream b(stream->stream, dim, true);
    char* c = b.printStreamInHexadecimal();
    return c;
}

SDFBlock* SourceDataField::getBlock(word nblock,word rBlockIndex)
{
    return block[0].getBlock(nblock, rBlockIndex);
}


dword SourceDataField::getMaxDimension()
{
    return block[0].getMaxDimension();
}

dword SourceDataField::getDimension()
{
    return block[0].getDimension();
}

dword SourceDataField::getDimensionFixedPart()
{
    return block[0].fixed.getDimension();
}

void SourceDataField::setNumberOfRealDataBlock(word number, word rblockIndex)  throw (PacketException*)
{
    /// The block[0] is the only block present
    block[0].setNumberOfRealDataBlock(number, rblockIndex);
    reset_output_stream = true;
}


word SourceDataField::getNumberOfRealDataBlock(word rblockIndex)
{
    /// The block[0] is the only block present
    return  block[0].getNumberOfRealDataBlock(rblockIndex);
}


bool SourceDataField::setOutputStream(ByteStreamPtr os, dword first)
{
    return block[0].setOutputStream(os, first);
}

ByteStreamPtr SourceDataField::generateStream(bool bigendian)
{
    return block[0].generateStream(bigendian);
}

bool SourceDataField::setByteStream(ByteStreamPtr s, int decodeType)
{
    stream = s;
    return block[0].setByteStream(s, decodeType);
}

Field* SourceDataField::getFields(word index)
{
    return block[0].getFields(index);
}

word SourceDataField::getFieldValue(word index)
{
    return block[0].getFieldValue(index);
}

void SourceDataField::setFieldValue(word index, word value)
{
    return block[0].setFieldValue(index, value);
}

word SourceDataField::getNumberOfFields()
{
    return block[0].getNumberOfFields();
}

char** SourceDataField::printValue(char* addString)
{
    return block[0].printValue(addString);
}

void SourceDataField::printValueStdout()
{
    block[0].printValueStdout();
}

string* SourceDataField::printStructure()
{
    return block[0].printStructure();
}

bool SourceDataField::get_reset_output_stream() const
{
    return reset_output_stream;
}



void SourceDataField::set_reset_output_stream(bool value)
{
    reset_output_stream = value;
}


