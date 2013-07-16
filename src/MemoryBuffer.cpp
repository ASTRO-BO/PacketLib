/***************************************************************************
                      MemoryBuffer.cpp  -  description
                         -------------------
begin                : Fri Apr 12 2002
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

#include "MemoryBuffer.h"
#include <unistd.h>
#include "File.h"
#include "OutputFile.h"

using namespace PacketLib;

//##ModelId=3DA3E57B01A4
MemoryBuffer::MemoryBuffer()
{
    dim = 5000;
    buffer = (char**) malloc(sizeof(char*)*dim);
    for(dword i=0; i<dim; i++)
        buffer[i] = 0;
    indexread = 0;
    indexwrite = 0;
}


//##ModelId=3DA3E57B01A5
MemoryBuffer::~MemoryBuffer()
{
	if(buffer)
		freebuffer();
}

void MemoryBuffer::freebuffer() {
    if(!buffer)
    	return;
    for(dword i = 0; i < dim; i++) {
        delete[] buffer[i];
	buffer[i] = 0;
    }
    free(buffer);
    buffer = 0;
}


/** Read property of char** buffer. */
//##ModelId=3DA3E57B0245
char* MemoryBuffer::getbuffer()
{
    if(indexread <= dim)
    {
        return buffer[indexread++];
    }
    else
        return 0;
}


/** Read property of char** buffer. */
//##ModelId=3DA3E57B0280
char* MemoryBuffer::getbuffer(dword index)
{

    if(index <= dim)
    {
        return buffer[index];
    }
    else
        return 0;
}


/** Write property of char** buffer. */
//##ModelId=3DA3E57B01D6
void MemoryBuffer::setbuffer(char* _newVal)
{
    buffer[indexwrite] = _newVal;
    indexwrite++;
    if(indexwrite > dim)
        ;                        //TODO
    //realloc
}


/** Write property of char** buffer. */
//##ModelId=3DA3E57B0212
void MemoryBuffer::setbuffer(char* _newVal, dword index)
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

    buffer[index] = _newVal;

    if(indexwrite > dim)
        ;                        //TODO
    //realloc
}


//##ModelId=3DA3E57B02B2
void MemoryBuffer::readRewind()
{
    indexread = 0;
}


//##ModelId=3DA3E57B02B3
void MemoryBuffer::writeRewind()
{
    indexwrite = 0;
}


/** No descriptions */
//##ModelId=3DA3E57B02B4
dword MemoryBuffer::getBufferDimension()
{
    return indexwrite;
}


//##ModelId=3DA3E57B02EE
bool MemoryBuffer::loadBuffer(char* filename)  throw(PacketExceptionIO*)
{
    	bool ret;
   	File* itf= new File;

    	indexread = 0;
    	indexwrite = 0;
    

    	ret = itf->open(filename, "r");
    	unsigned long tempdim = itf->getNumberOfStringLines();
        if(tempdim > dim) {
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


//##ModelId=3DA3E57B0320
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
