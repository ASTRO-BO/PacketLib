#include "SDFRBlock.h"

using namespace PacketLib;

SDFRBlock::SDFRBlock(PartOfPacket* pop) : SourceDataField("SDF Recoursive Block") {
    isblock = false;
    fixed = false;
    rblock = true;
    block = NULL;
    previous = pop;   
}

SDFRBlock::~SDFRBlock() {

  //delete[] block;
  
}

bool SDFRBlock::loadFields(InputText& fp) throw(PacketException*) {
  try {
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
    line = fp.getLine(); //get the [Identifiers] section
    return true;
  } catch(PacketExceptionIO* e) {
        e->add(" - ");
        e->add("Configuration file: ");
        throw e;
  }  
}

SDFRBBlock* SDFRBlock::getBlock(word nblock,word rBlockIndex) {
  return block[0].getBlock(nblock, rBlockIndex);  
}

word SDFRBlock::getMaxDimension() {
  return block[0].getMaxDimension();
}

word SDFRBlock::getDimension() {
  return block[0].getDimension();
}

void SDFRBlock::setNumberOfRealDataBlock(word number, word rblockIndex)
{
    //il block[0] e' l'unico block presente
    block[0].setNumberOfRealDataBlock(number, rblockIndex);
    reset_output_stream = true;
}


word SDFRBlock::getNumberOfRealDataBlock(word rblockIndex)
{
    //il block[0] e' l'unico block presente
    return  block[0].getNumberOfRealDataBlock(rblockIndex);
}


bool SDFRBlock::setOutputStream(ByteStream* os, word first)
{
    return block[0].setOutputStream(os, first);
}

ByteStream* SDFRBlock::generateStream(bool bigendian)
{
    return block[0].generateStream(bigendian);      
}

bool SDFRBlock::setByteStream(ByteStream* s) {
    stream = s;
    return block[0].setByteStream(s);
}

Field* SDFRBlock::getFields(word index) {
  return block[0].getFields(index);
}

word SDFRBlock::getFieldValue(word index) {
  return block[0].getFieldValue(index);
}

void SDFRBlock::setFieldValue(word index, word value) {
  return block[0].setFieldValue(index, value);
}

word SDFRBlock::getNumberOfFields() {
  return block[0].getNumberOfFields();
}

char** SDFRBlock::printValue(char* addString) {
    return block[0].printValue(addString);
}

string* SDFRBlock::printStructure() {
    return block[0].printStructure();
}
  

