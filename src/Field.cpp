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

using namespace PacketLib;

static FieldType** filedTypeList = 0;


Field::Field(char* n, char* dim, char* prVal, int count) : progressiv(count)
{
    value = 0;
    /// create FieldType list
    if(filedTypeList == 0)
    {
        //cout << "create list" << endl;
        dword nb = CONFIG_MAXNUMBEROFLINES_OFCONFIGILES/3;
        filedTypeList = (FieldType**) new FieldType* [nb];
        for(dword i = 0; i<nb; i++)
            filedTypeList[i] = 0;
    }
    //cout << "------" << endl;
    int i = 0;
    type = 0;
    while(filedTypeList[i] != 0)
    {
        //cout << filedTypeList[i]->name << " " << n << endl;
        if(filedTypeList[i]->name == n)
        {
            type = filedTypeList[i];
            break;
        }
        else
            i++;
    }
    //cout << type << endl;
    if(type == 0)
    {
        type = new FieldType;
        filedTypeList[i] = type;

        type->name = n;

        type->dimension = atoi(dim);
        if(strcmp(prVal, "none") != 0)
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

void Field::getType(char* type, enum LogicalFieldDataType &outtype, int &outtypenfields, int &outputfieldsbitsize) {
	outtype = UNKNOWN;
	outputfieldsbitsize = 0;
	outtypenfields = 0;
	int dim = atoi(type);
	if(dim == 0) {
		//>= 16bit
		outputfieldsbitsize = 16;
		if(strcmp(type, "int16") == 0) {
			outtypenfields = 1;
			outtype = INT16;
		} else if(strcmp(type, "uint16") == 0) {
			outtypenfields = 1;
			outtype = UINT16;
		} else if(strcmp(type, "int32") == 0) {
			outtypenfields = 2;
			outtype = INT32;
		} else if(strcmp(type, "uint32") == 0) {
			outtypenfields = 2;
			outtype = UINT32;
		} else if(strcmp(type, "float") == 0) {
			outtypenfields = 2;
			outtype = FLOAT;
		} else if(strcmp(type, "int64") == 0) {
			outtypenfields = 4;
			outtype = INT64;
		} else if(strcmp(type, "uint64") == 0) {
			outtypenfields = 4;
			outtype = UINT64;
		} else if(strcmp(type, "double") == 0) {
			outtypenfields = 4;
			outtype = DOUBLE;
		}
	} else {
		//<=16 bit (unsigned)
		outtypenfields = 1;
		outputfieldsbitsize = dim;
		switch(dim) {
			case 1:
			outtype = UINT1;
			break;
			case 2:
			outtype = UINT2;
			break;
			case 3:
			outtype = UINT3;
			break;
			case 4:
			outtype = UINT4;
			break;
			case 5:
			outtype = UINT5;
			break;
			case 6:
			outtype = UINT6;
			break;
			case 7:
			outtype = UINT7;
			break;
			case 8:
			outtype = UINT8;
			break;
			case 9:
			outtype = UINT9;
			break;
			case 10:
			outtype = UINT10;
			break;
			case 11:
			outtype = UINT11;
			break;
			case 12:
			outtype = UINT12;
			break;
			case 13:
			outtype = UINT13;
			break;
			case 14:
			outtype = UINT14;
			break;
			case 15:
			outtype = UINT15;
			break;
			case 16:
			outtype = UINT16;
			break;
		}
	}
}

