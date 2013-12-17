/***************************************************************************
                          SDFRBlock.cpp  -  description
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
 
#include "SDFRBlock.h"

using namespace PacketLib;

SDFRBlock::SDFRBlock(PartOfPacket* pop) : SourceDataField("SDF Recoursive Block")
{
    isblock = false;
    fixed = false;
    rblock = true;
    block = NULL;
    previous = pop;
}

SDFRBlock::~SDFRBlock()
{

    delete[] block;

}

bool SDFRBlock::loadFields(InputText& fp) throw(PacketException*)
{
    try
    {
        char* line;
        numberOfRBlocks = 1;
        rblockFilename = new char* [numberOfRBlocks];
        numberOfBlockFixed[0] = true;
        maxNumberOfBlock[0] = 1;
        numberOfRealDataBlock[0] = 1;
        indexOfNBlock[0] = 0;
        subFromNBlock[0] = 0;
        rblockFilename[0]= (char*)"Source Data Field";
        nblockmax = 1;
        block = (SDFRBBlock*) new SDFRBBlock[nblockmax];
        block[0].setPreviousPop(previous);
        block[0].setRBlockType(0);
        block[0].setID(0);
        block[0].loadFields(fp);
        fp.setpos(0);
        /// It gets the [Identifiers] section
        line = fp.getLine("[Identifiers]"); 
        return true;
    }
    catch(PacketExceptionIO* e)
    {
        e->add(" - ");
        e->add("Configuration file: ");
        throw e;
    }
}

SDFRBBlock* SDFRBlock::getBlock(word nblock,word rBlockIndex)
{
    return block[0].getBlock(nblock, rBlockIndex);
}

dword SDFRBlock::getMaxDimension()
{
    return block[0].getMaxDimension();
}

dword SDFRBlock::getDimension()
{
    return block[0].getDimension();
}

void SDFRBlock::setNumberOfRealDataBlock(word number, word rblockIndex)  throw (PacketException*)
{
    /// The block[0] is the only block present
    block[0].setNumberOfRealDataBlock(number, rblockIndex);
    reset_output_stream = true;
}


word SDFRBlock::getNumberOfRealDataBlock(word rblockIndex)
{
    /// The block[0] is the only block present
    return  block[0].getNumberOfRealDataBlock(rblockIndex);
}


bool SDFRBlock::setOutputStream(ByteStream* os, dword first)
{
    return block[0].setOutputStream(os, first);
}

ByteStream* SDFRBlock::generateStream(bool bigendian)
{
    return block[0].generateStream(bigendian);
}

bool SDFRBlock::setByteStream(ByteStream* s)
{
    stream = s;
    return block[0].setByteStream(s);
}

Field* SDFRBlock::getFields(word index)
{
    return block[0].getFields(index);
}

word SDFRBlock::getFieldValue(word index)
{
    return block[0].getFieldValue(index);
}

void SDFRBlock::setFieldValue(word index, word value)
{
    return block[0].setFieldValue(index, value);
}

word SDFRBlock::getNumberOfFields()
{
    return block[0].getNumberOfFields();
}

char** SDFRBlock::printValue(char* addString)
{
    return block[0].printValue(addString);
}

void SDFRBlock::printValueStdout()
{
    block[0].printValueStdout();
}

string* SDFRBlock::printStructure()
{
    return block[0].printStructure();
}


