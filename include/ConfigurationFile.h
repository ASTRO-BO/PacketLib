/***************************************************************************
                          ConfigurationFile.h  -  description
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001 by Andrea Bulgarelli
    email                : bulgarelli@bo.iasf.cnr.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/

#ifndef CONFIGURATIONFILE_H
#define CONFIGURATIONFILE_H

#include "PacketExceptionIO.h"
#include "InputTextFile.h"

namespace PacketLib
{

//##ModelId=3EADC12201A5
//##Documentation
//##	$Date: 2012/06/08 15:14:29 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/ConfigurationFile.h,v 1.3 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Id: ConfigurationFile.h,v 1.3 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Revision: 1.3 $
//##	\brief This class represent the text file which contains the configurations
class ConfigurationFile : public InputTextFile
{
public:

    //##ModelId=3EADC12701F1
    ConfigurationFile();

    //##ModelId=3EADC12701F4
    ~ConfigurationFile();

    //##ModelId=3EADC12701F5
    virtual bool open(char** parameters) throw(PacketExceptionIO*);

    //##ModelId=3EADC12701F8
    virtual char* getLine() throw(PacketExceptionIO*);

    //##ModelId=3EADC12701FB
    virtual char* getLine(const char* s) throw(PacketExceptionIO*);

    //##ModelId=3EADC12701FE
    virtual void close() throw(PacketExceptionIO*);

private:

    //##ModelId=3EADC12701EF
    char* currentpwd;

};

}

#endif
