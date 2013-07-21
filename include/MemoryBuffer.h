/***************************************************************************
                          MemoryBuffer.h  -  description
                             -------------------
    begin                : Fri Apr 12 2002
    copyright            : (C) 2002 by Andrea Bulgarelli
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

#ifndef MEMORYBUFFER_H
#define MEMORYBUFFER_H
#include "PacketLibDefinition.h"
#include "PacketExceptionIO.h"

namespace PacketLib {

//##ModelId=3EADC1230064
//##Documentation
//##	$Date: 2005/05/09 12:24:29 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/MemoryBuffer.h,v 1.3 2005/05/09 12:24:29 bulgarelli Exp $
//##	$Id: MemoryBuffer.h,v 1.3 2005/05/09 12:24:29 bulgarelli Exp $
//##	$Revision: 1.3 $
//##	\brief Class that represent an FIFO structure of char*
class MemoryBuffer
{
    public:
        //##ModelId=3EADC12A00B6
        MemoryBuffer();

        //##ModelId=3EADC12A00B7
        ~MemoryBuffer();

        //##ModelId=3EADC12A00B8
        //##Documentation
        //## Write property of char** buffer.
        void setbuffer( char* _newVal);

        //##ModelId=3EADC12A00BF
        void setbuffer( char* _newVal, dword index);

        //##ModelId=3EADC12A00CB
        //##Documentation
        //## Read property of char** buffer.
        char* getbuffer();
        
        char* getlastbuffer();

        //##ModelId=3EADC12A00CD
        char* getbuffer(dword index);

        //##ModelId=3EADC12A00D3
        void readRewind();

        //##ModelId=3EADC12A00D5
        void writeRewind();

        //##ModelId=3EADC12A00D6
        dword getBufferDimension();

        //##ModelId=3EADC12A00D8
        bool loadBuffer(char* filename) throw(PacketExceptionIO*);

        //##ModelId=3EADC12A00DF
        bool saveBuffer(char* filename) throw(PacketExceptionIO*);
	
		void freebuffer();
		
		void setName(char* name);
		
		char* getName() { return bufferName; };
		
		int getpos();
		
		bool memBookmarkPos();
		
		bool setLastBookmarkPos();
		
		long setpos(int index);

    private:
    
    	int bookmarkpos;
    
        dword dim;

        //##ModelId=3EADC12A0091
        char** buffer;

        dword indexwrite;

        dword indexread;

        //##ModelId=3EADC12A00AF
        char* currentpwd;
        
        // The name of the buffer
        char* bufferName;
};

}
#endif
