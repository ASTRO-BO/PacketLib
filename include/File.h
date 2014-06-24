/***************************************************************************
                          File.h 
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
#ifndef _FILE_H_H
#define _FILE_H_H

#include "PacketLibDefinition.h"
#include "Device.h"
#include "PacketExceptionIO.h"
#include "ByteStream.h"

namespace PacketLib
{

///	\brief This class represent a device file for IO system.
class File : public Device
{
public:

    File();

    ///  \param b Indicates if the machine is big or little endian. If little endian, this class
    ///  swap the byte of a word
    ///  \param startP Starting position whitin file
    File(bool b, long startP = 0);

    virtual ~File();

    ///  Open the file
    ///  \param filename Name of file
    ///  \param mode Mode of file opened. r for read, w for writing
    virtual bool open( const char* filename, const char* mode="r") throw(PacketExceptionIO*);

    virtual void setFileName(char* filename )
    {
        this->filename = filename;
    };

    virtual char* getFileName()
    {
        return filename;
    };

    ///  Get a single byte from current position of file opened.
    ///  \pre The file must be opened.
    virtual int getByte();

    ///  Reads a pair number of byte from opened file and manages the big or little endian
    ///  format. If the format of machine is little endian, a pair of byte is swapped.
    ///  \pre The file must be opened.
    virtual ByteStreamPtr getNByte( dword N = 1 );

    ///  Get the current line.
    ///  \pre The file must be opened.
    virtual char* getLine() throw(PacketExceptionIO*);

    ///  Close the file.
    virtual void close( ) throw(PacketExceptionIO*);

    ///  \return true if file is closed, false if file is opened.
    virtual bool isClosed() const;

    ///  \return Returns last line read from file.
    char* getLastLineRead();

    ///  Sets the position into file.
    ///  \pre The file must be opened.
    virtual long setpos(long offset) throw(PacketExceptionIO*);

    ///  Gets the current file position.
    ///  \pre The file must be opened.
    virtual long getpos();

    ///  Stores the current position
    ///  \pre The file must be opened.
    virtual bool memBookmarkPos();

    ///  Sets the position stored with memBookmarkPos() method.
    ///  \pre The file must be opened.
    virtual bool setLastBookmarkPos();

    ///  \return Returns true is the position into file is at end of file
    virtual bool isEOF() const;

    ///  \pre The file must be opened.
    long setFirstPos() throw(PacketExceptionIO*);

    ///  Changes directory. The path is in the filename of file opened.
    ///  \pre The file name must be set.
    bool fchdir() throw(PacketExceptionIO*);

    long find(byte b) throw(PacketExceptionIO*) ;

    ///  Writes a string into opend file.
    ///  \pre The file must be opened in w mode
    bool writeString(const char* str) throw(PacketExceptionIO*);

    ///  Writes a stream of byte into opend file.
    ///  \pre The file must be opened in w mode
    bool writeByteStream(ByteStreamPtr b) throw(PacketExceptionIO*);

    ///  Count the number of string lines into a text file.
    long getNumberOfStringLines();
    
    ///  The dimension of the file
    long fsize();

    static dword byte_read;

    static dword char_read;

protected:

    char* lastLineRead;

    FILE* fp;

    long bookmarkPos;

    long startPosition;

    char* filename;

    char* mode;
};
}
#endif
