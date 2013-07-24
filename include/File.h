/***************************************************************************
                          File.h  -  description
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001 by Andrea Bulgarelli
    email                : bulgarelli@bo.iasf.cnr.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *             
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/
#ifndef file_h_h
#define file_h_h

#include "PacketLibDefinition.h"
#include "Device.h"
#include "PacketExceptionIO.h"
#include "ByteStream.h"

namespace PacketLib {

//##ModelId=3C0F6C190309
//##Documentation
//##	$Date: 2012/06/08 15:14:29 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/File.h,v 1.6 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Id: File.h,v 1.6 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Revision: 1.6 $
//##	\brief This class represent a device file for IO system.
class File : public Device
{
    public:

        //##ModelId=3C0F6C1A0012
        File();

        //##ModelId=3C187750028F
        //##Documentation
        //## \param b Indicates if the machine is big or little endian. If little endian, this class
        //## swap the byte of a word
        //## \param startP Starting position whitin file
        File(bool b, long startP = 0);
	
        virtual ~File();

        //##ModelId=3C0F6C1A0013
        //##Documentation
        //## Open the file
        //## \param filename Name of file
        //## \param mode Mode of file opened. r for read, w for writing
        virtual bool open( const char* filename, const char* mode="r") throw(PacketExceptionIO*);

		virtual void setFileName(char* filename ) { this->filename = filename; };
		
        virtual char* getFileName() { return filename;};

        //##ModelId=3C0F6C1A0016
        //## Documentation
        //## Get a single byte from current position of file opened.
        //## \pre The file must be opened.
        virtual int getByte();

        //##ModelId=3C0F6C1A0018
        //##Documentation
        //## Reads a pair number of byte from opened file and manages the big or little endian
        //## format. If the format of machine is little endian, a pair of byte is swapped.
        //## \pre The file must be opened.
        virtual ByteStream* getNByte( int N = 1 );

        //##ModelId=3C0F6C1A001B
        //##Documentation
        //## Get the current line.
        //## \pre The file must be opened.
        virtual char* getLine() throw(PacketExceptionIO*);

        //##ModelId=3C0F6C1A001F
        //##Documentation

        //## Close the file.
        virtual void close( ) throw(PacketExceptionIO*);

        //##ModelId=3C0F6C1A0021
        //##Documentation
        //## \return true if file is closed, false if file is opened.
        virtual bool isClosed();

        //##ModelId=3C15F42303C4
        //##Documentation
        //## \return Returns last line read from file.
        char* getLastLineRead();

        //##ModelId=3C205AF20278
        //## Sets the position into file.
        //## \pre The file must be opened.
        virtual long setpos(long offset) throw(PacketExceptionIO*);

        //##ModelId=3C205AF202C3
        //## Gets the current file position.
        //## \pre The file must be opened.
        virtual long getpos();

        //##ModelId=3C205AF20313
        //##Documentation
        //## Stores the current position
        //## \pre The file must be opened.
        virtual bool memBookmarkPos();

        //##ModelId=3C205AF20334
        //##Documentation
        //## Sets the position stored with memBookmarkPos() method.
        //## \pre The file must be opened.
        virtual bool setLastBookmarkPos();

        //##ModelId=3A5A30B40368
        //##Documentation
        //## \return Returns true is the position into file is at end of file
        virtual bool isEOF();

        //##ModelId=3C51324A022E
        //## \pre The file must be opened.
        int setFirstPos() throw(PacketExceptionIO*);

        //##ModelId=3C51324A0299
        //## Changes directory. The path is in the filename of file opened.
        //## \pre The file name must be setted.
        bool fchdir() throw(PacketExceptionIO*);

        //##ModelId=3C51324A0304
        long find(byte b) throw(PacketExceptionIO*) ;

        //##ModelId=3EADC12800D8
        //##Documentation
        //## Writes a string into opend file.
        //## \pre The file must be opened in w mode
        bool writeString(const char* str) throw(PacketExceptionIO*);

        //##ModelId=3EADC12801EA
        //##Documentation
        //## Writes a stream of byte into opend file.
        //## \pre The file must be opened in w mode
        bool writeByteStream(ByteStream* b) throw(PacketExceptionIO*);
	
	//##Documentation
	//## Count the number of string lines into a text file.
	long getNumberOfStringLines();

        //##ModelId=3EADC12702C9
        static unsigned long byte_read;

        //##ModelId=3EADC1270363
        static unsigned long char_read;

    protected:

        //##ModelId=3ACCD75E038A
        char* lastLineRead;

        //##ModelId=3DA3E56B0064
        FILE* fp;

        //##ModelId=3C187750023E
        long bookmarkPos;

        //##ModelId=3C51324900FB
        long startPosition;

        //##ModelId=3C5132490213
        char* filename;
	
	char* mode;
};
}
#endif
