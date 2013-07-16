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

//##ModelId=3C87743F029E
//##Documentation
//##	$Date: 2012/06/08 15:14:29 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/InputText.h,v 1.4 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Id: InputText.h,v 1.4 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Revision: 1.4 $
//##	\brief This class represents generic type of input. The input must be a text input. This class is used
//##	for the configuration files
class InputText
{
    public:

        //##ModelId=3AA6490E015C
        InputText();

        //##ModelId=3AA6490E016F
        virtual ~InputText();

        //##ModelId=3AA6490E018D
        virtual char* getLine() throw(PacketExceptionIO*) = 0 ;

        //##ModelId=3AA6490E01AB
        virtual char* getLine(const char* s) throw(PacketExceptionIO*) = 0;

        //##ModelId=3AA6490E01FB
        virtual char* getLastLineRead() = 0;

        virtual char* getInputTextName() = 0;

        //##ModelId=3EADC12902FB
        virtual bool isClosed();

        //##ModelId=3EADC1290322
        virtual bool isEOF();

    protected:

        //##ModelId=3EADC1290274
        bool eof;

        //##ModelId=3EADC12902AC
        bool closed;

};
}
#endif
