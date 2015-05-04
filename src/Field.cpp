/***************************************************************************
                          Field.cpp  -  description
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


#include "Field.h"
#include "Utility.h"

//#define DEBUG 1

using namespace PacketLib;

static FieldType** filedTypeList = 0;

std::map<std::string, LogicalFieldDataType> Field::makeMap()
{
	std::map<std::string, LogicalFieldDataType> map;

	map[""] = UNKNOWN;
	map["uint1"] = UINT1;
	map["uint2"] = UINT2;
	map["uint3"] = UINT3;
	map["uint4"] = UINT4;
	map["uint5"] = UINT5;
	map["uint6"] = UINT6;
	map["uint7"] = UINT7;
	map["uint8"] = UINT8;
	map["uint9"] = UINT9;
	map["uint10"] = UINT10;
	map["uint11"] = UINT11;
	map["uint12"] = UINT12;
	map["uint13"] = UINT13;
	map["uint14"] = UINT14;
	map["uint15"] = UINT15;
	map["uint16"] = UINT16;
	map["int16"] = INT16;
	map["uint24"] = UINT24;
	map["int24"] = INT24;
	map["uint32"] = UINT32;
	map["int32"] = INT32;
	map["uint64"] = UINT64;
	map["int64"] = INT64;
	map["float"] = FLOAT;
	map["double"] = DOUBLE;
	map["bytes"] = BYTEARRAY;

	return map;
}

std::map<std::string, LogicalFieldDataType> Field::typeStringToEnum = Field::makeMap();

Field::Field(std::string name, std::string typeStr, std::string dim, std::string prVal, int count, int sectionOffset)
	: progressiv(count)
{
    value = 0;
    /// create FieldType list
    if(filedTypeList == 0)
    {
        dword nb = CONFIG_MAXNUMBEROFLINES_OFCONFIGILES/3;
        filedTypeList = (FieldType**) new FieldType* [nb];
        for(dword i = 0; i<nb; i++)
            filedTypeList[i] = 0;
    }
    int i = 0;
    type = 0;
    while(filedTypeList[i] != 0)
    {
        if(filedTypeList[i]->name == name)
        {
            type = filedTypeList[i];
            break;
        }
        else
            i++;
    }
    if(type == 0)
    {
        type = new FieldType;
        filedTypeList[i] = type;
        type->name = name;
		type->dimension = atoi(dim.c_str());
		type->type = Field::typeStringToEnum[typeStr];
		type->sectionOffsetBits = sectionOffset;
        type->sectionOffsetBytes = (sectionOffset % 8) ? -1 : sectionOffset / 8;
#ifdef DEBUG
		std::cout << "Adding field '" << name << "', " << type->dimension << " bits type " << typeStr << " (" << type->type << ")" << " section offset " << type->sectionOffsetBits << " " << type->sectionOffsetBytes << std::endl;
#endif

        if(prVal.compare("none") != 0)
        {
            type->thereIsPredefinedValue = true;
            type->predefinedValue = Utility::convertToInteger(prVal);
			value = type->predefinedValue; //AB
        }
        else
        {
            type->predefinedValue = 0;
            type->thereIsPredefinedValue = false;
        }
    }
}


Field::~Field()
{

}

void Field::print() {
	cout << progressiv << " " << getName() << " " << size() << endl;
}
