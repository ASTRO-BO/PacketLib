/***************************************************************************
                          ByteStream.h  
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001-2013 by Andrea Bulgarelli
                               2013-2014 by Andrea Bulgarelli, Andrea Zoli
    email                : bulgarelli@iasfbo.inaf.it, zoli@iasfbo.inaf.it
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
#include "SharedPtr.h"

namespace PacketLib
{

class ByteStream;
typedef SharedPtr<ByteStream> ByteStreamPtr;

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
    ByteStream(ByteStreamPtr b0, ByteStreamPtr b1, ByteStreamPtr b2);
	
	/// Creates a new ByteStream from start to end
	/// If end=-1 use the end of the b0
    ByteStream(ByteStreamPtr b0, dword start, dword end=-1, bool memory_sharing=true);

    ~ByteStream();

    byte* getStream();
	
	ByteStreamPtr compress(enum CompressionAlgorithms algorithmType, byte compressionLevel);
	
	ByteStreamPtr decompress(enum CompressionAlgorithms algorithmType, byte compressionLevel, dword dmax);

    /// Returns a pointer of the stream for output purpose. If there is problems return NULL
    /// \remarks In little endian architecture it is necessary to call endOutputStream()
    /// after the use of the byte* stream in output operations.
    byte* encode();

    // This method must be called after the output operation.
    void endOutputStream();

    /// Returns a subset of the current stream. If there is problemas return NULL
    /// \remarks This method don't allocate a new stream structure in memory,
    /// but create only a new ByteStream object that points in the same memory area.
    ByteStreamPtr getSubByteStream(dword first, dword last);

    /// Returns a subset of the current stream. If there is problemas return NULL
    /// \remarks This method allocate a new stream structure in memory.
    ByteStreamPtr getSubByteStreamCopy(dword first, dword last);

    /// Sets the stream from arguments.
    bool setStream(byte* b, dword dim, bool bigendian, bool memory_sharing = true);

    /// Get the stream from another object of the same type. Don't allocate new memory
    bool setStream(ByteStreamPtr b, dword first, dword last);

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
    /// \param dim number of byte (1 or 2)
    long getValue(dword start, word dim);

    /// Gets the dimension of the stream
    dword size();

	/// Create a copy of the stream with some additional padding. The stream is divided into chunks
	/// with numberOfChunks = size() / chunkSize.
	/// \param chunkSize the size of a chunk without padding.
	/// \param padSize Size of the padding.
	/// \return The padded copy of this byte stream.
	ByteStreamPtr getPaddedCopy(dword chunkSize, dword padSize);

	/// Create a copy of the stream removing some padding. The stream is divided into chunks
	/// with numberOfChunks = size() / chunkSize.
	/// \param chunkSize the size of a chunk with padding.
	/// \param padSize Size of the padding.
	/// \return The unpadded copy of this byte stream.
	ByteStreamPtr getUnpaddedCopy(dword chunkSize, dword padSize);

    char* printStreamInHexadecimal();

    /// Get type of allocations.
    /// \return True if this ByteStream contains the allocated memory area
    /// for the stream; false if this ByteStream haven't allocated the
    /// memory area but it's only a pointer of this area
    bool getMemAllocation();

    bool isBigendian() const;


    /// Swap the stream if it is little endian (for big endian architectures, e.g. Motorola)
    void swapWordIfStreamIsLittleEndian();

    /// Swap the stream if it is big endian (for little endian architectures, e.g. Intel)
    void swapWordIfStreamIsBigEndian();

    /// Swap the stream Intel architectures
    void swapWordForIntel();


    /// Swap  the stream of words
    void swapWord();

    /// Pointer to the stream
    byte* stream;

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
