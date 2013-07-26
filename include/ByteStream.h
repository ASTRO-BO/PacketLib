/***************************************************************************
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
 
#ifndef _BYTESTREAM_H
#define _BYTESTREAM_H

#include "PacketLibDefinition.h"

namespace PacketLib
{


///	\brief Represent a stream of byte.
class ByteStream
{

public:


    /// The memory of byte* is not allocated
    /// \param bigendian The byte alignment
    ByteStream(bool bigendian = false);

    /// The memory of byte* is allocated
    ByteStream(dword size, bool bigendian);

    /// The memory of byte* is not allocated
    ByteStream(byte* stream, dword dim, bool bigendian, bool memory_sharing = true);

    /// Creates a new ByteStream that it is the sum of one or two or three ByteStream
    /// passed as input.
    /// It's possibile to pass 0 as pointer.
    /// The mamory of byte* is allocated.
    ByteStream(ByteStream* b0, ByteStream* b1, ByteStream* b2);

    ~ByteStream();

    byte* getStream();

    /// Returns a pointer of the stream for output purpose. If there is problems return NULL
    /// \remarks In little endian architecture it is necessary to call endOutputStream()
    /// after the use of the byte* stream in output operations.
    byte* getOutputStream();

    // This method must be called after the output operation.
    void endOutputStream();

    /// Returns a subset of the current stream. If there is problemas return NULL
    /// \remarks This method don't allocate a new stream structure in memory,
    /// but create only a new ByteStream object that points in the same memory area.
    ByteStream* getSubByteStream(dword first, dword last);

    /// Returns a subset of the current stream. If there is problemas return NULL
    /// \remarks This method allocate a new stream structure in memory.
    ByteStream* getSubByteStreamCopy(dword first, dword last);

    /// Sets the stream from arguments.
    bool setStream(byte* b, dword dim, bool bigendian, bool memory_sharing = true);

    /// Get the stream from another object of the same type. Don't allocate new memory
    bool setStream(ByteStream* b, dword first, dword last);

    /// Copy the stream in argument of dimension dim.
    /// \remarks This method delete old stream and creates a new stream in memory
    void setStreamCopy(byte* b, dword dim);

    /// Sets a word of the stream with the value of parameter.
    bool setWord(dword start, word value);

    /// Sets a byte of the stream with the value of parameter.
    void setByte(dword start, word value);

    /// This method return a byte of the stram in the position byteNumber
    byte getByte( dword byteNumber );

    /// Get the value in the stream starting from position start and of dim dimension
    /// \param start Start position in the stream of byte
    /// \param dim number of byte (1 oe 2)
    long getValue(dword start, word dim);

    /// Gets the dimension of the stream
    dword getDimension();

    char* printStreamInHexadecimal();

    /// Get type of allocations.
    /// \return True if this ByteStream contains the allocated memory area
    /// for the stream; false if this ByteStream haven't allocated the
    /// memory area but it's only a pointer of this area
    bool getMemAllocation();

    bool isBigendian() const;


    /// Swap of the stream if the architecture is little endian
    void swap();

    /// Pointer to the stream
    byte* stream;

    static dword count_object;

    static dword count_object2;

    static dword count_object_deleted;

    static dword count_object_deleted2;

protected:

    /// Internal use only for memory management
    void setMemoryAllocated(bool allocated);

    /// Internal use only for memory management
    void deleteStreamMemory();

private:


    /// This attribute specifes the number of byte in the stream
    dword byteInTheStream;

    /// Specifies if the stream is big or little endian
    bool bigendian;


    /// Indicates if there is memory allocated for stream. It could be indicate
    /// that the byte* stream memory area is shared between many ByteStream.
    /// In this case the memory must not be deallocated (when memory_sharing attribute is
    /// true).
    bool mem_allocation;

    bool mem_allocation_constructor;

};
}


#endif
