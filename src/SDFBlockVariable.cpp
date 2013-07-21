#include "SDFBlockVariable.h"
#include "ByteStream.h"
#include "Field.h"
#include "ConfigurationFile.h"
#include "PacketExceptionFileFormat.h"
#include "MemoryBuffer.h"

using namespace PacketLib;

//##ModelId=3C3576980390
bool SDFBlockVariable::loadFields(InputText& fp) throw(PacketException*)
{
    try
    {
        char* line, *linesection;
        word indexOfNElement;
        unsigned addToNElements;
        word maxNumberOfElement;
        bool first1 = true, first2 = true;
        MemoryBuffer* buffer1, *buffer2;

        line = fp.getLine();
        if(strcmp(line, "fixed") == 0)
            numberOfBlockFixed[0] = true;
        else
            numberOfBlockFixed[0] = false;
        //delete line;

        //numero massimo di blocchi presenti
        line = fp.getLine();
        maxNumberOfBlock[0] = atoi(line);
        //delete line;
	
	if(numberOfBlockFixed[0])
    		numberOfRealDataBlock[0] = maxNumberOfBlock[0];

        //indice del fields che contiene il numero di blocchi presenti
        line = fp.getLine();
        indexOfNBlock[0] = atoi(line);
        //delete line;

        //valore da sottrarre al valore nel field dell'indice precedente per ottenere il numero reale di blocchi
        line = fp.getLine();
        subFromNBlock[0] =  atoi(line);
        //delete line;

        blocks = (SDFBVBlock*) new SDFBVBlock[maxNumberOfBlock[0]];

        //find the [SourceDataFieldBlock] section
        if(strlen(line=fp.getLine("[SourceDataFieldBlockFixed]")) != 0)
        {
            if(first1)
            {
                buffer1 = blocks[0].fixed.loadFieldsInBuffer(fp);
                //first1=false;
            }
            buffer1->readRewind();
            //fp.memBookmarkPos();
            for(int i=0; i<maxNumberOfBlock[0]; i++)
            {
                //read supposed number (or max number) of element
                //line = fp.getLine();
                line = buffer1->getbuffer();
                maxNumberOfElement = atoi(line);
                //			delete line;

                //index of field in the [SourceDataFieldBlockFixed] section wich rappresent the number of element (the number of bar) of the block
                //		line = fp.getLine();
                line = buffer1->getbuffer();
                indexOfNElement = atoi(line);
                //delete line;

                //numero da sommare per ottenere il numero di elements reale
                //line = fp.getLine();
                line = buffer1->getbuffer();
                addToNElements   = atoi(line);
                //delete line;

                if(blocks[i].fixed.loadFields(buffer1))
                {
                    blocks[i].fixed.setIndexOfNElement(indexOfNElement);
                    blocks[i].fixed.setAddToNElement(addToNElements);
                    blocks[i].fixed.setMaxNumberOfElement(maxNumberOfElement);
                    if(first1)
                    {
                        linesection=fp.getLastLineRead();
                        first1=false;
                    }
                    //line = fp.getLine();
                    if(strcmp(linesection, "[SourceDataFieldBlockVariable]") == 0)
                    {
                        //					delete line;
                        //alloca lo spazio necessario
                        blocks[i].variables = (SDFBVBlockVariable*) new SDFBVBlockVariable[maxNumberOfElement];

                        if(first2)
                        {
                            buffer2 = blocks[i].variables[0].loadFieldsInBuffer(fp);
                            first2 = false;
                        }
                        buffer2->readRewind();
                        //memorizza il bookmark
                        //					long pos = fp.getpos();
                        for(int j=0; j<maxNumberOfElement; j++)
                            if(blocks[i].variables[j].loadFields(buffer2))
                        {
                            if(j != maxNumberOfElement - 1)
                            {
                                //							fp.setpos(pos);
                                buffer2->readRewind();
                            }
                        }
                        else
                            throw new PacketExceptionFileFormat("No load fields in section [SourceDataFieldBlockVariable].");
                    }
                    else
                        throw new PacketExceptionFileFormat("Section [SourceDataFieldBlockVariable] not found.");
                    if(i != maxNumberOfBlock[0] - 1)
                        //fp.setLastBookmarkPos();
                        buffer1->readRewind();
                }
                else
                    throw new PacketExceptionFileFormat("No load fields in section [SourceDataFieldBlockFixed].");
            }
        }
        else
            throw new PacketExceptionFileFormat("Section [SourceDataFieldBlockFixed] not found.");
        return true;
    }
    catch(PacketExceptionIO* e)
    {
        e->add(" - ");
        //e->add(fp.getFileName());
        e->add("Configuration file: ");
        throw e;
    }
}


//##ModelId=3C357B8103E6
SDFBlockVariable::SDFBlockVariable() : SourceDataField("SDF Block Variable")
{
    isblock = true;
    fixed = false;
    rblock = false;
    blocks = 0;
    tempBlock = new ByteStream();
}


//##ModelId=3C357B85035D
SDFBlockVariable::~SDFBlockVariable()
{
}


//##ModelId=3A54BDE40309
word SDFBlockVariable::getNumberOfFields()
{
    word number_of_real_element;
    word n_fields = 0;
    word nfv = blocks[0].variables[0].getNumberOfFields();
    word nff = blocks[0].fixed.getNumberOfFields();
    word n_block = getNumberOfRealDataBlock();
    for(word i = 0; i< n_block; i++)
    {
        number_of_real_element = blocks[i].fixed.getNumberOfRealElement();
        n_fields += number_of_real_element * nfv + nff;
    }
    return n_fields;
}


//##ModelId=3A54BDE4032D
bool SDFBlockVariable::setByteStream(ByteStream* s)
{
    word bytestart=0, bytestop=0;
    word number_of_real_element;
    stream = s;
    word n_block = getNumberOfRealDataBlock();
    word dim_of_fixed_part = blocks[0].fixed.getDimension();
    word dim_of_single_variable_part = blocks[0].variables[0].getDimension();

    bytestop =  dim_of_fixed_part - 1;
    for(word i = 0; i< n_block; i++)
    {
        if(tempBlock->setStream(s, bytestart, bytestop))
            if(!blocks[i].fixed.setByteStream(tempBlock))
                return false;
        number_of_real_element = blocks[i].fixed.getNumberOfRealElement();
        for(word j = 0; j<number_of_real_element; j++)
        {
            bytestart = bytestop + 1;
            bytestop =  bytestop + dim_of_single_variable_part;
            if(tempBlock->setStream(s, bytestart, bytestop))
                if(!blocks[i].variables[j].setByteStream(tempBlock))
                    return false;
        }
        bytestart = bytestop + 1;
        bytestop =  bytestop + dim_of_fixed_part;
    }

    return true;
}


//##ModelId=3A54BDE40376
word SDFBlockVariable::getDimension()
{
    word nb = getNumberOfRealDataBlock();
    word dim = 0;
    for(word i=0 ; i<nb; i++)
        dim += blocks[i].getDimension();
    return dim;
}


//##ModelId=3DA3E5DB0104
word SDFBlockVariable::getMaxDimension(word nblock)
{
    if(nblock < numberOfRealDataBlock[0])
        return blocks[nblock].getMaxDimension();
    else
        return 0;
}


//##ModelId=3DA3E5D900AA
word SDFBlockVariable::getDimension(word block)
{
    if(block < numberOfRealDataBlock[0])
        return blocks[block].getDimension();
    else
        return 0;
}


//##ModelId=3DA3E5DA01EA
word SDFBlockVariable::getMaxDimension()
{
    word nb = getMaxNumberOfBlock();
    word dim = 0;
    for(word i=0 ; i<nb; i++)
        dim += blocks[i].getMaxDimension();
    return dim;
}


//##ModelId=3A54BDE40351
char** SDFBlockVariable::printValue(char* addString)
{
    char** cc;
    char** ct;
    word index=0;
    word number_of_real_element;
    word ntf = getNumberOfFields();
    word n_block = getNumberOfRealDataBlock();
    cc = new char* [ntf+1];
    for(word i = 0; i< n_block; i++)
    {

        ct = (char**) blocks[i].fixed.printValue(addString);
        for(int ii=0; ct[ii] != 0; ii++)
        {
            cc[index] = ct[ii];
            index++;
        }

        number_of_real_element = blocks[i].fixed.getNumberOfRealElement();
        for(word j = 0; j<number_of_real_element; j++)
        {
            ct = (char**) blocks[i].variables[j].printValue(addString);
            for(int ii=0; ct[ii] != 0; ii++)
            {
                //char *c = ct[ii];
                cc[index] = ct[ii];
                index++;
            }
        }
    }
    cc[index] = '\0';
    return cc;
}


//##ModelId=3C35F9580094
string* SDFBlockVariable::printStructure()
{
    return new string("string* SDFBlockVariable::printStructure() - TODO");
}


//##ModelId=3C9AED040307
Field* SDFBlockVariable::getFields(word block, word index)
{
    if(block < numberOfRealDataBlock[0] && index < blocks[block].getNumberOfFields())
        return blocks[block].getFields(index);
    else
        return 0;
};

Field* SDFBlockVariable::getFields(word index)
{
    word nblock = getNumberOfRealDataBlock();
    word dim = 0;
    word precdim = 0;
    for(word i=0; i< nblock; i++)
    {
        precdim = dim;
        dim += blocks[i].getNumberOfFields();
        if(dim>index)
            return blocks[i].getFields(index-precdim);
    }
    return 0;
}


//##ModelId=3C9AFF9E0157
word SDFBlockVariable::getNumberOfRealElement(word block)
{
    return blocks[block].fixed.getNumberOfRealElement();
};

//##ModelId=3DA3E5F002E4
void SDFBlockVariable::setNumberOfRealElement(word nblock, word value)
{
    if(nblock < numberOfRealDataBlock[0])
        blocks[nblock].fixed.setNumberOfRealElement(value);
    else
        blocks[nblock].fixed.setNumberOfRealElement(maxNumberOfBlock[0]);
    reset_output_stream = true;
};

//##ModelId=3DA3E5DC02E4
word SDFBlockVariable::getMaxNumberOfElements(word block)
{
    return blocks[block].fixed.getMaxNumberOfElement();
}


//##ModelId=3DA3E5DE0154
word SDFBlockVariable::getNumberOfFields(word nblock)
{
    if(nblock < numberOfRealDataBlock[0])
        return blocks[nblock].getNumberOfFields();
    else
        return 0;
}


//##ModelId=3DA3E5E00028
word SDFBlockVariable::getFieldValue(word index)
{
    Field* f = getFields(index);
    if(f != 0)
        return f->value;
    else
        return 0;
}


//##ModelId=3DA3E5E10352
word SDFBlockVariable::getFieldValue(word block, word index)
{
    Field* f = getFields(block, index);
    if(f != 0)
        return f->value;
    else
        return 0;
}


//##ModelId=3DA3E5E401EA
void SDFBlockVariable::setFieldValue(word index, word value)
{
    Field* f = getFields(index);
    if(f != 0)
        f->value = (value & pattern[f->dimension]);
}


//##ModelId=3DA3E5E7015E
void SDFBlockVariable::setFieldValue(word block, word index, word value)
{
    Field* f = getFields(block, index);
    if(f != 0)
        f->value = (value & pattern[f->dimension]);
}


//##ModelId=3DA3E5EB00BE
bool SDFBlockVariable::setOutputStream(ByteStream* os, word first)
{
    word mnb = getNumberOfRealDataBlock();
    word start = first;
    delete outputstream;
    outputstream = new ByteStream((os->stream + first), getDimension(), os->isBigendian());
    for(word i = 0; i<mnb; i++)
    {
        blocks[i].setOutputStream(os, start);
        start += blocks[i].getDimension();
    }
    return true;
}


//##ModelId=3DA3E5EE017C
ByteStream* SDFBlockVariable::generateStream(bool bigendian)
{
    word mnb = getNumberOfRealDataBlock();
    for(word i = 0; i<mnb; i++)
    {
        blocks[i].generateStream(bigendian);
    }
    return outputstream;
}

SDFBVBlock* SDFBlockVariable::getBlock(word block) {
	if(block < maxNumberOfBlock[0])
		return &blocks[block];
	return 0;
}
