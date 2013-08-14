/***************************************************************************
                      MemoryBuffer.cpp  -  description
                         -------------------
begin                : Fri Apr 12 2002
copyright            : (C) 2002, 2013 by Andrea Bulgarelli
email                : bulgarelli@iasfbo.inaf.it
***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "MemoryBuffer.h"
#include <unistd.h>
#include "File.h"
#include "OutputFile.h"
#include "PacketLibDefinition.h"

using namespace PacketLib;


MemoryBuffer::MemoryBuffer()
{
    dim = CONFIG_MAXNUMBEROFLINES_OFCONFIGILES;
    buffer = (char**) malloc(sizeof(char*)*dim);
    for(dword i=0; i<dim; i++)
        buffer[i] = 0;
    indexread = 0;
    indexwrite = 0;
}



MemoryBuffer::~MemoryBuffer()
{
    //if(buffer)
    //	freebuffer();
}

bool MemoryBuffer::getEOF() {
	return eof;
}

void MemoryBuffer::printBuffer() {
	if(!buffer)
		return;
	dword i = 0;
	cout << "********************************************" << endl;
	cout << bufferName << endl;
	cout << "**********************" << endl;
	while(buffer[i] != 0) {
		cout << buffer[i++] << endl;
	}
	cout << "********************************************" << endl;

}

void MemoryBuffer::freebuffer()
{
    if(!buffer)
        return;
    for(dword i = 0; i < dim; i++)
    {
        delete[] buffer[i];
        buffer[i] = 0;
    }
    free(buffer);
    buffer = 0;
}


/// Read property of char** buffer. 
char* MemoryBuffer::getbuffer()
{
    if(indexread <= dim)
    {

        char* ret =  getbuffer(indexread);
        indexread++;
        return ret;
    }
    else
        return 0;
}

/// Read property of char** buffer.
char* MemoryBuffer::getbuffer(dword index)
{

    if(index <= dim)
    {
        //int dimline = strlen(buffer[index]);
        //char* ret = (char*) new char[dimline+1];
        //strcpy(ret, buffer[index]);
        char* ret = buffer[index];
        if(ret == 0)
        	eof = true;
        else
        	eof = false;
        return ret;
    }
    else {
    	eof = true;
    	return 0;
    }

}

char* MemoryBuffer::getlastbuffer()
{
    if(indexread <= dim)
    {
        return getbuffer(indexread-1);
    }
    else
        return 0;
}

int MemoryBuffer::getpos()
{
    return indexread;
}

bool MemoryBuffer::memBookmarkPos()
{
    bookmarkpos = indexread;
    return true;
}

bool MemoryBuffer::setLastBookmarkPos()
{
    indexread = bookmarkpos;
    return true;
}

long MemoryBuffer::setpos(int index)
{
    indexread = index;
    return index;
}





/// Write property of char** buffer. 
void MemoryBuffer::setbuffer(char* line) throw (PacketException*)
{
    //copy string
    int dimline = strlen(line);
    buffer[indexwrite] = (char*) new char[dimline+1];
    strcpy(buffer[indexwrite], line);
    indexwrite++;
    if(indexwrite > dim)
        throw new PacketException("MemoryBuffer::setbuffer. Buffer too big");
    //realloc
}


/// Write property of char** buffer. 
void MemoryBuffer::setbuffer(char* line, dword index) throw(PacketException*)
{
    if(index > indexwrite)
    {
        if(index == (indexwrite + 1))
        {
            indexwrite++;
        }
        else
        {
            index = indexwrite + 1;
            indexwrite++;
        }
    }

    if(buffer[index] != 0)
        delete buffer[index];

    int dimline = strlen(line);
    buffer[index] = (char*) new char[dimline+1];
    strcpy(buffer[index], line);


    if(indexwrite > dim)
        throw new PacketException("MemoryBuffer::setbuffer(2). Buffer too big");
    //realloc
}



void MemoryBuffer::readRewind()
{
    indexread = 0;
}



void MemoryBuffer::writeRewind()
{
    indexwrite = 0;
}



dword MemoryBuffer::getBufferDimension()
{
    return indexwrite;
}


bool MemoryBuffer::loadBuffer(char* filename)  throw(PacketExceptionIO*)
{
    bool ret;
    File* itf= new File;

    indexread = 0;
    indexwrite = 0;


    ret = itf->open(filename, "r");
    unsigned long tempdim = itf->getNumberOfStringLines();
    if(tempdim > dim)
    {
        for(int i=0; buffer[i] !=0; i++)
        {
            delete[] buffer[i];
            buffer[i]=0;
        }
        delete[] buffer;
        buffer = (char**) malloc(sizeof(char*)*dim);
        for(dword i=0; i<dim; i++)
            buffer[i] = 0;
    }
    while(!itf->isEOF())
    {
        setbuffer(itf->getLine());
    }

    delete itf;
    return ret;
}



bool MemoryBuffer::saveBuffer(char* filename)  throw(PacketExceptionIO*)
{
    bool ret = true;
    OutputFile* fo = new OutputFile(false);
    char **argv = new char* [1];
    argv[0] = filename;
    fo->open(argv);
    indexread = 0;

    for(unsigned i = 0; i< getBufferDimension(); i++)
    {
        fo->writeString(getbuffer());
        fo->writeString("\n");
    }
    fo->close();

    delete fo;
    return ret;

}

void MemoryBuffer::setName(char* name)
{

	int dimline = strlen(name);
	bufferName = (char*) new char[dimline+1];
	strcpy(bufferName, name);
}


