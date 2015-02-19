/***************************************************************************
                          InputTextFile.cpp  -  description
                             -------------------
    begin                : Mon Mar 4 2002
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

#include "InputTextFile.h"
#include "MemoryBuffer.h"
#include "PacketLibDefinition.h"

using namespace PacketLib;

int InputTextFile::nListOfBuffers = 0;
MemoryBuffer** InputTextFile::listOfBuffers = 0;


InputTextFile::InputTextFile() : InputText()
{
    /// create buffer list
    if(InputTextFile::listOfBuffers == 0)
    {
        int nb = CONFIG_MAXNUMBER_OFCONFIGILES;
        InputTextFile::listOfBuffers = (MemoryBuffer**) new MemoryBuffer* [nb];
        for(int i = 0; i<nb; i++)
            InputTextFile::listOfBuffers[i] = 0;
    }
    usebuffer = false;
    buffer = 0;
}


InputTextFile::~InputTextFile()
{

}


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


bool InputTextFile::open(char** parameters) throw(PacketExceptionIO*)
{
    //cout << "open " << parameters[0] << endl;


    bool ret;
    /// check if the file has been already loaded into MemoryBuffer
    /// find the name of the buffer in the list


    buffer = 0;
    usebuffer = false;
    int i = 0;
    while(InputTextFile::listOfBuffers[i] != 0)
    {
        char* filename = parameters[0];
        char* buffername = InputTextFile::listOfBuffers[i]->getName();
        //cout << "# i: " << i << " " << buffername << " " << filename << endl;
        if(strcmp(filename, buffername) == 0)
        {
            //cout << "# BN: " << listOfBuffers[i]->getName() << endl;
            buffer = (MemoryBuffer*) listOfBuffers[i];
            file.setFileName(filename);
            usebuffer = true;
            ret = true;
            break;
        }
        i++;
    }
    if(i>CONFIG_MAXNUMBER_OFCONFIGILES)
        throw new PacketExceptionIO("InputTextFile::open(char** parameters) too many config files");

    try
    {
        if(usebuffer == false)
        {
            ret =  file.open(parameters[0]);
            eof = file.isEOF();
            closed = file.isClosed();


            buffer =  new MemoryBuffer;
            buffer->setName(parameters[0]);
            //cout << "# NEW BN: " << buffer->getName() << endl;
            InputTextFile::listOfBuffers[i] = buffer;
            bool eofl = false;
            while(!eofl)
            {
                char* ret =  file.getLine();
                eofl = file.isEOF();
                //cout << ret << endl;
                buffer->setbuffer(ret);
            }
        }
        buffer->setpos(0);
        /*if(usebuffer == false) {
        	int i=0;
        	cout << "@@@@ add buffer to  InputTextFile()::buffer " << parameters[0] << endl;
        	while(InputTextFile::listOfBuffers[i] != 0)
        		 InputTextFile::listOfBuffers[i++]->printBuffer();
        }*/
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
    catch(PacketException* e)
    {
        throw e;
    }

}


void InputTextFile::close()  throw(PacketExceptionIO*)
{
    file.close();
    eof = file.isEOF();
    closed = file.isClosed();
}


char* InputTextFile::getLine() throw(PacketExceptionIO*)
{
    try
    {
        char* ret;
        ret = buffer->getbuffer();
        eof = buffer->getEOF();
        return ret;
    }
    catch(PacketExceptionIO* e)
    {
        throw e;
    }
}



char* InputTextFile::getLine(const char* s) throw(PacketExceptionIO*)
{
    char* line;
    bool eof;
    line = buffer->getbuffer();
    if(line == 0)
    {
        eof = true;
    }

    while(strstr(line, s) == NULL)
    {
        line = buffer->getbuffer();
        if(line == 0)
        {
            eof = true;
        }
        if(eof == true)
            break;
    }

    //closed = file.isClosed();
    return line;
}



char* InputTextFile::getLastLineRead()
{
    return buffer->getlastbuffer();
}


long InputTextFile::getpos()
{
    return buffer->getpos();
}


bool InputTextFile::memBookmarkPos()
{
    return buffer->memBookmarkPos();
}


int InputTextFile::setFirstPos()
{
    return buffer->setpos(0);
}


bool InputTextFile::setLastBookmarkPos()
{
    return buffer->setLastBookmarkPos();
}


long InputTextFile::setpos(long offset) throw(PacketExceptionIO*)
{
    long l;

    l = buffer->setpos(offset);
    eof = false;
    closed = false;
    return l;
}
