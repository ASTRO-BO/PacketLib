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

namespace PacketLib
{


class FieldType
{

public:

    //Dimension of field in bit.
    word dimension;

    //It indicates that there's a predefined value for this field.
    bool thereIsPredefinedValue;

    //Predefined value of field (for the generation of packet).
    int predefinedValue;

    //Name of the field.
    char* name;
};



//A single field of a telemetry packet
class Field
{
public:

    //Constructor of class.
    Field(char* name, char* dimension, char* predefinedValue, int progressiv);

    //Destructor of class.
    ~Field();

    //Value reads from stream of byte (from packet).
    word value;

    //Dimension of field in bit.
    inline dword getDimension()
    {
        return type->dimension;
    };

    //It indicates that there's a predefined value for this field.
    inline bool thereIsPredefinedValue()
    {
        return type->thereIsPredefinedValue;
    };

    //Predefined value of field (for the generation of packet).
    inline int getPredefinedValue()
    {
        return type->predefinedValue;
    };

    //Name of the field.
    inline char* getName()
    {
        return type->name;
    };

    inline int getProgressiv()
    {
        return progressiv;
    };

protected:

    //Index of packet in the list of packet.
    int progressiv;

    FieldType * type;

};

}

#endif
