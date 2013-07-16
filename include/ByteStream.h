/***************************************************************************
                          ByteStream.h  -  description
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
#ifndef ByteStream_h_h_ZC2002
#define ByteStream_h_h_ZC2002

#include "PacketLibDefinition.h"

namespace PacketLib {

//##ModelId=3C0F6BDB0029
//##Documentation
//##	$Date: 2005/04/15 14:44:54 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/ByteStream.h,v 1.3 2005/04/15 14:44:54 bulgarelli Exp $
//##	$Id: ByteStream.h,v 1.3 2005/04/15 14:44:54 bulgarelli Exp $
//##	$Revision: 1.3 $
//##	\brief Represent a stream of byte.
class ByteStream
{

    public:

        //##ModelId=3C0F6BDB003B
        //##Documentation
        //## The memory of byte* is not allocated
        ByteStream(bool bigendian = false);

        //##ModelId=3EADC12501CA
        //##Documentation
        //## The memory of byte* is allocated
        ByteStream(long size, bool bigendian);

        //##ModelId=3EADC125023B
        //##Documentation
        //## The memory of byte* is not allocated
        ByteStream(byte* stream, long dim, bool bigendian, bool memory_sharing = true);

        //##ModelId=3EADC125031B
        //##Documentation
        //## Creates a new ByteStream that it is the sum of one or two or three ByteStream
        //## passed as input.
        //## It's possibile to pass 0 as pointer.
        //## The mamory of byte* is allocated.
        ByteStream(ByteStream* b0, ByteStream* b1, ByteStream* b2);

        //##ModelId=3C205AF201F8
        ~ByteStream();

        //##ModelId=3EADC12503D4
        byte* getStream();

        //##ModelId=3EADC1260005
        //##Documentation
        //## Returns a pointer of the stream for output purpose. If there is problems return NULL
        //## \remarks In little endian architecture it is necessary to call endOutputStream()
        //## after the use of the byte* stream in output operations.
        byte* getOutputStream();

        //##ModelId=3EADC126001E
        //##Documentation
        //## This method must be call after the output operation.
        void endOutputStream();

        //##ModelId=3C301E8800C7
        //##Documentation
        //## Returns a subset of the current stream. If there is problemas return NULL
        //## \remarks This method don't allocate a new stream structure in memory,
        //## but create only a new ByteStream object that points in the same memory area.
        ByteStream* getSubByteStream(word first, word last);

        //##ModelId=3EADC126003A
        //##Documentation
        //## Returns a subset of the current stream. If there is problemas return NULL
        //## \remarks This method allocate a new stream structure in memory.
        ByteStream* getSubByteStreamCopy(word first, word last);

        //##ModelId=3C87744001F6
        //##Documentation
        //## Sets the stream from arguments.
        bool setStream(byte* b, unsigned dim, bool bigendian, bool memory_sharing = true);

        //##ModelId=3EADC1260157
        //##Documentation
        //## Get the stream from another object of the same type. Don't allocate new memory
        bool setStream(ByteStream* b, word first, word last);

        //##ModelId=3EADC1260244
        //##Documentation
        //## Copy the stream in argument of dimension dim.
        //## \remarks This method delete old stream and creates a new stream in memory
        void setStreamCopy(byte* b, unsigned dim);

        //##ModelId=3EADC12602F1
        //##Documentation
        //## Sets a word of the stream with the value of parameter.
        bool setWord(unsigned start, word value);

        //##ModelId=3EADC12603A5
        //##Documentation
        //## Sets a byte of the stream with the value of parameter.
        void setByte(unsigned start, word value);

        //##ModelId=3C0F6BDB0041
        //##Documentation
        //## This method return a byte of the stram in the position byteNumber
        byte getByte( unsigned byteNumber );

        //##ModelId=3C18775001BB
        //##Documentation
        //## Get the value in the stream starting from position start and of dim dimension
        //## \param start Start position in the stream of byte
        //## \param dim number of byte (1 oe 2)
        long getValue(unsigned start, unsigned dim);

        //##ModelId=3C87744001D8
        //##Documentation
        //## Gets the dimension of the stream
        unsigned getDimension();

        //##ModelId=3C87744001EC
        char* printStreamInHexadecimal();

        //##ModelId=3EADC1270079
        //##Documentation
        //## Get type of allocations.
        //## \return True if this ByteStream contains the allocated memory area
        //## for the stream; false if this ByteStream haven't allocated the
        //## memory area but it's only a pointer of this area
        bool getMemAllocation();

        //##ModelId=3EADC127009D
        bool isBigendian() const;

        //##ModelId=3EADC12700E8
        //##Documentation
        //## Swap of the stream if the architecture is little endian
        void swap();

	//##ModelId=3DC5702E01D1
        //##Documentation
        //## Pointer of the stream
        byte* stream;

	//##ModelId=3EADC125005E
        static dword count_object;

	//##ModelId=3EADC12500B7
        static dword count_object2;

        //##ModelId=3EADC12500CF
        static dword count_object_deleted;

        //##ModelId=3EADC12500F6
        static dword count_object_deleted2;

    protected:

        //##ModelId=3EADC127010D
        //##Documentation
        //## Internal use only for memory management
        void setMemoryAllocated(bool allocated);

        //##ModelId=3EADC12701A5
        //##Documentation
        //## Internal use only for memory management
        void deleteStreamMemory();

    private:

	//##ModelId=3EADC1250121
        //##Documentation
        //## This attribute specifes the number of byte in the stream
        word byteInTheStream;

        //##ModelId=3C877440014B
        //##Documentation
        //## Specifies if the stream is big or little endian
        bool bigendian;

        //##ModelId=3EADC125013B
        //##Documentation
        //## Indicates if there is memory allocated for stream. It could be indicate
        //## that the byte* stream memory area is shared between many ByteStream.
        //## In this case the memory must not be deallocated (when memory_sharing attribute is
        //## true).
        bool mem_allocation;

        //##ModelId=3EADC1250171
        bool mem_allocation_constructor;

};
}


#endif
