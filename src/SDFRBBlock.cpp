#include "SDFRBBlock.h"
#include "ConfigurationFile.h"
#include "PacketExceptionFileFormat.h"

using namespace PacketLib;

static SDFRBBlockType** blockTypeList = 0;

long SDFRBBlock::counter = 0;

SDFRBBlockType::SDFRBBlockType() {
// 	cout << "SDFRBBlockType::SDFRBBlockType " << sizeof(SDFRBBlockType) << endl;
}

bool SDFRBBlockType::loadType(InputText& fp) throw(PacketException*) {

	char* popName = fp.getInputTextName();
	try
        {
           
			
            int dimline = strlen(popName);
            name = (char*) new char[dimline+1];
            strcpy(name, popName);
            
            //cout << type->name << endl;

			fp.setpos(0);
            char* line=fp.getLine("[RBlock Configuration]");
            if(strlen(line) != 0)
            {
                //fixed part
                line = fp.getLine();
                if(strcmp(line, "yes") == 0)
                {
                    fixedPresent = true;
                }
                else
                {
                    if(strcmp(line, "no") == 0)
                        fixedPresent = false;
                    else
                        throw new PacketExceptionFileFormat("Rblock file format error. Fixed part section - expected yes or no keywords.");
                }

                //variable part
                line = fp.getLine();
                if(strcmp(line, "yes") == 0)
                {
                    variablePresent = true;
                }
                else
                {
                    if(strcmp(line, "no") == 0)
                        variablePresent = false;
                    else
                        throw new PacketExceptionFileFormat("Rblock file format error. Variable part section - expected yes or no keywords.");
                }

                if(variablePresent)
                {
                    //numero di rblocchi presenti
                    line = fp.getLine();
                    dword nev = atoi(line);
                    
                    if(nev > 65535)
                            throw new PacketExceptionFileFormat("Too many number of Rblocks in the packet type.");
                    numberOfRBlocks = nev;
                    //si alloca la memoria per gestire gli rblock previsti
                    rblockFilename = new char* [nev];
                    rBlockVariable = new bool[nev];
                    maxNumberOfBlock = new word[nev];
                    indexOfNBlock = new word[nev];
                    subFromNBlock = new word[nev];
                    numberOfBlockFixed = new bool[nev];
                    headerLevelOfNBlockIndex = new word[nev];
                    operatorType = new byte[nev];
                    
                }
                else
                {
                    numberOfRBlocks = 0;
                    rblockFilename = 0;
                    rBlockVariable = 0;
                    maxNumberOfBlock = 0;
                    indexOfNBlock = 0;
                    subFromNBlock = 0;
                    numberOfBlockFixed = 0;
                    headerLevelOfNBlockIndex = 0;
                    operatorType = 0;
                    
                }

                if(variablePresent)
                {
                    //find the [SourceDataFieldBlock] section
                    for(int i=0; i< numberOfRBlocks; i++)
                    {
                        char* linefind = Utility::integerToString3((char*)"[RBlock%d]", i+1);
                        fp.setpos(0);
                        line=fp.getLine(linefind);
                        /*if(i == 0)
                            line = fp.getLastLineRead();
                        else
                            line = fp.getLine();*/
                        if(strcmp(line, linefind) == 0)
                        {
                            if(i != 0)
                            {
                                line = 0;
                            }
                            //delete[] linefind;
                            linefind = 0;

                            //type of number of block
                            line = fp.getLine();
                            if(strcmp(line, "variable") == 0)
                            {
                                rBlockVariable[i] = true;
                            }
                            else
                            {
                                if(strcmp(line, "fixed") == 0)
                                {
                                    rBlockVariable[i] = false;
                                }
                                else
                                    throw new PacketExceptionFileFormat("It's impossibile to identify the type of rblock. Expected fixed or variable keywords.");
                            }

                            //number of blocks
                            line = fp.getLine();
                            dword nev = atoi(line);
                            if(nev > 65535)
                                throw new PacketExceptionFileFormat("Too many number of blocks in the packet type.");
                            maxNumberOfBlock[i] = (word) nev;

                            

                            //header level for the index of field
                            line = fp.getLine();
                            headerLevelOfNBlockIndex[i] = atoi(line);

                            //index of field
                            line = fp.getLine();
                            indexOfNBlock[i] = atoi(line);

                            //sum value
                            line = fp.getLine();
                            switch(line[0])
                            {
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

                            //file name of the rblock 
                            rblockFilename[i] = fp.getLine();
//                             cout << "S " << rblockFilename[i] << endl;
                        }
                        else
                            throw new PacketExceptionFileFormat("No [RBlockX] section found.");
                    }
                }
                nblockmax = 0;
                if(variablePresent)
                {
                    for(int i=0; i < numberOfRBlocks; i++)
                        nblockmax += maxNumberOfBlock[i];
                           
                }
            }
            else
                throw new PacketExceptionFileFormat("[RBlock Configuration] section not found");
                
        }
        catch(PacketException* e)
        {
            e->add(": ");
            e->add(popName);
            throw e;
        }
        
        return true;
}

SDFRBBlock::SDFRBBlock()
{
    tempBlock = new ByteStream();
    counter++;
    //cout << counter << " " << sizeof(SDFRBBlock) << endl;

    //create BlockType list
    if(blockTypeList == 0)
    {
        dword nb = CONFIG_MAXNUMBER_OFCONFIGILES;
        blockTypeList = (SDFRBBlockType**) new SDFRBBlockType* [nb];
        for(dword i = 0; i<nb; i++)
            blockTypeList[i] = 0;
    }

}


bool SDFRBBlock::loadFields(InputText& fp) throw (PacketException*)
{
// 	cout << "0------" << endl;
    char* line;
    popName = fp.getInputTextName();
    dword indexlist = 0;

    indexlist = 0;
    type = 0;
    while(blockTypeList[indexlist] != 0)
    {
        if(strcmp(blockTypeList[indexlist]->name, popName) == 0)
        {
            type = blockTypeList[indexlist];
            break;
        }
        else
            indexlist++;
    }

	this->previous = previous;
// 	cout << "T" << type << endl;
    if(type == 0)
    {
//     	cout << "create the type " << popName << endl;
		type = new SDFRBBlockType;
		blockTypeList[indexlist] = type;
		type->loadType(fp);
        
    } 
    
// 	cout << "NZ " << type->name << endl;
	if(type->variablePresent)
	{
		numberOfRealDataBlock = new word[type->numberOfRBlocks];
	} else 
	{
		numberOfRealDataBlock = 0;
	}
	//si carica la fixed part (se presente)
	if(type->fixedPresent)
	{
		fp.setpos(0);
		line=fp.getLine("[Fixed Part]");
		if(strcmp(line, "[Fixed Part]") == 0)
		{
			fixed.loadFields(fp);
		}
		else
			throw new PacketExceptionFileFormat("[Fixed Part] section not found");
	}
	if(type->variablePresent)
	{
		for(int i=0; i< type->numberOfRBlocks; i++)
			if(type->rBlockVariable[i] == false)
				numberOfRealDataBlock[i] = type->maxNumberOfBlock[i];
	}
	
	if(type->variablePresent) {
// 		cout << "CP --- " << type->name << endl;	
		block = (SDFRBBlock*) new SDFRBBlock[type->nblockmax];

		int indexRBlock = 0;
		dword sumBlock = type->maxNumberOfBlock[indexRBlock];
		word id = 0;
		for(dword nblock=0; nblock < type->nblockmax; nblock++)
		{
// 			cout << "nblock: " << nblock << endl;
			if(nblock >= sumBlock)
			{
				indexRBlock++;
				id = 0;
				sumBlock += type->maxNumberOfBlock[indexRBlock];
			}
			ConfigurationFile* file = new ConfigurationFile;
			char** argv = new char* [1];
// 			cout << "indexRBlock " << indexRBlock << endl;
			argv[0] = type->rblockFilename[indexRBlock];
			if(file->open(argv))
			{
				block[nblock].setPreviousPop(&fixed);
				block[nblock].setRBlockType(indexRBlock);
				block[nblock].setID(id);
// 				cout << "now load " << argv[0] << endl;
				block[nblock].loadFields(*file);
				id++;
				file->close();
			}
			else
				throw new PacketExceptionFileFormat("rblock file name not found.");
		}
	}
//     cout << "1------" << endl;        
    return true;
}

//OK
dword SDFRBBlock::getMaxDimension()
{
    dword dim = fixed.getDimension(); //for fixed part
    //variable part

    for(dword i=0; i < type->nblockmax; i++)
    {
        dim += block[i].getMaxDimension();
    }
    return dim;
}

dword SDFRBBlock::getDimension()
{
    dword dim = fixed.getDimension(); //for fixed part
    word bi = 0;
    word rbi = 0;
    for(int i=0; i < type->nblockmax; i++)
    {
        bi = block[i].getID();
        rbi = block[i].getRBlockType();
        word nrdb = getNumberOfRealDataBlock(rbi);
        if(bi < nrdb)
            dim += block[i].getDimension();
        else
            i += type->maxNumberOfBlock[rbi] - getNumberOfRealDataBlock(rbi) - 1;
    }
    return dim;
}

SDFRBBlock* SDFRBBlock::getBlock(word nblock, word rBlockIndex)
{
    word bi = 0;
    word rbi = 0;
    for(int i=0; i< type->nblockmax; i++)
    {
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
    if(!type->variablePresent || !type->rBlockVariable[rblockIndex])
    {
        throw new PacketException("It is not possible to set setNumberOfRealDataBlock for this rBlock: variable part not present");
        return;
    }
    PartOfPacket* pop = &fixed;
    if(number > type->maxNumberOfBlock[rblockIndex])
        throw new PacketException("It is not possible to set setNumberOfRealDataBlock: too much blocks");
    numberOfRealDataBlock[rblockIndex] = number;
    for(int i=0; i< type->headerLevelOfNBlockIndex[rblockIndex]; i++)
        pop = pop->previous;
    if(type->operatorType[rblockIndex] == 1)
    {
        number *= 2;	//NON FUNZIONA BENE, DA CONTROLLARE
    }
    if(type->operatorType[rblockIndex] == 2)
    {
        number /= 2;
    }
    pop->setFieldValue(type->indexOfNBlock[rblockIndex], number - type->subFromNBlock[rblockIndex]);
    numberOfRealDataBlock[rblockIndex] = number;
    reset_output_stream = true;
}


word SDFRBBlock::getNumberOfRealDataBlock(word rblockIndex)
{
    if(!type->variablePresent)
        return 0;
    if(!type->rBlockVariable[rblockIndex])
        return type->maxNumberOfBlock[rblockIndex];
    PartOfPacket* pop = &fixed;
    for(int i=0; i< type->headerLevelOfNBlockIndex[rblockIndex]; i++)
        pop = pop->previous;
    if(type->operatorType[rblockIndex] == 0)
        numberOfRealDataBlock[rblockIndex] = pop->getFieldValue(type->indexOfNBlock[rblockIndex]) + type->subFromNBlock[rblockIndex];
    if(type->operatorType[rblockIndex] == 1)
    {
        word nb = pop->getFieldValue(type->indexOfNBlock[rblockIndex]);
        if(nb % 2 != 0)
            nb++;
        nb = nb / 2;
        nb += type->subFromNBlock[rblockIndex];
        numberOfRealDataBlock[rblockIndex] = nb;
    }
    if(type->operatorType[rblockIndex] == 2)
    {
        word nb = pop->getFieldValue(type->indexOfNBlock[rblockIndex]);
        nb = nb * 2;
        nb += type->subFromNBlock[rblockIndex];
        numberOfRealDataBlock[rblockIndex] = nb;
    }
    return  numberOfRealDataBlock[rblockIndex];
}


word SDFRBBlock::getCurrentNumberOfBlocks()
{
    word nblock = 0;
    for(int i=0; i< type->numberOfRBlocks; i++)
        nblock = getNumberOfRealDataBlock(i);
    return nblock;
}

bool SDFRBBlock::setOutputStream(ByteStream* os, dword first)
{
    dword start = first;
    //setta l'output stream per la parte fixed (se presente)
    if(type->fixedPresent)
    {
        fixed.setOutputStream(os, start);
        delete outputstream;
        outputstream = new ByteStream((os->stream + start), getDimension(), os->isBigendian());
        start += fixed.getDimension();
    }
    if(type->variablePresent)
    {
        dword bi = 0;
        dword rbi = 0;
        for(word i=0; i < type->nblockmax; i++)
        {
            bi = block[i].getID();
            rbi = block[i].getRBlockType();
            if(bi < getNumberOfRealDataBlock(rbi))
            {
                //solo per i blocchi validi
                block[i].setOutputStream(os, start);
                start += block[i].getDimension();
            }
            else
                i += type->maxNumberOfBlock[rbi] - getNumberOfRealDataBlock(rbi) - 1;
        }
    }
    return true;
}

ByteStream* SDFRBBlock::generateStream(bool bigendian)
{
    if(type->fixedPresent)
        fixed.generateStream(bigendian);

    if(type->variablePresent)
    {
        word bi = 0;
        word rbi = 0;
        for(int i=0; i < type->nblockmax; i++)
        {
            bi = block[i].getID();
            rbi = block[i].getRBlockType();
            if(bi < getNumberOfRealDataBlock(rbi))
            {
                //solo per i blocchi validi
                block[i].generateStream(bigendian);
            }
            else
                i += type->maxNumberOfBlock[rbi] - getNumberOfRealDataBlock(rbi) - 1;
        }
    }

    return outputstream;
}

bool SDFRBBlock::setByteStream(ByteStream* s)
{
    dword bytestart=0;
    dword bytestop=0;
    stream = s;
    //ByteStream* s = new ByteStream(k->stream, k->getDimension(), k->isBigendian());
    //setta l'output stream per la parte fixed (se presente)
    if(type->fixedPresent)
    {
        bytestop += fixed.getDimension() - 1;
        if(tempBlock->setStream(s, bytestart, bytestop))
            if(!fixed.setByteStream(tempBlock))
                return false;
        bytestart = bytestop + 1;
    }
    if(type->variablePresent)
    {
        word bi = 0;
        word rbi = 0;
        for(int i=0; i < type->nblockmax; i++)
        {
            bi = block[i].getID();
            rbi = block[i].getRBlockType();
            word nrdb = getNumberOfRealDataBlock(rbi);
            if(bi < nrdb)
            {
                //solo per i blocchi validi
                //1) per prima cosa occorre settare la parte fissa del block[i]
                //prima di richiamare block[i].getDimension(), altrimenti ci sono
                //solo valori casuali
                tempBlock->setStream(s, bytestart, s->getDimension() - 1);
                block[i].setByteStream(tempBlock);
                //2) ora si puo' procedere con il calcolo corretto della dimensione
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
                i += type->maxNumberOfBlock[rbi] - getNumberOfRealDataBlock(rbi) - 1;
        }
    }
    return true;
}


char** SDFRBBlock::printValue(char* addString)
{
    char** cc;
    char** ct;
    word index=0;
    word ntf = getTotalNumberOfFields();
    cc = new char* [ntf+1];

    if(type->fixedPresent)
    {
        ct = (char**) fixed.printValue(addString);
        for(int ii=0; ct[ii] != 0; ii++)
        {
            cc[index] = ct[ii];
            index++;
        }
    }

    if(type->variablePresent)
    {
        word bi = 0;
        word rbi = 0;
        for(int i=0; i < type->nblockmax; i++)
        {
            bi = block[i].getID();
            rbi = block[i].getRBlockType();
            if(bi < getNumberOfRealDataBlock(rbi))
            {
                //solo per i blocchi validi
                ct = block[i].printValue(addString);
                for(int ii=0; ct[ii] != 0; ii++)
                {
                    cc[index] = ct[ii];
                    index++;
                }
            }
            else
                i += type->maxNumberOfBlock[rbi] - getNumberOfRealDataBlock(rbi) - 1;
        }
    }
    cc[index] = '\0';
    return cc;
}

void SDFRBBlock::printValueStdout()
{

    if(type->fixedPresent)
    {
        fixed.printValueStdout();
    }

    if(type->variablePresent)
    {
        word bi = 0;
        word rbi = 0;
        for(int i=0; i < type->nblockmax; i++)
        {
            bi = block[i].getID();
            rbi = block[i].getRBlockType();
            if(bi < getNumberOfRealDataBlock(rbi))
            {
                //solo per i blocchi validi
                block[i].printValueStdout();
            }
            else
                i += type->maxNumberOfBlock[rbi] - getNumberOfRealDataBlock(rbi) - 1;
        }
    }
}


string* SDFRBBlock::printStructure()
{
    return new string("string* SDFRBBlock::printStructure() - TODO");
}


word SDFRBBlock::getTotalNumberOfFields()
{
    word dim = fixed.getNumberOfFields(); //for fixed part
    word bi = 0;
    word rbi = 0;
    int j;
    for(j=0; j < type->nblockmax; j++)
    {
        bi = block[j].getID();
        rbi = block[j].getRBlockType();
        if(bi < getNumberOfRealDataBlock(rbi))
            dim += block[j].getNumberOfFields();
        else
            j += type->maxNumberOfBlock[rbi] - getNumberOfRealDataBlock(rbi) - 1;
    }
    return dim;
}


