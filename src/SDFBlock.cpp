/***************************************************************************
                          SDFBlock.cpp  -  description
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

#include <sstream>
#include "SDFBlock.h"
#include "ConfigurationFile.h"
#include "PacketExceptionFileFormat.h"

using namespace PacketLib;

static SDFBlockType** blockTypeList = 0;

long SDFBlock::counter = 0;

SDFBlockType::SDFBlockType()
{
// 	cout << "SDFBlockType::SDFBlockType " << sizeof(SDFBlockType) << endl;
}

void SDFBlockType::loadType(pugi::xml_node node, const pugi::xml_document& doc,
                            std::map<pugi::xml_node, int>& physicalIndex)
{
	nblockmax = 0;

	std::string tmp;
	if(strcmp(node.name(),"sourcedatafield") == 0)
	{
		tmp = std::string(node.parent().attribute("name").value()) + "_sdf";
	}
	else
		tmp = node.attribute("name").value();

	name = (char*) new char[tmp.size()+1];
	strncpy(name, tmp.c_str(), tmp.size());
	name[tmp.size()] = 0;

	pugi::xml_node fNode = node.child("field");
	if(fNode)
		fixedPresent = true;
	else
		fixedPresent = false;

	variablePresent = false;
	pugi::xpath_node_set rbNodeSet = node.select_nodes("rblock");
	if(rbNodeSet.size() == 0) 
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

		return;
	}
	variablePresent = true;
#ifdef DEBUG
	std::cout << "fixed part: " << variablePresent;
	std::cout << " variable part: " << variablePresent << std::endl;
#endif
	numberOfRBlocks = rbNodeSet.size();
	if(numberOfRBlocks > 65535)
		throw new PacketExceptionFileFormat("Too many number of Rblocks in the packet type.");
	rblockFilename = new char*[numberOfRBlocks];
	rBlockVariable = new bool[numberOfRBlocks];
	maxNumberOfBlock = new word[numberOfRBlocks];
	indexOfNBlock = new word[numberOfRBlocks];
	subFromNBlock = new word[numberOfRBlocks];
	numberOfBlockFixed = new bool[numberOfRBlocks];
	headerLevelOfNBlockIndex = new word[numberOfRBlocks];
	operatorType = new byte[numberOfRBlocks];

	for(int i=0; i < numberOfRBlocks; i++)
	{
		const pugi::xml_node rbNode = rbNodeSet[i].node();
		pugi::xml_attribute idref = rbNode.attribute("idref");
		if(idref)
			rBlockVariable[i] = true;
		else
			rBlockVariable[i] = false;

		const char* nblocks = rbNode.attribute("maxnumberofblocks").value();
		maxNumberOfBlock[i] = atoi(nblocks);
		if(maxNumberOfBlock[i] > 65535)
			throw new PacketExceptionFileFormat("Too many number of blocks in the packet type.");

		if(!idref)
		{
			stringstream ss;
			ss << "idref attribute not defined for rblock" << rbNode.attribute("name").value();
			throw new PacketExceptionFileFormat(ss.str().c_str());
		}

		string query = string("//field[@id=\"")+idref.value()+"\"]";
		pugi::xml_node numberofblocksid = doc.select_nodes(query.c_str())[0].node();
		pugi::xml_node nodetmp = rbNode;
		unsigned int level = 0;

		while(nodetmp.parent() != numberofblocksid.parent())
		{
			// if the parent is a packet means that the id is not in the fixed part of the
			// recursive rblocks nor the sourcedatafield. So test the datafieldheader
			// and header, otherwise complain.
			if(string(nodetmp.parent().name()).compare("packet") == 0)
			{
				string idparentnodename = numberofblocksid.parent().name();
				if(idparentnodename.compare("datafieldheader") == 0)
				{
					// we have already add 1 level because nodetmp in this case is
					// the sourcedatafield node
				}
				else if(idparentnodename.compare("header") == 0)
				{
					// we add just one level for the same reason above
					level++;
				}
				else
				{
					std::stringstream ss;
					ss << "Error on id association. Id'" << idref.value() << "' doesn't exists. idref defined by rblock '" << rbNode.attribute("name").value() << "'.";
					throw new PacketExceptionFileFormat(ss.str().c_str());
				}

				break;
			}
			level++;
			nodetmp = nodetmp.parent();
		}
		headerLevelOfNBlockIndex[i] = level;
		indexOfNBlock[i] = physicalIndex[numberofblocksid];
		pugi::xml_attribute offsetAttr = numberofblocksid.attribute("numberofblocksoffset");
		const char* offset;
		if(offsetAttr)
			offset = offsetAttr.value();
		else
			offset = "0";

		switch(offset[0])
		{
			case '/':
				operatorType[i] = 1;
				subFromNBlock[i] = atoi(offset+1);
				break;
			case '*':
				operatorType[i] = 2;
				subFromNBlock[i] = atoi(offset+1);
				break;
			default:
				operatorType[i] = 0;
				subFromNBlock[i] = atoi(offset);
		}
#ifdef DEBUG
		std::cout << "Add rblock index for " << rbNode.attribute("name").value();
		std::cout << " level " << level << " phyindex " << indexOfNBlock[i] << " offset " << offset << std::endl;
#endif
		rblockFilename[i] = (char*) rbNode.attribute("name").value();

		nblockmax += maxNumberOfBlock[i];
	}
}

bool SDFBlockType::loadType(InputText& fp) throw(PacketException*)
{

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
            /// fixed part
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

            /// variable part
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
                /// numero di rblocchi presenti
                line = fp.getLine();
                dword nev = atoi(line);

                if(nev > 65535)
                    throw new PacketExceptionFileFormat("Too many number of Rblocks in the packet type.");
                numberOfRBlocks = nev;
                /// Memory allocation to handle the expected rblock
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
                /// It finds the [SourceDataFieldBlock] section
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
                        /// delete[] linefind;
                        linefind = 0;

                        /// type of number of block
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

                        /// number of blocks
                        line = fp.getLine();
                        dword nev = atoi(line);
                        if(nev > 65535)
                            throw new PacketExceptionFileFormat("Too many number of blocks in the packet type.");
                        maxNumberOfBlock[i] = (word) nev;



                        /// header level for the index of field
                        line = fp.getLine();
                        headerLevelOfNBlockIndex[i] = atoi(line);

                        /// index of field
                        line = fp.getLine();
                        indexOfNBlock[i] = atoi(line);

                        /// sum value
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

                        /// file name of the rblock
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

SDFBlock::SDFBlock() : block(0)
{
    tempBlock1 = ByteStreamPtr(new ByteStream());
    counter++;
    //cout << counter << " " << sizeof(SDFBlock) << endl;

    /// create BlockType list
    if(blockTypeList == 0)
    {
        dword nb = CONFIG_MAXNUMBER_OFCONFIGILES;
        blockTypeList = (SDFBlockType**) new SDFBlockType* [nb];
        for(dword i = 0; i<nb; i++)
            blockTypeList[i] = 0;
    }

}


SDFBlock::~SDFBlock()
{
    delete[] block;
}

void SDFBlock::loadFieldsSDFB(pugi::xml_node rbNode, const pugi::xml_document& doc,
                            std::map<pugi::xml_node, int>& physicalIndex)
{
	std::string tmp;
	if(strcmp(rbNode.name(),"sourcedatafield") == 0)
	{
		tmp = std::string(rbNode.parent().attribute("name").value()) + "_sdf";
	}
	else
		tmp = rbNode.attribute("name").value();

	popName = (char*) new char[tmp.size()+1];
	strncpy(popName, tmp.c_str(), tmp.size());
	popName[tmp.size()] = 0;

	dword indexlist = 0;
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
	if(type == 0)
	{
		type = new SDFBlockType;
		blockTypeList[indexlist] = type;
		type->loadType(rbNode, doc, physicalIndex);
	}

// 	cout << "NZ " << type->name << endl;
	if(type->variablePresent)
		numberOfRealDataBlock = new word[type->numberOfRBlocks];
	else
		numberOfRealDataBlock = 0;

	/// It loads the fixed part (if present)
	fixed.previous = previous;
	if(type->fixedPresent)
		fixed.loadFields(rbNode);

	if(type->variablePresent)
	{
		for(int i=0; i< type->numberOfRBlocks; i++)
			if(type->rBlockVariable[i] == false)
				numberOfRealDataBlock[i] = type->maxNumberOfBlock[i];

		block = (SDFBlock*) new SDFBlock[type->nblockmax];
		int indexRBlock = 0;
		dword sumBlock = type->maxNumberOfBlock[indexRBlock];
		word id = 0;
		for(dword nblock=0; nblock < type->nblockmax; nblock++)
		{
			if(nblock >= sumBlock)
			{
				indexRBlock++;
				id = 0;
				sumBlock += type->maxNumberOfBlock[indexRBlock];
			}

			block[nblock].setPreviousPop(&fixed);
			block[nblock].setRBlockType(indexRBlock);
			block[nblock].setID(id);
			pugi::xml_node childNode = rbNode.find_child_by_attribute("name", type->rblockFilename[indexRBlock]);
			block[nblock].loadFieldsSDFB(childNode, doc, physicalIndex);
			id++;
		}
	}
}

bool SDFBlock::loadFields(InputText& fp) throw (PacketException*)
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
        type = new SDFBlockType;
        blockTypeList[indexlist] = type;
        type->loadType(fp);

    }

// 	cout << "NZ " << type->name << endl;
    if(type->variablePresent)
    {
        numberOfRealDataBlock = new word[type->numberOfRBlocks];
    }
    else
    {
        numberOfRealDataBlock = 0;
    }
    /// It loads the fixed part (if present)
    if(type->fixedPresent)
    {
        fp.setpos(0);
        line=fp.getLine("[Fixed Part]");
        if(strcmp(line, "[Fixed Part]") == 0)
        {
        	fixed.previous = previous; //AB2014
            fixed.loadFields(fp);
        }
        else
            throw new PacketExceptionFileFormat("[Fixed Part] section not found");
    } else
    	fixed.previous = previous;//AB2014

    if(type->variablePresent)
    {
        for(int i=0; i< type->numberOfRBlocks; i++)
            if(type->rBlockVariable[i] == false)
                numberOfRealDataBlock[i] = type->maxNumberOfBlock[i];
    }

    if(type->variablePresent)
    {
// 		cout << "CP --- " << type->name << endl;
        block = (SDFBlock*) new SDFBlock[type->nblockmax];

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
                delete[] argv;
                delete file;
            }
            else {
            	delete[] argv;
                throw new PacketExceptionFileFormat("rblock file name not found.");
            }
        }
    }
//     cout << "1------" << endl;
    return true;
}

//OK
dword SDFBlock::sizeMax()
{
	/// for fixed part
    dword dim = fixed.size(); 
    ///variable part

    for(dword i=0; i < type->nblockmax; i++)
    {
        dim += block[i].sizeMax();
    }
    return dim;
}

dword SDFBlock::size()
{
	/// for fixed part
    dword dim = fixed.size();
	///variable part
    word bi = 0;
    word rbi = 0;
    for(int i=0; i < type->nblockmax; i++)
    {
        bi = block[i].getID();
        rbi = block[i].getRBlockType();
        word nrdb = getNumberOfBlocks(rbi);
        if(bi < nrdb)
            dim += block[i].size();
        else
            i += type->maxNumberOfBlock[rbi] - getNumberOfBlocks(rbi) - 1;
    }
    return dim;
}

SDFBlock* SDFBlock::getBlock(word nblock, word rBlockIndex)
{
	if(rBlockIndex == 0)
		return &block[nblock];
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


void SDFBlock::setNumberOfBlocks(word number, word rblockIndex) throw (PacketException*)
{

	/// In case the variable part is not present or rBlockVariable = false,
	/// the field where to save the value is not present. The dimension is fixed.
    if(!type->variablePresent || !type->rBlockVariable[rblockIndex])
    {
        throw new PacketException("It is not possible to set setNumberOfBlocks for this rBlock: variable part not present");
        return;
    }
    PartOfPacket* pop = &fixed;
    if(number > type->maxNumberOfBlock[rblockIndex])
        throw new PacketException("It is not possible to set setNumberOfBlocks: too much blocks");
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


word SDFBlock::getNumberOfBlocks(word rblockIndex)
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


word SDFBlock::getCurrentNumberOfBlocks()
{
    word nblock = 0;
    for(int i=0; i< type->numberOfRBlocks; i++)
        nblock = getNumberOfBlocks(i);
    return nblock;
}

bool SDFBlock::setOutputStream(ByteStreamPtr os, dword first)
{
    dword start = first;
    /// It sets the output stream for the fixed part (if present)
    if(type->fixedPresent)
    {
        fixed.setOutputStream(os, start);
        outputstream = ByteStreamPtr(new ByteStream((os->stream + start), size(), os->isBigendian()));
        start += fixed.size();
    }
    if(type->variablePresent)
    {
        dword bi = 0;
        dword rbi = 0;
        for(word i=0; i < type->nblockmax; i++)
        {
            bi = block[i].getID();
            rbi = block[i].getRBlockType();
            if(bi < getNumberOfBlocks(rbi))
            {
                /// Only for valid blocks
                block[i].setOutputStream(os, start);
                start += block[i].size();
            }
            else
                i += type->maxNumberOfBlock[rbi] - getNumberOfBlocks(rbi) - 1;
        }
    }
    return true;
}

ByteStreamPtr SDFBlock::generateStream(bool bigendian)
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
            if(bi < getNumberOfBlocks(rbi))
            {
                /// Only for valid blocks
                block[i].generateStream(bigendian);
            }
            else
                i += type->maxNumberOfBlock[rbi] - getNumberOfBlocks(rbi) - 1;
        }
    }

    return outputstream;
}

bool SDFBlock::setByteStream(ByteStreamPtr s, int decodeType)
{
	//cout << "bool SDFBlock::setByteStream(ByteStreamPtr s)" << " " << s << endl; //AB
    dword bytestart=0;
    dword bytestop=0;
    this->stream->setStream(s, 0, s->size() - 1);
	
	if(decodeType == 0)
		return true;

    //ByteStreamPtr  tmpstream = new ByteStream(s->stream, s->size(), s->isBigendian());
    //ByteStreamPtr s = new ByteStream(k->stream, k->size(), k->isBigendian());
    // It sets the output stream for the fixed part (if present)
    if(type->fixedPresent)
    {
        bytestop += fixed.size() - 1;
        if(tempBlock1->setStream(s, bytestart, bytestop))
            if(!fixed.setByteStream(tempBlock1))
                return false;
        bytestart = bytestop + 1;
    }
	if(decodeType == 1)
		return true;
    if(type->variablePresent)
    {
        word bi = 0;
        word rbi = 0;
        for(int i=0; i < type->nblockmax; i++)
        {
            bi = block[i].getID();
            rbi = block[i].getRBlockType();
            word nrdb = getNumberOfBlocks(rbi);
            if(bi < nrdb)
            {
                /// Only for valid blocks
            	/// 1) first of all the fixed part of block[i] must be set 
            	/// before calling  block[i].size(), otherwise only random values are present
                tempBlock1->setStream(s, bytestart, s->size() - 1);
                block[i].setByteStream(tempBlock1, decodeType);
                /// 2) Now the correct computation of the dimension can be started
                if(bytestop != 0)
                    bytestop += block[i].size();
                else
                    bytestop += block[i].size() - 1;
                if(tempBlock1->setStream(s, bytestart, bytestop))
                    if(!block[i].setByteStream(tempBlock1, decodeType))
                        return false;
                bytestart = bytestop + 1;
            }
            else
                i += type->maxNumberOfBlock[rbi] - getNumberOfBlocks(rbi) - 1;
        }
    }
    return true;
}


char** SDFBlock::printValue(const char* addString)
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
            if(bi < getNumberOfBlocks(rbi))
            {
                /// Only for valid blocks
                ct = block[i].printValue(addString);
                for(int ii=0; ct[ii] != 0; ii++)
                {
                    cc[index] = ct[ii];
                    index++;
                }
            }
            else
                i += type->maxNumberOfBlock[rbi] - getNumberOfBlocks(rbi) - 1;
        }
    }
    cc[index] = 0;
    return cc;
}

void SDFBlock::printValueStdout()
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
            if(bi < getNumberOfBlocks(rbi))
            {
                /// Only for valid blocks
                block[i].printValueStdout();
            }
            else
                i += type->maxNumberOfBlock[rbi] - getNumberOfBlocks(rbi) - 1;
        }
    }
}


string* SDFBlock::printStructure()
{
    return new string("string* SDFBlock::printStructure() - TODO");
}


word SDFBlock::getTotalNumberOfFields()
{
	/// for fixed part
    word dim = fixed.getNumberOfFields(); 
    word bi = 0;
    word rbi = 0;
    int j;
    for(j=0; j < type->nblockmax; j++)
    {
        bi = block[j].getID();
        rbi = block[j].getRBlockType();
        if(bi < getNumberOfBlocks(rbi))
            dim += block[j].getNumberOfFields();
        else
            j += type->maxNumberOfBlock[rbi] - getNumberOfBlocks(rbi) - 1;
    }
    return dim;
}

word SDFBlock::getFieldValue(string fieldname) {
	return fixed.getFieldValue(fieldname);
	
}


signed short SDFBlock::getFieldValue_16i(string fieldname) {
	return fixed.getFieldValue_16i(fieldname);
	
}



word SDFBlock::getFieldValue_16ui(string fieldname) {
	return fixed.getFieldValue_16ui(fieldname);
	
}



signed long SDFBlock::getFieldValue_32i(string fieldname){
	return fixed.getFieldValue_32i(fieldname);
	
}



unsigned long SDFBlock::getFieldValue_32ui(string fieldname){
	return fixed.getFieldValue_32ui(fieldname);
	
}



float SDFBlock::getFieldValue_32f(string fieldname){
	return fixed.getFieldValue_32f(fieldname);
	
}



double SDFBlock::getFieldValue_64f(string fieldname){
	return fixed.getFieldValue_64f(fieldname);
	
}



void SDFBlock::setFieldValue(string fieldname, word value){
	fixed.setFieldValue(fieldname, value);
	
}



void SDFBlock::setFieldValue_16i(string fieldname, signed short value){
	fixed.setFieldValue_16i(fieldname, value);
	
}



void SDFBlock::setFieldValue_16ui(string fieldname, word value){
	fixed.setFieldValue_16ui(fieldname, value);
	
}



void SDFBlock::setFieldValue_32i(string fieldname, signed long value){
	fixed.setFieldValue_32i(fieldname, value);
	
}



void SDFBlock::setFieldValue_32ui(string fieldname, unsigned long value){
	fixed.setFieldValue_32ui(fieldname, value);
	
}



void SDFBlock::setFieldValue_32f(string fieldname, float value){
	fixed.setFieldValue_32f(fieldname, value);
	
}



void SDFBlock::setFieldValue_64f(string fieldname, double value){
	fixed.setFieldValue_64f(fieldname, value);
	
}


