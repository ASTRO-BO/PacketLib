/***************************************************************************
                          filepacket.cpp  -  description
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001 by Andrea Bulgarelli
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

#include "ConfigurationFile.h"
#include "InputTextFile.h"
#include <unistd.h>

using namespace PacketLib;

//##ModelId=3DA3E568008C
ConfigurationFile::ConfigurationFile()
{
    currentpwd = 0;
}


//##ModelId=3DA3E568008D
ConfigurationFile::~ConfigurationFile()
{
    //free(currentpwd);
}


//##ModelId=3DA3E568008E
bool ConfigurationFile::open(char** parameters) throw(PacketExceptionIO*)
{
    bool ret;
    currentpwd = getcwd(NULL, 512L);
    ret = InputTextFile::open(parameters);
    if(!closed)
        fchdir();
    return ret;
}


//##ModelId=3DA3E56800FD
void ConfigurationFile::close() throw(PacketExceptionIO*)
{
    InputTextFile::close();
    chdir(currentpwd);
}


//##ModelId=3DA3E56800C0
char* ConfigurationFile::getLine() throw(PacketExceptionIO*)
{
    char* temp;

    try
    {
        temp = InputTextFile::getLine();
        while(strstr(temp, "--") !=  NULL)
        {
	    	//delete[] temp; 
            temp = InputTextFile::getLine();
        }
        return temp;
    }
    catch (PacketExceptionIO* e)
    {
        throw e;
    }

}


//##ModelId=3DA3E56800FA
char* ConfigurationFile::getLine(const char* s) throw(PacketExceptionIO*)
{
    char* line;

    try
    {
        line = this->getLine();

        while(strstr(line, s) == NULL)
        {
            line = this->getLine();
            if(strlen(line) == 0)
                return line;
        }
        return line;
    }
    catch(PacketExceptionIO* e)
    {
        throw e;
    }
}
