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

static FieldType** fieldTypeList = 0;

static LogicalFieldType** logicalFieldTypeList = 0;


Field::Field(char* n, word dim, char* prVal, int count) : progressiv(count)
{
    value = 0;
    /// create FieldType list
    if(fieldTypeList == 0)
    {
        //cout << "create list" << endl;
        dword nb = CONFIG_MAXNUMBEROFLINES_OFCONFIGILES/3;
        fieldTypeList = (FieldType**) new FieldType* [nb];
        for(dword i = 0; i<nb; i++)
            fieldTypeList[i] = 0;
    }
    //cout << "------" << endl;
    int i = 0;
    type = 0;
    while(fieldTypeList[i] != 0)
    {
        //cout << fieldTypeList[i]->name << " " << n << endl;
		//qui funziona il confronto tra puntatori e non tra stringhe
		//perche' si sfrutta il fatto che si scorre lo stesso blocco
        if(fieldTypeList[i]->name == n)
        {
            type = fieldTypeList[i];
            break;
        }
        else
            i++;
    }
    //cout << type << endl;
    if(type == 0)
    {
        type = new FieldType;
        fieldTypeList[i] = type;

        type->name = n;

        type->dimension = dim;
        if(strcmp(prVal, "none") != 0)
        {
            type->thereIsPredefinedValue = true;
            type->predefinedValue = Utility::convertToInteger(prVal);
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

LogicalField::LogicalField(char* n, char* type, char* prVal, int count) : progressiv(count)
{
	
	progressivPhysical = -1;
    /// create LogicalFieldType list
    if(logicalFieldTypeList == 0)
    {
        //cout << "create list" << endl;
        dword nb = CONFIG_MAXNUMBEROFLINES_OFCONFIGILES/3;
        logicalFieldTypeList = (LogicalFieldType**) new LogicalFieldType* [nb];
        for(dword i = 0; i<nb; i++)
			logicalFieldTypeList[i] = 0;
    }
    int i = 0;
    logicaltype = 0;
	
    while(logicalFieldTypeList[i] != 0)
    {
		// TODO non funziona la test unit se lascio attivo il meccanismo di caching qui sotto
		
		if(logicalFieldTypeList[i]->name == n)
        {
            logicaltype = logicalFieldTypeList[i];
			//cout << "FOUUND " << n << endl;
            break;
        }
        else
			i++;
    }
    if(logicaltype == 0)
    {
        logicaltype = new LogicalFieldType;
        logicalFieldTypeList[i] = logicaltype;
		
        logicaltype->name = n;
		
		enum LogicalFieldDataType selectedtype;
		int outtypenfields;
		int outputfieldsbitsize;
		getType(type, selectedtype, outtypenfields, outputfieldsbitsize);
		
        logicaltype->type = selectedtype;
		logicaltype->outtypenfields = outtypenfields;
		logicaltype->outputfieldsbitsize = outputfieldsbitsize;
		
        if(strcmp(prVal, "none") != 0)
        {
            logicaltype->thereIsPredefinedValue = true;
            logicaltype->predefinedValue = Utility::convertToInteger(prVal);
        }
        else
        {
            logicaltype->predefinedValue = 0;
            logicaltype->thereIsPredefinedValue = false;
        }
    }
}


LogicalField::~LogicalField()
{
	
}

void LogicalField::getType(char* type, enum LogicalFieldDataType &outtype, int &outtypenfields, int &outputfieldsbitsize) {
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
