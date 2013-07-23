/***************************************************************************
                          InputText.h  -  description
                             -------------------
    begin                : Mon Mar 4 2002
    copyright            : (C) 2002 by Andrea Bulgarelli
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

#ifndef INPUTTEXT_H
#define INPUTTEXT_H

#include "PacketLibDefinition.h"
#include "PacketExceptionIO.h"

namespace PacketLib {

//This class represents generic type of input. The input must be a text input. This class is used for the configuration files
class InputText
{
    public:

        InputText();

        virtual ~InputText();

        virtual char* getLine() throw(PacketExceptionIO*) = 0 ;

        virtual char* getLine(const char* s) throw(PacketExceptionIO*) = 0;

        virtual char* getLastLineRead() = 0;

        virtual char* getInputTextName() = 0;
        
        virtual long getpos() = 0;
        
        virtual long setpos(long offset) throw(PacketExceptionIO*) = 0;

        virtual bool isClosed();

        virtual bool isEOF();

    protected:

        bool eof;

        bool closed;

};
}
#endif
