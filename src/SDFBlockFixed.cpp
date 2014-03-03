/***************************************************************************
                          SDFBlockFixed.cpp  -  description
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
#include "SDFBlockFixed.h"
#include "ByteStream.h"
#include "Field.h"
#include "ConfigurationFile.h"
#include "MemoryBuffer.h"

using namespace PacketLib;


bool SDFBlockFixed::loadFields(InputText& fp) throw(PacketException*)
{
    char* line;
    bool first1 = true;
    MemoryBuffer* buffer1;

    //return PartOfPacket::loadFields(fp);
    line = fp.getLine();
    if(strcmp(line, "fixed") == 0)
        numberOfBlockFixed[0] = true;
    else
        numberOfBlockFixed[0] = false;
    //delete[] line;

    line = fp.getLine();
    maxNumberOfBlock[0] = atoi(line);
    //delete[] line;

    if(numberOfBlockFixed[0])
        numberOfRealDataBlock[0] = maxNumberOfBlock[0];

    line = fp.getLine();
    indexOfNBlock[0] = atoi(line);
    //delete[] line;

    line = fp.getLine();
    subFromNBlock[0] =  atoi(line);
    //delete[] line;

    block = (SDFBFBlock*) new SDFBFBlock[maxNumberOfBlock[0]];

    /// find the [SourceDataFieldBlock] section
    if(strlen(line=fp.getLine("[SourceDataFieldBlock]")) != 0)
    {
        PRINTDEBUG("Found [SourceDataFieldBlock]");
        if(first1)
        {
            buffer1 = block[0].loadFieldsInBuffer(fp);
            first1 = false;
        }
        buffer1->readRewind();
        for(int i=0; i<maxNumberOfBlock[0]; i++)
        {
            if(block[i].loadFields(buffer1))
            {
                if(i != maxNumberOfBlock[0] - 1)
                    buffer1->readRewind();
            }
        }
    }
    else
        throw new PacketExceptionFileFormat("Section [SourceDataFieldBlock] not found.");
    delete buffer1;
    return true;
}



SDFBlockFixed::SDFBlockFixed() : SourceDataField("SDF Block Fixed")
{
    isblock = true;
    fixed = true;
    rblock = false;
    block = NULL;
    subFromNBlock[0] = 0;
    tempBlock = ByteStreamPtr(new ByteStream());
}



SDFBlockFixed::~SDFBlockFixed()
{
    //for(int i=0; i< maxNumberOfBlock; i++)
    //	delete &block[i];
}


Field* SDFBlockFixed::getFields(word index)
{
    word nblock = getNumberOfRealDataBlock();
    word dim = 0;
    word precdim = 0;
    for(int i=0; i< nblock; i++)
    {
        precdim = dim;
        dim += block[i].getNumberOfFields();
        if(dim>index)
            return block[i].getFields(index-precdim);
    }
    return 0;
}



Field* SDFBlockFixed::getFields(word nblock, word index)
{
    if(nblock < numberOfRealDataBlock[0] && index < block[nblock].getNumberOfFields())
        return block[nblock].getFields(index);
    else
        return 0;
}



word SDFBlockFixed::getFieldValue(word index)
{
    Field* f = getFields(index);
    if(f != 0)
        return f->value;
    else
        return 0;
}



word SDFBlockFixed::getFieldValue(word block, word index)
{
    Field* f = getFields(block, index);
    if(f != 0)
        return f->value;
    else
        return 0;
}



void SDFBlockFixed::setFieldValue(word index, word value)
{
    Field* f = getFields(index);
    if(f != 0)
        f->value = (value & pattern[f->getDimension()]);
}


void SDFBlockFixed::setFieldValue(word block, word index, word value)
{
    Field* f = getFields(block, index);
    if(f != 0)
        f->value = (value & pattern[f->getDimension()]);
}


word SDFBlockFixed::getNumberOfFields()
{
    word n_block = getNumberOfRealDataBlock();
    return block[0].getNumberOfFields() * n_block;
}



bool SDFBlockFixed::setByteStream(ByteStreamPtr s)
{
    bool b;
    word bytestart=0, bytestop=0;
    stream = s;
    word n_block = getNumberOfRealDataBlock();
    /// It controls the blocks maximum dimension
    word n_block_max = getMaxNumberOfBlock();
    if(n_block > n_block_max)
    {
        PRINTERROR("Error in SDFBlockFixed n_block > n_block_max");
        return false;
    }
    word block_dimension = block[0].getDimension();
    for(int i=0; i<n_block; i++)
    {
        bytestop = bytestart + block_dimension - 1;
        b = tempBlock->setStream(s, bytestart, bytestop);
        // b = s->getSubByteStream(bytestart, bytestop);

        if(b)
        {
            bool ret = block[i].setByteStream(tempBlock);
            if(!ret)
                return false;
        }
        else
            return false;
        bytestart = bytestop + 1;
    }
    return true;                 //TODO
}



char** SDFBlockFixed::printValue(char* addString)
{
    char **c;                    // = new char[1];
    //char *s = new char[1];
    char **cc;
    string s1 = "";
    long index;
    word n_block = getNumberOfRealDataBlock();
    word nf = getNumberOfFields() + n_block + 1;
    //	cc = (char**) malloc(sizeof(char*) * (nf));
    cc = new char* [nf];
    index = 0;
    for(int i=0; i<n_block; i++)
    {
        c = (char**) block[i].printValue(addString);
        //sprintf(s, "BLOCK NUMBER %d ----------------------- \n", i);
        //			s1 += s;
        //			s1 += c;
        //cc[index] = s;

        //index++;
        for(int j=0; c[j] != 0; j++, index++)
        {
            cc[index] = c[j];
            //printf("%p\n", cc[index]);
            //cout<< cc[index] << endl;
        }
    }
    //	cc = (char*) s1.c_str();
    cc[index] = 0;
    return cc;
}


dword SDFBlockFixed::getDimension()
{
    dword dimOfEventBlock;        //Dimensione di ogni event
    dimOfEventBlock = block[0].getDimension();
    //numero di eventi letti dallo stream
    return dimOfEventBlock * numberOfRealDataBlock[0];
}


dword SDFBlockFixed::getDimension(word nblock)
{
    if(nblock < numberOfRealDataBlock[0])
        return block[nblock].getDimension();
    else
        return 0;
}



dword SDFBlockFixed::getMaxDimension()
{
	/// Event dimension
    dword dimOfEventBlock = 0;
    if(block != NULL)
        dimOfEventBlock = block[0].getDimension();
    else
    {
        throw PacketException("Error on SDFBlockFixed::getMaxDimension: block is NULL");
    }
    return dimOfEventBlock * maxNumberOfBlock[0];
}



dword SDFBlockFixed::getMaxDimension(word nblock)
{
    if(nblock < numberOfRealDataBlock[0])
        return block[nblock].getDimension();
    else
        return 0;
}



string* SDFBlockFixed::printStructure()
{
    return new string("string* SDFBlockFixed::printStructure() - TODO");
}


bool SDFBlockFixed::setOutputStream(ByteStreamPtr os, dword first)
{
    dword mnb = getNumberOfRealDataBlock();
    dword start = first;
    outputstream = ByteStreamPtr(new ByteStream((os->stream + first), getDimension(), os->isBigendian()));
    for(dword i = 0; i<mnb; i++)
    {
        block[i].setOutputStream(os, start);
        start += block[i].getDimension();
    }
    return true;
}


ByteStreamPtr SDFBlockFixed::generateStream(bool bigendian)
{
    word mnb = getNumberOfRealDataBlock();
    for(word i = 0; i<mnb; i++)
    {
        block[i].generateStream(bigendian);
    }
    return outputstream;
}


word SDFBlockFixed::getNumberOfFields(word nblock)
{
    if(nblock < numberOfRealDataBlock[0])
        return block[nblock].getNumberOfFields();
    else
        return 0;
}

SDFBFBlock* SDFBlockFixed::getBlock(word nblock)
{
    if(nblock < maxNumberOfBlock[0])
        return &block[nblock];
    return 0;
}

