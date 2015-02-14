/***************************************************************************
                          ConfigurationFile.cpp
                          -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001, 2013 by Andrea Bulgarelli
                           (C) 2014 by Andrea Zoli
    email                : bulgarelli@iasfbo.inaf.it, zoli@iasfbo.inaf.it
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
#include <string>
#include <algorithm>

using namespace PacketLib;

ConfigurationFile::ConfigurationFile()
{
    currentpwd = 0;
}


ConfigurationFile::~ConfigurationFile()
{
    free(currentpwd);
}


bool ConfigurationFile::open(char** parameters) throw(PacketExceptionIO*)
{
    free(currentpwd);

    bool ret;
    currentpwd = getcwd(NULL, 512L);

	ret = InputTextFile::open(parameters);
    if(!closed)
        fchdir();
    return ret;
}



void ConfigurationFile::close() throw(PacketExceptionIO*)
{
    InputTextFile::close();
    chdir(currentpwd);
}



char* ConfigurationFile::getLine() throw(PacketExceptionIO*)
{
    char* temp;

    try
    {
        temp = InputTextFile::getLine();
        if(temp[0] == 0)
        	return temp;
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
