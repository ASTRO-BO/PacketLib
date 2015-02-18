/***************************************************************************
                          Field.h   
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

#ifndef _FIELD_H_H
#define _FIELD_H_H

#include "PacketLibDefinition.h"
#include <string>
#include <map>

namespace PacketLib
{
	
enum LogicalFieldDataType { UNKNOWN, UINT1, UINT2, UINT3, UINT4, UINT5, UINT6, UINT7, UINT8, UINT9, UINT10, UINT11, UINT12, UINT13, UINT14, UINT15, UINT16, INT16, UINT24, INT24, UINT32, INT32, UINT64, INT64, FLOAT, DOUBLE, BYTEARRAY };

class FieldType
{

public:

    /// Dimension of field in bit.
    word dimension;

    /// It indicates that there's a predefined value for this field.
    bool thereIsPredefinedValue;

    /// Predefined value of field (for the generation of packet).
    int predefinedValue;

    /// Name of the field.
	std::string name;
	
	/// Logical type
	enum LogicalFieldDataType type;
};



/// A single field of a telemetry packet
class Field
{
public:

    /// Constructor of class.
	Field(std::string name, std::string typeStr, std::string dim, std::string prVal, int count);

    /// Destructor of class.
    ~Field();

    /// Value reads from stream of byte (from packet).
    word value;

    /// Dimension of field in bit.
    inline dword size()
    {
        return type->dimension;
    };

    /// It indicates that there's a predefined value for this field.
    inline bool thereIsPredefinedValue()
    {
        return type->thereIsPredefinedValue;
    };

    /// Predefined value of field (for the generation of packet).
    inline int getPredefinedValue()
    {
        return type->predefinedValue;
    };

    /// Name of the field.
    std::string getName()
    {
        return type->name.c_str();
    };

	/// Return the logical field data type.
	LogicalFieldDataType getType()
	{
		return type->type;
	}

    inline int getProgressiv()
    {
        return progressiv;
    };
	
	void print();
	
protected:

	static std::map<std::string, LogicalFieldDataType> typeStringToEnum;
	static std::map<std::string, LogicalFieldDataType> makeMap();

    /// Index of packet in the list of packet.
    int progressiv;

    FieldType * type;

};

}

#endif
