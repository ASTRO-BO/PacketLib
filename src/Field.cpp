/**
 * @(#) Field.cpp
 */

#include "Field.h"
#include "Utility.h"

using namespace PacketLib;



//##ModelId=3C0F6C1A0001
Field::Field(char* n, char* dim, char* prVal, int count) : progressiv(count)
{
    #ifndef NOFIELDSNAME
    //cout << "define field name" << endl;
    //name
    dword l = strlen(n);
    l++;
    name = (char*)malloc(sizeof(char)*l);
    memcpy(name, n, l);
    #endif

    dimension = atoi(dim);
    if(strcmp(prVal, "none") != 0)
    {
        thereIsPredefinedValue = true;
        predefinedValue = Utility::convertToInteger(prVal);
    }
    else
    {
        predefinedValue = 0;
        thereIsPredefinedValue = false;
    }
}


//##ModelId=3ACCD75E036B
Field::~Field()
{
    //	cout << "deleted field: " << name << endl;
    #ifndef NOFIELDSNAME
    free(name);
    #endif
}
