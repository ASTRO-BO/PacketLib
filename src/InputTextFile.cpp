/***************************************************************************
                          InputTextFile.cpp  -  description
                             -------------------
    begin                : Mon Mar 4 2002
    copyright            : (C) 2002 by Andrea Bulgarelli
    email                : bulgarelli@tesre.bo.cnr.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "InputTextFile.h"
#include "MemoryBuffer.h"

using namespace PacketLib;

int InputTextFile::nListOfBuffers = 0;
MemoryBuffer** InputTextFile::listOfBuffers = 0;

//##ModelId=3AA64922006A
InputTextFile::InputTextFile() : InputText()
{
	//create buffer list
    if(InputTextFile::listOfBuffers == 0) {
    	int nb = 2000;
    	InputTextFile::listOfBuffers = (MemoryBuffer**) new MemoryBuffer* [nb];
    	for(int i = 0; i<nb; i++)
    		InputTextFile::listOfBuffers[i] = 0;
    }
    usebuffer = false;
    buffer = 0;
}


//##ModelId=3AA64922007E
InputTextFile::~InputTextFile()
{

}


//##ModelId=3DA3E57A02F8
bool InputTextFile::fchdir() throw(PacketExceptionIO*)
{
    try
    {
    	if(usebuffer)
    		return true;
    	else
        	return file.fchdir();
    }
    catch(PacketExceptionIO* e)
    {
        e->add("InputTextFile::fchdir() -- ");
        throw e;
    }
}


//##ModelId=3AA64922009C
bool InputTextFile::open(char** parameters) throw(PacketExceptionIO*)
{
	//cout << "open " << parameters[0] << endl;
	
    try
    {
        bool ret;
        //check if the file has been already loaded into MemoryBuffer
        //find the name of the buffer in the list
    	
        	
    	buffer = 0;
    	usebuffer = false;
    	int i = 0;
		while(InputTextFile::listOfBuffers[i] != 0) {
			char* filename = parameters[0];
			char* buffername = InputTextFile::listOfBuffers[i]->getName();
			//cout << "# i: " << i << " " << buffername << " " << filename << endl;
			if(strcmp(filename, buffername) == 0) {
				//cout << "# BN: " << listOfBuffers[i]->getName() << endl;
				buffer = (MemoryBuffer*) listOfBuffers[i];
				usebuffer = true;
				ret = true;
			}
			i++;
		}
		if(usebuffer == false) {
			ret =  file.open(parameters[0]);
        	eof = file.isEOF();
        	closed = file.isClosed();
        	
        	
			buffer =  new MemoryBuffer;
			buffer->setName(parameters[0]);
			//cout << "# NEW BN: " << buffer->getName() << endl;
    		InputTextFile::listOfBuffers[i] = buffer;
    		bool eofl = false;
    		while(!eofl) {
    			char* ret =  file.getLine();
    			eofl = file.isEOF();
    			//cout << ret << endl;
				buffer->setbuffer(ret);
    		}
    	}
    	buffer->setpos(0);
    	/*
    	cout << "#### BUFFER: " << buffer << " " << buffer->getName() << endl;
    	cout << "#### check list: " << endl;
    	char* line;
    	line = buffer->getbuffer();
    	if(line) cout << "** " << line << endl;
    	while(line != 0) {
    		line = buffer->getbuffer();
    		if(line) cout << "** " << line << endl;
    	}
    	buffer->setpos(0);
    	*/
        return ret;
    }
    catch(PacketExceptionIO* e)
    {
        throw e;
    }
};

//##ModelId=3AA6492200F6
void InputTextFile::close()  throw(PacketExceptionIO*)
{
    file.close();
    eof = file.isEOF();
    closed = file.isClosed();
};

//##ModelId=3AA64922011E
char* InputTextFile::getLine() throw(PacketExceptionIO*)
{
    try
    {
        char* ret;
		ret = buffer->getbuffer();
		//cout << "## " << ret << endl;
		if(ret == 0) {
			eof = true;
		}
		//closed = file.isClosed();
        return ret;
    }
    catch(PacketExceptionIO* e)
    {
        throw e;
    }
}


//##ModelId=3AA64922013C
char* InputTextFile::getLine(const char* s) throw(PacketExceptionIO*)
{
    char* line;
    bool eof;
    line = buffer->getbuffer();
    if(line == 0) {
		eof = true;
	}
    
    while(strstr(line, s) == NULL) {
    	line = buffer->getbuffer();
    	if(line == 0) {
			eof = true;
		}
    	if(eof == true)
			break;
	}
    
    //closed = file.isClosed();
    return line;
}


//##ModelId=3AA649220196
char* InputTextFile::getLastLineRead()
{
	return buffer->getlastbuffer();
}


//##ModelId=3AA6492201BE
long InputTextFile::getpos()
{
    return buffer->getpos();
}


//##ModelId=3AA6492201DC
bool InputTextFile::memBookmarkPos()
{
    return buffer->memBookmarkPos();
}


//##ModelId=3AA64922020E
int InputTextFile::setFirstPos()
{
    return buffer->setpos(0);
}


//##ModelId=3AA64922022C
bool InputTextFile::setLastBookmarkPos()
{
	return buffer->setLastBookmarkPos();
}


//##ModelId=3AA64922025E
long InputTextFile::setpos(long offset) throw(PacketExceptionIO*)
{
    long l;

	l = buffer->setpos(offset);
	eof = false;
	closed = false;
    return l;
}
