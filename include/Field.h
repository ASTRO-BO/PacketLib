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
    char* name;
};
	
class LogicalFieldType
{
	
public:
	
	/// Logical type
	enum LogicalFieldDataType type;
	
	///the number of physical fields equivalent to this logical field
	int outtypenfields;
	
	///the number of bits of each single field
	int outputfieldsbitsize;
	
	/// It indicates that there's a predefined value for this field.
	bool thereIsPredefinedValue;
	
	/// Predefined value of the logical field (for the generation of packet).
	double predefinedValue;
	
	/// Name of the field.
	char* name;

};



/// A single field of a telemetry packet
class Field
{
public:

    /// Constructor of class.
    Field(char* name, word dimension, char* predefinedValue, int progressiv);

    /// Destructor of class.
    ~Field();

    /// Value reads from stream of byte (from packet). 16 bits max
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
    inline char* getName()
    {
        return type->name;
    };

    inline int getProgressiv()
    {
        return progressiv;
    };
	
	void print();
	

protected:

    /// Index of packet in the list of packet.
    int progressiv;

    FieldType * type;

};
	
	
class LogicalField
{
public:
	LogicalField(char* name, char* type, char* predefinedValue, int progressiv);
	
	/// Destructor of class.
    ~LogicalField();
	
	/// Get a description of the type (e.g. int32, 16, etc) and the number of bits of each single field
	///\param type (input) the type read from configuration file
	///\param outtype (output) the type as enum
	///\param outtypenfields (output) the number of physical fields equivalent to this logical field
	///\param outputfieldsbitsize (output) the number of bits of each single field
	static void getType(char* type, enum LogicalFieldDataType &outtype, int &outtypenfields, int &outputfieldsbitsize);
	
	/// Dimension of field in bit.
    enum LogicalFieldDataType type()
    {
        return logicaltype->type;
    };
	
    /// It indicates that there's a predefined value for this field.
    inline bool thereIsPredefinedValue()
    {
        return logicaltype->thereIsPredefinedValue;
    };
	
    /// Predefined value of field (for the generation of packet).
    inline double getPredefinedValue()
    {
        return logicaltype->predefinedValue;
    };
	
    /// Name of the field.
    inline char* getName()
    {
        return logicaltype->name;
    };
	
    inline int getProgressiv()
    {
        return progressiv;
    };
	
	
	inline enum LogicalFieldDataType getType()
	{
		return logicaltype->type;
	};
	
	inline int getOutTypeNfields() {
		return logicaltype->outtypenfields;
	};
	
	///the number of bits of each single field
	inline int getOutputFieldsBitSize() {
		return logicaltype->outputfieldsbitsize;
	};
	
	inline void setIndexOfPhysicalField(int progressivph) {
		progressivPhysical = progressivph;
	}
	
	inline int getIndexOfPhysicalField() {
		return progressivPhysical;
	}
	
protected:
	
    /// Index of field in the list of logical fields.
    int progressiv;
	
	/// Index of field in the list of physical fields
	int progressivPhysical;
	
	/// Logical field type
    LogicalFieldType * logicaltype;
	
};

}

#endif
