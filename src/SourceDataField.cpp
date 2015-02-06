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

void SourceDataField::loadFields(pugi::xml_node node, const pugi::xml_document& doc, std::map<pugi::xml_node, int>& physicalIndex)
{
        numberOfRBlocks = 1;
        rblockFilename = new char*[numberOfRBlocks];
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
        block[0].loadFields(node, doc, physicalIndex);
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
    dword dim = size();
    ByteStream b(stream->stream, dim, true);
    char* c = b.printStreamInHexadecimal();
    return c;
}

SDFBlock* SourceDataField::getBlock(word nblock,word rBlockIndex)
{
    return block[0].getBlock(nblock, rBlockIndex);
}


dword SourceDataField::sizeMax()
{
    return block[0].sizeMax();
}

dword SourceDataField::size()
{
    return block[0].size();
}

dword SourceDataField::sizeFixedPart()
{
    return block[0].fixed.size();
}

void SourceDataField::setNumberOfBlocks(word number, word rblockIndex)  throw (PacketException*)
{
    /// The block[0] is the only block present
    block[0].setNumberOfBlocks(number, rblockIndex);
    reset_output_stream = true;
}


word SourceDataField::getNumberOfBlocks(word rblockIndex)
{
    /// The block[0] is the only block present
    return  block[0].getNumberOfBlocks(rblockIndex);
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

word SourceDataField::getFieldIndex(string fieldname) {
	return block[0].getFieldIndex(fieldname);
}

void SourceDataField::setFieldValue(word index, word value)
{
    block[0].setFieldValue(index, value);
}


void SourceDataField::setFieldValue_16i(word index, signed short value)
{
    block[0].setFieldValue_16i(index, value);
}

void SourceDataField::setFieldValue_16ui(word index, word value)
{
    block[0].setFieldValue_16ui(index, value);
}


void SourceDataField::setFieldValue_32i(word index, signed long value)
{
    block[0].setFieldValue_32i(index, value);
}

void SourceDataField::setFieldValue_32ui(word index, unsigned long value)
{
    block[0].setFieldValue_32ui(index, value);
}

void SourceDataField::setFieldValue_32f(word index, float value)
{
    block[0].setFieldValue_32f(index, value);
}

void SourceDataField::setFieldValue_64f(word index, double value)
{
    block[0].setFieldValue_64f(index, value);
}

word SourceDataField::getNumberOfFields()
{
    return block[0].getNumberOfFields();
}

char** SourceDataField::printValue(const char* addString)
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

signed short SourceDataField::getFieldValue_16i(word index){
	return block[0].getFieldValue_16i(index);
}

word SourceDataField::getFieldValue_16ui(word index){
	return block[0].getFieldValue_16ui(index);
}

signed long SourceDataField::getFieldValue_32i(word index){
	return block[0].getFieldValue_32i(index);
}


unsigned long SourceDataField::getFieldValue_32ui(word index) {
	return block[0].getFieldValue_32ui(index);
}

float SourceDataField::getFieldValue_32f(word index) {
	return block[0].getFieldValue_32f(index);
}

double SourceDataField::getFieldValue_64f(word index) {
	return block[0].getFieldValue_64f(index);
}

word SourceDataField::getFieldValue(string fieldname) {
		return block[0].getFieldValue(fieldname);
	
}


signed short SourceDataField::getFieldValue_16i(string fieldname) {
		return block[0].getFieldValue_16i(fieldname);
	
}



word SourceDataField::getFieldValue_16ui(string fieldname) {
		return block[0].getFieldValue_16ui(fieldname);
	
}



signed long SourceDataField::getFieldValue_32i(string fieldname){
		return block[0].getFieldValue_32i(fieldname);
	
}



unsigned long SourceDataField::getFieldValue_32ui(string fieldname){
		return block[0].getFieldValue_32ui(fieldname);
	
}



float SourceDataField::getFieldValue_32f(string fieldname){
		return block[0].getFieldValue_32f(fieldname);
	
}



double SourceDataField::getFieldValue_64f(string fieldname){
		return block[0].getFieldValue_64f(fieldname);
	
}



void SourceDataField::setFieldValue(string fieldname, word value){
		block[0].setFieldValue(fieldname, value);
	
}



void SourceDataField::setFieldValue_16i(string fieldname, signed short value){
		block[0].setFieldValue_16i(fieldname, value);
	
}



void SourceDataField::setFieldValue_16ui(string fieldname, word value){
		block[0].setFieldValue_16ui(fieldname, value);
	
}



void SourceDataField::setFieldValue_32i(string fieldname, signed long value){
		block[0].setFieldValue_32i(fieldname, value);
	
}



void SourceDataField::setFieldValue_32ui(string fieldname, unsigned long value){
	block[0].setFieldValue_32ui(fieldname, value);
	
}



void SourceDataField::setFieldValue_32f(string fieldname, float value){
		block[0].setFieldValue_32f(fieldname, value);
	
}



void SourceDataField::setFieldValue_64f(string fieldname, double value){
		block[0].setFieldValue_64f(fieldname, value);
	
}



