/***************************************************************************
                          PacktException.h  -  description
                             -------------------
    begin                : Tue Jan 15 2002
    copyright            : (C) 2002, 2013 by Andrea Bulgarelli
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

#ifndef _PACKTEXCEPTION_H
#define _PACKTEXCEPTION_H
#include "PacketLibDefinition.h"

namespace PacketLib
{

///	\brief Exception class of the PacketLib
class PacketException
{
public:

    PacketException(const char* error, int code = 0);

    virtual ~PacketException();

    virtual const char* geterror();

    void add(const char* error);

    int geterrorcode() const;


    void seterrorcode(int errorcode);

protected:

    string* error;

    int errorcode;

};
}


#endif



