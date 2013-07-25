/***************************************************************************
                          file.cpp  -  description
                             -------------------
    begin                : Tue Nov 20 2001
    copyright            : (C) 2001 by Andrea Bulgarelli
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

#include "File.h"
#include "PacketLibDefinition.h"
#include <unistd.h>
#include "Utility.h"
#include "PacketLibDemo.h"

using namespace PacketLib;

//##ModelId=3DA3E56900F0
dword File::byte_read = 0;
//##ModelId=3DA3E56A0078
dword File::char_read = 0;

//##ModelId=3C0F6C1A0012
File::File() : Device(false)
{
    //	bigendian = false; //si presume che la macchina sia little endian
    startPosition = 0;
    filename = 0;
    bookmarkPos =0;
    lastLineRead = 0;
}


//##ModelId=3C187750028F
File::File(bool b, long startP) : Device(b)
{
    //bigendian = b;   //si specifica il formato endian della macchina
    startPosition = startP;
    filename = 0;
    bookmarkPos =0;
    lastLineRead = 0;
}

File::~File() {
	//delete[] lastLineRead;
	//delete[] filename;
	//delete[] mode;
}

//##ModelId=3C0F6C1A0013
bool File::open(const char* filename, const char* mode) throw(PacketExceptionIO*)
{
    DEMORET0;
	
    fp = fopen(filename, mode);

    if(fp == NULL)
    {
        closed = true;
        eof = true;
        this->filename = 0;
		this->mode = 0;
        //throw new PacketExceptionIO("File not opened. [File::open()]");
        throw new PacketExceptionIO(strerror(errno));

    }
    else
    {
        closed = false;
        eof = false;
        setFirstPos();
        this->filename = (char*)filename;
		this->mode = (char*)mode;
    };
    return !closed;
}


//##ModelId=3C0F6C1A0016
int File::getByte()
{
    int c;
    if(!closed && !eof)
    {
        c = fgetc(fp);
        if(c == EOF)
        {
            eof = true;
            //close();
            c = EOI;
        }
        File::byte_read++;
        return c;
    }
    else
    {
        return EOI;
    }
}


//##ModelId=3C0F6C1A0018
ByteStream* File::getNByte(dword N)
{
    dword i = 0;
    int c1, c2;
    if(N == 0)
        return new ByteStream(0, bigendian);
    //solo un numero pari di byte
    //if(N%2 != 0 || !fileOpened) return NULL;

    if(closed) return NULL;

    //ByteStream* b = new ByteStream(N, bigendian);
    byte* stream = (byte*) new byte[N];

    for(i = 0; i<N && (c1 = getByte()) != EOI && (c2 = getByte()) != EOI; i+=2)
    {
        //File::byte_read += 2;
        stream[i] = c1;
        stream[i+1] = c2;
        /*        if(bigendian)
                {
                    //se la  macchina e' bigendian, non e' necessario effettuare scambi di byte
                    b->stream[i] = c1;
                    b->stream[i+1] = c2;
                }
                else                     //little endian
                {
                    //se la macchina lavora in little endian, per "far tornare i conti" e' necessario
                    //invertire i byte letti
                    b->stream[i] = c2;
                    b->stream[i+1] = c1;
                }*/
    }
    /*if(i != N)
    {
        ByteStream* b1 = new ByteStream(i, bigendian);
        for(int j = 0; j<i; j++)
            b1->stream[j] = b->stream[j];
        delete b;
        b = b1;
    } */
    //for(; i<N; i++)
    //	b->stream[i] = 0;
    //return b;
    return new ByteStream(stream, i, bigendian, false);
}


//##ModelId=3C0F6C1A001B
char* File::getLine() throw(PacketExceptionIO*)
{
    //char* s = new char[500];
    static char s[2048];
    //	static unsigned long dimalloc = 0;
    char c;
    dword i = 0;

    if(!closed)
    {
        c=fgetc(fp);
        File::char_read++;
        while( c != '\n' && c != EOF )
        {
            s[i] = c;
            //printf("%c", c);
            i++;
            if(i>=2048)
                throw new PacketExceptionIO("Error: it's impossible to read a line with more of 2048 bytes.");
            c=fgetc(fp);
            File::char_read++;
        }
        if(c == EOF)
        {
            eof = true;
            //close();
        }
    }
    s[i] = '\0';
    unsigned dims = strlen(s);
    char* sr = new char[ dims + 1];
    for(unsigned i=0; i<=dims; i++)
        sr[i] = s[i];

    delete[] lastLineRead; 
    lastLineRead = new char[ dims + 1];
    for(unsigned i=0; i<=dims; i++)
        lastLineRead[i] = s[i];  
    
    return sr;
}


long File::getNumberOfStringLines() {
long nlines = 0;
	memBookmarkPos();
	setpos(0);
	while(!isEOF()) {
		char* line = getLine();
		nlines++;
		delete[] line;
	}	
	setLastBookmarkPos();
	setpos(0);
	return nlines;
}

//##ModelId=3C0F6C1A001F
void File::close( )  throw(PacketExceptionIO*)
{
    if(!closed)
    {
        fclose(fp);
        closed = true;
        eof = true;
    }
}


//##ModelId=3C0F6C1A0021
bool File::isClosed()
{
    return closed;
}


//##ModelId=3C15F42303C4
char* File::getLastLineRead()
{
    return lastLineRead;
}


//##ModelId=3C205AF20278
dword File::setpos(dword offset)  throw(PacketExceptionIO*)
{
    dword f;
    //clearerr(fp);
    f =  fseek(fp, offset, 0);
    if(feof(fp))
        eof=true;
    else
        eof=false;
    return f;
}


//##ModelId=3C205AF202C3
dword File::getpos()
{
    return ftell(fp);
}


//##ModelId=3C205AF20313
bool File::memBookmarkPos()
{
    if((bookmarkPos =  ftell(fp)) != (dword) -1)
        return true;
    else
        return false;
}


//##ModelId=3C205AF20334
bool File::setLastBookmarkPos()
{
    if(fseek(fp, bookmarkPos, SEEK_SET) == 0)
        return true;
    else
        return false;
}


//##ModelId=3A5A30B40368
bool File::isEOF()
{
    if(!closed)
        return eof;
    else
        return true;
}


//##ModelId=3C51324A022E
int File::setFirstPos()  throw(PacketExceptionIO*)
{
    return setpos(startPosition);
}


//##ModelId=3C51324A0299
bool File::fchdir() throw(PacketExceptionIO*)
{
	
    char* path = Utility::extractPath(filename);
    if(strlen(path) != 0) {
    	if(chdir(path)==0) {
    		delete[] path;
        	return true;
    	}
    	else {
    		delete[] path;
        	throw new PacketExceptionIO("Error: can't change directory.");
    	}
    }
    delete[] path;
    return true;
}


/** No descriptions */
//##ModelId=3C51324A0304
long File::find(byte b)   throw(PacketExceptionIO*)
{
    byte f;
    while(!isEOF())
    {
        f = (byte) getByte();
        if(f == b)
            return getpos();
    }
    return -1;
}


//##ModelId=3DA3E56D0244
bool File::writeString(const char* str) throw(PacketExceptionIO*)
{
    if(str != 0)
        if(!closed)
            if(fprintf(fp,"%s",str)<0)
                throw new PacketExceptionIO("Can't write the file.");
    return true;
}


//##ModelId=3DA3E56F00DC
bool File::writeByteStream(ByteStream* b) throw(PacketExceptionIO*)
{
    byte* stream = b->getOutputStream();
    if(fwrite((void*)stream, b->getDimension(), 1, fp)<1)
        throw new PacketExceptionIO("Can't write stream in the file.");
    b->endOutputStream();
    return true;

}
