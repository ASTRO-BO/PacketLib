#include "SDFRBBlock.h"
#include "ConfigurationFile.h"
#include "PacketExceptionFileFormat.h"

using namespace PacketLib;

SDFRBBlock::SDFRBBlock() {
  fixedPresent = false;
  variablePresent = false;
  tempBlock = new ByteStream();
}


bool SDFRBBlock::loadFields(InputText& fp) throw (PacketException*) {
  char* line;
  popName = fp.getInputTextName();
  this->previous = previous;
  try {    
      line=fp.getLine("[RBlock Configuration]");
      if(strlen(line) != 0) {
        //fixed part
        line = fp.getLine();
        if(strcmp(line, "yes") == 0) {
          fixedPresent = true;
        } else {
          if(strcmp(line, "no") == 0)
            fixedPresent = false;
          else
            throw new PacketExceptionFileFormat("Rblock file format error. Fixed part section - expected yes or no keywords.");
        }
        delete[] line;

        //variable part
        line = fp.getLine();
        if(strcmp(line, "yes") == 0) {
          variablePresent = true;
        } else {
          if(strcmp(line, "no") == 0)
            variablePresent = false;
          else
            throw new PacketExceptionFileFormat("Rblock file format error. Variable part section - expected yes or no keywords.");
        }
        delete[] line;

        if(variablePresent) {
          //numero di rblocchi presenti
          line = fp.getLine();
          numberOfRBlocks = atoi(line);
          delete line;
        }
        else
          numberOfRBlocks = 0;        

        //si alloca la memoria per gestire gli rblock previsti
        rblockFilename = new char* [numberOfRBlocks];
        rBlockVariable = new bool[numberOfRBlocks];
        maxNumberOfBlock = new word[numberOfRBlocks];
        indexOfNBlock = new word[numberOfRBlocks];
        subFromNBlock = new word[numberOfRBlocks];
        numberOfBlockFixed = new bool[numberOfRBlocks];
        numberOfRealDataBlock = new word[numberOfRBlocks];
        headerLevelOfNBlockIndex = new word[numberOfRBlocks];       
		operatorType = new byte[numberOfRBlocks]; 
	
        //si carica la fixed part (se presente)
        line=fp.getLine();
        
        if(fixedPresent) {
          if(strcmp(line, "[Fixed Part]") == 0) {
            fixed.loadFields(fp);
            delete[] line;            
          } else
              throw new PacketExceptionFileFormat("[Fixed Part] section not found");
        }


        if(variablePresent) {
          //find the [SourceDataFieldBlock] section
          for(int i=0; i< numberOfRBlocks; i++) {
            char* linefind = Utility::integerToString3((char*)"[RBlock%d]", i+1);
            if(i == 0)
              line = fp.getLastLineRead();
            else
              line = fp.getLine();
            if(strcmp(line, linefind) == 0) {
              if(i != 0) { delete[] line; line = 0; }
              delete[] linefind; linefind = 0;

              //type of number of block
              line = fp.getLine();
              if(strcmp(line, "variable") == 0) {
                rBlockVariable[i] = true;
              } else {
                if(strcmp(line, "fixed") == 0) {
                  rBlockVariable[i] = false;
                } else
                  throw new PacketExceptionFileFormat("It's impossibile to identify the type of rblock. Expected fixed or variable keywords.");
              }
              delete line;

              //number of blocks
              line = fp.getLine();
              maxNumberOfBlock[i] = atoi(line);
              delete line;

              if(rBlockVariable[i] == false)
                numberOfRealDataBlock[i] = maxNumberOfBlock[i];

              //header level for the index of field
              line = fp.getLine();
              headerLevelOfNBlockIndex[i] = atoi(line);
              delete line;
              
              //index of field
              line = fp.getLine();
              indexOfNBlock[i] = atoi(line);
              delete line;

              //sum value
              line = fp.getLine();
	      switch(line[0]) {
	      case '/':
	      		operatorType[i] = 1;
              		subFromNBlock[i] = atoi(line+1);
			break;
	      case '*':
	      		operatorType[i] = 2;
              		subFromNBlock[i] = atoi(line+1);
			break;
	      default:	      
	      		operatorType[i] = 0;
	      		subFromNBlock[i] = atoi(line);
	      }
              delete line;

              //file name of the rblock
              rblockFilename[i] = fp.getLine();
            } else
                throw new PacketExceptionFileFormat("No [RBlockX] section found.");
          }
        }
        nblockmax = 0;
        if(variablePresent) {  
          for(int i=0; i < numberOfRBlocks; i++)
            nblockmax += maxNumberOfBlock[i];

          block = (SDFRBBlock*) new SDFRBBlock[nblockmax];

          int indexRBlock = 0;
          int sumBlock = maxNumberOfBlock[indexRBlock];
          word id = 0;
          for(word nblock=0; nblock < nblockmax; nblock++) {
            if(nblock >= sumBlock) {
              indexRBlock++;
              id = 0;
              sumBlock += maxNumberOfBlock[indexRBlock];
            }
            ConfigurationFile file;
            char** argv = new char* [1];
            argv[0] = rblockFilename[indexRBlock];
            if(file.open(argv)) {
              block[nblock].setPreviousPop(&fixed);
              block[nblock].setRBlockType(indexRBlock);
              block[nblock].setID(id);
              block[nblock].loadFields(file);
              id++;
              file.close();
            }
            else
              throw new PacketExceptionFileFormat("rblock file name not found.");          
          }
        }
      }
      else
        throw new PacketExceptionFileFormat("[RBlock Configuration] section not found");

    return true;
  } catch(PacketException* e) {
        e->add(": ");
        e->add(popName);
        throw e;
  }  
}

//OK
word SDFRBBlock::getMaxDimension() {
  word dim = fixed.getDimension(); //for fixed part
  //variable part
  for(int i=0; i < nblockmax; i++) {
    dim += block[i].getMaxDimension();
  }
  return dim;
}

word SDFRBBlock::getDimension() {
  word dim = fixed.getDimension(); //for fixed part
  word bi = 0;
  word rbi = 0;
  for(int i=0; i < nblockmax; i++) {
    bi = block[i].getID();
    rbi = block[i].getRBlockType();
    word nrdb = getNumberOfRealDataBlock(rbi);
    if(bi < nrdb)
      dim += block[i].getDimension();
    else  
      i += maxNumberOfBlock[rbi] - getNumberOfRealDataBlock(rbi) - 1;
  }
  return dim;
}

SDFRBBlock* SDFRBBlock::getBlock(word nblock, word rBlockIndex) {
  word bi = 0; word rbi = 0;
  for(int i=0; i< nblockmax; i++) {
    bi = block[i].getID();
    rbi = block[i].getRBlockType();
    if(rbi == rBlockIndex && bi == nblock)
      return &block[i];
  }
  return 0;    
}


void SDFRBBlock::setNumberOfRealDataBlock(word number, word rblockIndex) throw (PacketException*)
{ 
  //Nel caso in cui la parte variabile non sia presente oppure rBlockVariable = false,
  //non e' presente un field in cui salvare il valore. La dimensione e' fissata
  if(!variablePresent || !rBlockVariable[rblockIndex]) {
  	throw new PacketException("It is not possible to set setNumberOfRealDataBlock for this rBlock: variable part not present");
    return;
  }
  PartOfPacket* pop = &fixed;
  if(number > maxNumberOfBlock[rblockIndex])
  		throw new PacketException("It is not possible to set setNumberOfRealDataBlock: too much blocks");
  numberOfRealDataBlock[rblockIndex] = number;
  for(int i=0; i< headerLevelOfNBlockIndex[rblockIndex]; i++)
    pop = pop->previous;
  if(operatorType[rblockIndex] == 1) {
  	number *= 2;	//NON FUNZIONA BENE, DA CONTROLLARE
  }
  if(operatorType[rblockIndex] == 2) {
  	number /= 2;	
  }
  pop->setFieldValue(indexOfNBlock[rblockIndex], number - subFromNBlock[rblockIndex]);
  numberOfRealDataBlock[rblockIndex] = number;
  reset_output_stream = true;
}


word SDFRBBlock::getNumberOfRealDataBlock(word rblockIndex)
{
  if(!variablePresent)
    return 0;
  if(!rBlockVariable[rblockIndex])
    return maxNumberOfBlock[rblockIndex];
  PartOfPacket* pop = &fixed;
  for(int i=0; i< headerLevelOfNBlockIndex[rblockIndex]; i++)
    pop = pop->previous;
  if(operatorType[rblockIndex] == 0)
  	numberOfRealDataBlock[rblockIndex] = pop->getFieldValue(indexOfNBlock[rblockIndex]) + subFromNBlock[rblockIndex];
  if(operatorType[rblockIndex] == 1) {
  	word nb = pop->getFieldValue(indexOfNBlock[rblockIndex]);
	if(nb % 2 != 0)
		nb++;
	nb = nb / 2;
	nb += subFromNBlock[rblockIndex];
	numberOfRealDataBlock[rblockIndex] = nb;	
  }
  if(operatorType[rblockIndex] == 2) {
  	word nb = pop->getFieldValue(indexOfNBlock[rblockIndex]);
	nb = nb * 2;
	nb += subFromNBlock[rblockIndex];
	numberOfRealDataBlock[rblockIndex] = nb;	
  }
  return  numberOfRealDataBlock[rblockIndex];
}


word SDFRBBlock::getCurrentNumberOfBlocks() {
  word nblock = 0;
  for(int i=0; i< numberOfRBlocks; i++)
    nblock = getNumberOfRealDataBlock(i);
  return nblock;
}

bool SDFRBBlock::setOutputStream(ByteStream* os, word first)
{
  word start = first;
  //setta l'output stream per la parte fixed (se presente)
  if(fixedPresent) {
    fixed.setOutputStream(os, start);
    delete outputstream;
    outputstream = new ByteStream((os->stream + start), getDimension(), os->isBigendian());
    start += fixed.getDimension();
  }
  if(variablePresent) {
    word bi = 0;
    word rbi = 0;
    for(int i=0; i < nblockmax; i++) {
      bi = block[i].getID();
      rbi = block[i].getRBlockType();
      if(bi < getNumberOfRealDataBlock(rbi)) {
        //solo per i blocchi validi
        block[i].setOutputStream(os, start);
        start += block[i].getDimension();
      }
      else
        i += maxNumberOfBlock[rbi] - getNumberOfRealDataBlock(rbi) - 1;
    }
  }
  return true;
}

//##ModelId=3DA3E5EE017C
ByteStream* SDFRBBlock::generateStream(bool bigendian)
{
    if(fixedPresent)
      fixed.generateStream(bigendian);

    if(variablePresent) {
      word bi = 0;
      word rbi = 0;
      for(int i=0; i < nblockmax; i++) {
        bi = block[i].getID();
        rbi = block[i].getRBlockType();
        if(bi < getNumberOfRealDataBlock(rbi)) {
          //solo per i blocchi validi
          block[i].generateStream(bigendian);
        }
        else
          i += maxNumberOfBlock[rbi] - getNumberOfRealDataBlock(rbi) - 1;
      }
    }
      
    return outputstream;
}

bool SDFRBBlock::setByteStream(ByteStream* s) {
word bytestart=0;
word bytestop=0;
    stream = s;
    //ByteStream* s = new ByteStream(k->stream, k->getDimension(), k->isBigendian());
    //setta l'output stream per la parte fixed (se presente)
    if(fixedPresent) {
        bytestop += fixed.getDimension() - 1;
        if(tempBlock->setStream(s, bytestart, bytestop))
            if(!fixed.setByteStream(tempBlock))
                return false;
        bytestart = bytestop + 1;
    }
    if(variablePresent) {
        word bi = 0;
        word rbi = 0;
        for(int i=0; i < nblockmax; i++) {
            bi = block[i].getID();
            rbi = block[i].getRBlockType();
            word nrdb = getNumberOfRealDataBlock(rbi);
            if(bi < nrdb) {
                //solo per i blocchi validi                
                //1) per prima cosa occorre settare la parte fissa del block[i]
                //prima di richiamare block[i].getDimension(), altrimenti ci sono
                //solo valori casuali
                tempBlock->setStream(s, bytestart, s->getDimension() - 1);
                block[i].setByteStream(tempBlock);              
                //2) ora si pu�procedere con il calcolo corretto della dimensione
                if(bytestop != 0)
                    bytestop += block[i].getDimension();
                else
                    bytestop += block[i].getDimension() - 1;                
                if(tempBlock->setStream(s, bytestart, bytestop))
                    if(!block[i].setByteStream(tempBlock))
                        return false;
                bytestart = bytestop + 1;
            }
            else
                i += maxNumberOfBlock[rbi] - getNumberOfRealDataBlock(rbi) - 1;
        }
    }
    return true;   
}



//##ModelId=3A54BDE40351
char** SDFRBBlock::printValue(char* addString)
{
    char** cc;
    char** ct;
    word index=0;
    word ntf = getTotalNumberOfFields();
    cc = new char* [ntf+1];
  
    if(fixedPresent) {
      ct = (char**) fixed.printValue(addString);
      for(int ii=0; ct[ii] != 0; ii++)
      {
            cc[index] = ct[ii];
            index++;
      }
    }
  
    if(variablePresent) {
      word bi = 0;
      word rbi = 0;
      for(int i=0; i < nblockmax; i++) {
        bi = block[i].getID();
        rbi = block[i].getRBlockType();
        if(bi < getNumberOfRealDataBlock(rbi)) {
            //solo per i blocchi validi
            ct = block[i].printValue(addString);
            for(int ii=0; ct[ii] != 0; ii++)
            {
                cc[index] = ct[ii];
                index++;
            }
        }
        else
          i += maxNumberOfBlock[rbi] - getNumberOfRealDataBlock(rbi) - 1;
      }
    }
    cc[index] = '\0';
    return cc;
}



//##ModelId=3C35F9580094
string* SDFRBBlock::printStructure()
{
    return new string("string* SDFRBBlock::printStructure() - TODO");
}


word SDFRBBlock::getTotalNumberOfFields() {
  word dim = fixed.getNumberOfFields(); //for fixed part
  word bi = 0; word rbi = 0; int j;
  for(j=0; j < nblockmax; j++) {
    bi = block[j].getID(); rbi = block[j].getRBlockType();
    if(bi < getNumberOfRealDataBlock(rbi))
      dim += block[j].getNumberOfFields();
    else
      j += maxNumberOfBlock[rbi] - getNumberOfRealDataBlock(rbi) - 1;
  }
  return dim;
}


