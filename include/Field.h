/***************************************************************************
                          Field.h  -  description
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
#ifndef Field_h_h
#define Field_h_h

#include "PacketLibDefinition.h"

namespace PacketLib {

//##ModelId=3C0F6C1902FA
//##Documentation
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/Field.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: Field.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.2 $
//##	\brief This is a single field of a packet
class Field
{
    public:

        //##ModelId=3C0F6C1A0001
        //##Documentation
        //## Constructor of class.
        Field(char* name, char* dimension, char* predefinedValue, int progressiv);

        //##ModelId=3ACCD75E036B
        //##Documentation
        //## Destructor of class.
        ~Field();

        //##Documentation
        //## Dimension of field in bit.
        word dimension;

        //##ModelId=3C0F6C1A0000
        //##Documentation
        //## It indicates that there's a predefined value for this field.
        bool thereIsPredefinedValue;

        //##ModelId=3C0F6C1903E5
        //##Documentation
        //## Predefined value of field (for the generation of packet).
        int predefinedValue;

        //##ModelId=3C0F6C1903E6
        //##Documentation
        //## Index of packet in the list of packet.
        int progressiv;

        //##ModelId=3ACCD75E033C
        //##Documentation
        //## Name of the field.
        char* name;

        //##Documentation
        //## Value reads from stream of byte (from packet).
        word value;

};

}

#endif
