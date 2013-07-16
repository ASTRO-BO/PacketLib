/***************************************************************************
                          InputTextFile.cpp  -  description
                             -------------------
    begin                : Mon Mar 4 2002
    copyright            : (C) 2002 by Andrea Bulgarelli
    email                : bulgarelli@tesre.bo.cnr.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "InputTextFile.h"

using namespace PacketLib;

//##ModelId=3AA64922006A
InputTextFile::InputTextFile() : InputText()
{

}


//##ModelId=3AA64922007E
InputTextFile::~InputTextFile()
{

}


//##ModelId=3DA3E57A02F8
bool InputTextFile::fchdir() throw(PacketExceptionIO*)
{
    try
    {
        return file.fchdir();
    }
    catch(PacketExceptionIO* e)
    {
        e->add("InputTextFile::fchdir() -- ");
        throw e;
    }
}


//##ModelId=3AA64922009C
bool InputTextFile::open(char** parameters) throw(PacketExceptionIO*)
{
    try
    {
        bool ret;
        ret =  file.open(parameters[0]);
        eof = file.isEOF();
        closed = file.isClosed();
        return ret;
    }
    catch(PacketExceptionIO* e)
    {
        throw e;
    }
};

//##ModelId=3AA6492200F6
void InputTextFile::close()  throw(PacketExceptionIO*)
{
    file.close();
    eof = file.isEOF();
    closed = file.isClosed();
};

//##ModelId=3AA64922011E
char* InputTextFile::getLine() throw(PacketExceptionIO*)
{
    try
    {
        char* ret =  file.getLine();
        eof = file.isEOF();
        closed = file.isClosed();
        return ret;
    }
    catch(PacketExceptionIO* e)
    {
        throw e;
    }
}


//##ModelId=3AA64922013C
char* InputTextFile::getLine(const char* s) throw(PacketExceptionIO*)
{
    char* line;
    line = file.getLine();

    while(strstr(line, s) == NULL) {
		delete line; line = 0;
        line = file.getLine();
		if(file.isEOF() == true)
			break;
	}
    eof = file.isEOF();
    closed = file.isClosed();
    return line;
}


//##ModelId=3AA649220196
char* InputTextFile::getLastLineRead()
{
    return file.getLastLineRead();
}


//##ModelId=3AA6492201BE
long InputTextFile::getpos()
{
    return file.getpos();
}


//##ModelId=3AA6492201DC
bool InputTextFile::memBookmarkPos()
{
    return file.memBookmarkPos();
}


//##ModelId=3AA64922020E
int InputTextFile::setFirstPos()
{
    return file.setFirstPos();
}


//##ModelId=3AA64922022C
bool InputTextFile::setLastBookmarkPos()
{
    return file.setLastBookmarkPos();
}


//##ModelId=3AA64922025E
long InputTextFile::setpos(long offset) throw(PacketExceptionIO*)
{
    long l =  file.setpos(offset);
    eof = file.isEOF();
    closed = file.isClosed();
    return l;
}
