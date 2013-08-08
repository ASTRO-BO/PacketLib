/***************************************************************************
                          ConfigurationFile.h
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

#ifndef _CONFIGURATIONFILE_H
#define _CONFIGURATIONFILE_H

#include "PacketExceptionIO.h"
#include "InputTextFile.h"

namespace PacketLib
{


///	\brief This class represent the text file which contains the configurations
class ConfigurationFile : public InputTextFile
{
public:

    ConfigurationFile();

    ~ConfigurationFile();

    virtual bool open(char** parameters) throw(PacketExceptionIO*);

    virtual char* getLine() throw(PacketExceptionIO*);

    virtual char* getLine(const char* s) throw(PacketExceptionIO*);

    virtual void close() throw(PacketExceptionIO*);

private:

    char* currentpwd;

};

}

#endif
