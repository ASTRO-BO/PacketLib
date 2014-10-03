/***************************************************************************
                          ByteStream.cpp  -  description
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001-2013 by Andrea Bulgarelli
                               2013-2914 by Andrea Bulgarelli, Andrea Zoli
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


#include "ByteStream.h"
#include "PacketLibDemo.h"
#include "PacketException.h"
#include "Utility.h"
#include "lz4.h"
#include "lz4hc.h"
using namespace PacketLib;

/// Returns a pointer of a field in the list of fields of this part of packet.
/// \remarks mem_allocation = true indicates that the allocated memory must be released by the destroyer.
/// \remarks memory_sharing=false In all methods of constructor or set type accepting byte*, it indicates that the swap is applied. 
/// In all methods of constructor or set type accepting ByteStreamPtr the swap is never applied.

PacketLib::ByteStream::ByteStream(bool bigendian)
	: stream(0), byteInTheStream(0), bigendian(bigendian)
{
    mem_allocation_constructor = true;
    setMemoryAllocated(false);
    mem_allocation_constructor = false;
}


PacketLib::ByteStream::ByteStream(dword dim, bool bigendian)
	: byteInTheStream(dim), bigendian(bigendian)
{
    mem_allocation_constructor = true;
    stream = (byte*) new byte[dim];
    setMemoryAllocated(true);
    mem_allocation_constructor = false;
}


PacketLib::ByteStream::ByteStream(byte* stream, dword dim, bool bigendian, bool memory_sharing)
	: stream(stream), byteInTheStream(dim), bigendian(bigendian)
{
    mem_allocation_constructor = true;
    //if(!memory_sharing)
    //    swapWordIfStreamIsLittleEndian();
    /// \remarks memory_sharing == false means that the object is responsible for the memory
    setMemoryAllocated(!memory_sharing);
    mem_allocation_constructor = false;
}

PacketLib::ByteStream::ByteStream(ByteStreamPtr b0, dword start, dword end, bool memory_sharing) {
	mem_allocation_constructor = true;
	
	if(end == (dword)-1)
		end = b0->size();
	
	byteInTheStream = end-start;
    this->stream = b0->stream+start;
    this->bigendian = b0->isBigendian();
    //if(!memory_sharing)
    //    swapWordIfStreamIsLittleEndian();
	
	setMemoryAllocated(!memory_sharing);
	mem_allocation_constructor = false;
}


PacketLib::ByteStream::ByteStream(ByteStreamPtr b0, ByteStreamPtr b1, ByteStreamPtr b2)
{
    mem_allocation_constructor = true;

    /// Streams are swapped
    dword dim = 0;
    if(b0 == 0 && b1 == 0 && b2 == 0)
    {

        setMemoryAllocated(false);

        byteInTheStream  = 0;
        stream = 0;
        mem_allocation_constructor = false;
        return;
    }
    byteInTheStream = (b0!=0?b0->size():0) + (b1!=0?b1->size():0) + (b2!=0?b2->size():0);
    stream = (byte*) new byte[byteInTheStream];
    this->bigendian = (b0!=0?b0->isBigendian():(b1!=0?b1->isBigendian():(b2!=0?b2->isBigendian():false)));

	if(b0 != 0)
	{
		memcpy(stream, b0->stream, b0->size());
		dim += b0->size();
	}
	if(b1 != 0)
	{
		memcpy(stream+dim, b1->stream, b1->size());
		dim += b1->size();
	}
	if(b2 != 0)
	{
		memcpy(stream+dim, b2->stream, b2->size());
		dim += b2->size();
	}
    setMemoryAllocated(true);
    mem_allocation_constructor = false;
}



PacketLib::ByteStream::~ByteStream()
{
    if(mem_allocation)
    {
        delete[] stream;
        stream = 0;
    }
}

ByteStreamPtr PacketLib::ByteStream::compress(enum CompressionAlgorithms algorithmType, byte compressionLevel) {
	ByteStreamPtr b;

	switch(algorithmType)
	{
		case LZ4:
		{
			byte* buff = new byte[LZ4_compressBound(size())];
			int buffsize = LZ4_compressHC2((const char*)stream, (char*)buff, size(), compressionLevel);
			if(!buffsize)
			{
				cout << "LZ4 compression error" << endl;
				return 0;
			}
			b = ByteStreamPtr(new ByteStream((byte*)buff, buffsize, bigendian));
			break;
		}
		case NONE:
		{
			b = ByteStreamPtr(new ByteStream(stream, size(), bigendian));
			break;
		}
		default:
		{
			return 0;
		}
	}
#ifdef DEBUG
	cout << "Buffer decompressed size: " << size() << endl;
	cout << "Buffer compressed size: " << b->size() << endl;
#endif
	return b;
}

ByteStreamPtr PacketLib::ByteStream::decompress(enum CompressionAlgorithms algorithmType, byte compressionLevel, dword dmax) {
	ByteStreamPtr b;

	switch(algorithmType)
	{
		case NONE:
		{
			b = stream;
			break;
		}
		case LZ4:
		{
			byte* tmpbuff = new byte[dmax];
			int buffsize = LZ4_decompress_safe((const char*)stream, (char*)tmpbuff, size(), dmax);
			if(!buffsize)
			{
				delete tmpbuff;
				throw new PacketException("LZ4 decompression error");
				return 0;
			}
			if(buffsize < 0) {
				delete tmpbuff;
				throw new PacketException("LZ4 decompression error: the source stream is malformed");
			}
			byte* decompbuff = new byte[buffsize];
			memcpy(decompbuff, tmpbuff, buffsize);
			b = ByteStreamPtr(new ByteStream(decompbuff, buffsize, bigendian));
			delete tmpbuff;
			break;
		}
		default:
		{
			return 0;
		}
	}

#ifdef DEBUG
	cout << "dmax: " << dmax << endl;
	cout << "Buffer compressed size: " << size() << endl;
	cout << "Buffer decompressed size: " << b->size() << endl;
#endif

	return b;
}


byte PacketLib::ByteStream::getByte( dword byteNumber)
{
    DEMORET0;
    if(byteNumber <= byteInTheStream)
        return stream[byteNumber];
    else
        return 0;
}


long PacketLib::ByteStream::getValue(dword start, word dim)
{
    DEMORET0;
    byte b1, b2;
	
	if(start >= byteInTheStream)
		throw PacketException("PacketLib::ByteStream::getValue() start greater than the size of the ByteStream", 0);
	
    /// only 1 or 2 bytes
    if(dim == 0 || dim > 2)
    	/// error
        return -1;               
    if(bigendian)
    {
        b1 = stream[start];
        if(dim==2)
            b2 = stream[start+1];
        else
            b2 = 0;
    }
    else
    {
        if(dim==1)
        {
            if((start%2) == 0)
                b2 = stream[start+1];
            else
                b2 = stream[start-1];
            b1 = 0;
        }
        if(dim==2)
        {
            if((start%2) == 0)
            {
                /// even value
                b1=stream[start+1];
                b2=stream[start];
            }
            else
            {
                //b1 = (start-1)<0?0:stream[start-1];
                //b2 = (start+2)>byteInTheStream?0:stream[start+2];
				b1=(start+1)>=byteInTheStream?0:stream[start+1];
                b2=stream[start];
            }
        }
    }
    return b2 + b1*256;
}



ByteStreamPtr PacketLib::ByteStream::getSubByteStream(dword first, dword last)
{
    DEMORET0;
    if(first > last)
        return NULL;
    if(last > byteInTheStream)
        return NULL;
    ByteStreamPtr b = ByteStreamPtr(new ByteStream((stream + first), last-first+1, bigendian, true));
    return b;
}



ByteStreamPtr PacketLib::ByteStream::getSubByteStreamCopy(dword first, dword last)
{
    DEMORET0;
    if(first > last)
        return NULL;
    if(last > byteInTheStream)
        return NULL;
    byte* streamtemp = (byte*) new byte[last-first+1];
    for(dword i=0; i<last-first+1; i++)
        streamtemp[i] = stream[first+i];
    return ByteStreamPtr(new ByteStream(streamtemp, last-first+1, bigendian, false));
}


byte* PacketLib::ByteStream::getStream()
{
    return stream;
}



byte* PacketLib::ByteStream::encode()
{
    //swapWordIfStreamIsLittleEndian();
    return stream;
}



void PacketLib::ByteStream::endOutputStream()
{
    //swapWordIfStreamIsLittleEndian();
}


dword PacketLib::ByteStream::size()
{
    return byteInTheStream;
}


char* PacketLib::ByteStream::printStreamInHexadecimal()
{
    return Utility::stringToHexadecimal(stream, byteInTheStream);
}



void PacketLib::ByteStream::setStreamCopy(byte* b, dword dim)
{
    deleteStreamMemory();

    byteInTheStream = dim;
    stream = (byte*) new byte[dim];
    for(dword i=0; i<dim; i++)
        stream[i] = b[i];
    //swapWordIfStreamIsLittleEndian();
    setMemoryAllocated(true);
}



bool PacketLib::ByteStream::setStream(byte* b, dword dim, bool bigendian, bool memory_sharing)
{
    deleteStreamMemory();

    byteInTheStream = dim;
    this->bigendian = bigendian;
    this->stream = b;

    //if(!memory_sharing) swapWordIfStreamIsLittleEndian();
    setMemoryAllocated(!memory_sharing);
    return true;
}



bool PacketLib::ByteStream::setStream(ByteStreamPtr b, dword first, dword last)
{
    if(first > last)
        return false;
    if(last > b->size())
        return false;

    deleteStreamMemory();

    this->stream = (b->stream + first);
    this->byteInTheStream = last-first+1;
    this->bigendian = b->isBigendian();

    setMemoryAllocated(false);

    return true;
}



bool PacketLib::ByteStream::getMemAllocation()
{
    return mem_allocation;
}


bool PacketLib::ByteStream::isBigendian() const
{
    return bigendian;
}



void PacketLib::ByteStream::setByte(dword start, word value)
{
    stream[start] = value;
}

word PacketLib::ByteStream::getWord(dword posword)
{
	word wordtemp;
	/// Temporary word to be modified for the elaboration
	byte bf = *(stream + posword);
	byte bl = *(stream + posword + 1);
	//word wordtemp = *(stream + posword);
	
	if(!ARCH_BIGENDIAN && !bigendian )
	{
		//swap OK

		wordtemp = bf * 256 + bl;
		return wordtemp;
	}
	if(ARCH_BIGENDIAN && bigendian )
	{
		//swap

		wordtemp = bf * 256 + bl;
		return wordtemp;
	}
	if(!ARCH_BIGENDIAN && bigendian )
	{
		///no Swap

		wordtemp = bl * 256 + bf;
		return wordtemp;
	}
	if(ARCH_BIGENDIAN && !bigendian )
	{
		///no Swap

		wordtemp = bl * 256 + bf;
		return wordtemp;
	}
	
	/*
	if (isBigendian())
		wordtemp = bf * 256 + bl;
	else
		wordtemp = bl * 256 + bf;
	*/
	return wordtemp;
}


bool PacketLib::ByteStream::setWord(dword start, word value)
{
    byte b1, b2;
    /// only even positions
    if(start%2 != 0)
        return false;
    /// It must not overtake the stream dimension
    if(start+1 > byteInTheStream)
        return false;
    /// Byte extraction
    /// \param LSByte
    b1 = (byte) value & 0xFF;
    /// \param MSByte
    b2 = (byte) (value >> 8);
	
	/*
	if(bigendian)
	{
        /// Swap
        stream[start] = b2;
        stream[start+1] = b1;
    } else {
		/// no Swap
        stream[start] = b1;
        stream[start+1] = b2;
	}
	*/
	
	if(!ARCH_BIGENDIAN && !bigendian )
	{
		//noswap
        stream[start] = b1;
        stream[start+1] = b2;
		return true;
    }
	if(ARCH_BIGENDIAN && bigendian )
	{
		//noswap
        stream[start] = b1;
        stream[start+1] = b2;
		return true;
    }
	if(!ARCH_BIGENDIAN && bigendian )
	{
        /// Swap
        stream[start] = b2;
        stream[start+1] = b1;
		return true;
    }
	if(ARCH_BIGENDIAN && !bigendian )
	{
        /// Swap
        stream[start] = b2;
        stream[start+1] = b1;
		return true;
    }
	
	/*
    if((bigendian && !ARCH_BIGENDIAN) || (!bigendian && ARCH_BIGENDIAN))
    {
        /// Swap
        stream[start] = b2;
        stream[start+1] = b1;
    }
    else
    {
        /// No swap for x86
        stream[start] = b1;
        stream[start+1] = b2;
    }
		*/
    return true;

}


void PacketLib::ByteStream::swapWordIfStreamIsLittleEndian()
{
    if(!bigendian)
    {
       swapWord();
    }
}

void PacketLib::ByteStream::swapWordIfStreamIsBigEndian()
{
    if(bigendian)
    {
       swapWord();
    }
}

void PacketLib::ByteStream::setMemoryAllocated(bool allocated)
{
	mem_allocation = allocated;
}

void PacketLib::ByteStream::deleteStreamMemory()
{
    if(!mem_allocation_constructor && mem_allocation)
        delete[] stream;
}

ByteStreamPtr PacketLib::ByteStream::getPaddedCopy(dword chunkSize, dword padSize)
{
	if(byteInTheStream % chunkSize != 0)
		throw new PacketException("getPadCopy() error. Chunk size must be a divisor of ByteStream::size().");

	dword nChunks = byteInTheStream / chunkSize;
	dword newChunkSize = chunkSize + padSize;

	ByteStreamPtr sPtr = ByteStreamPtr(new ByteStream(nChunks*(newChunkSize), bigendian));
	byte* raw = sPtr->getStream();

	for(dword i=0; i<nChunks; i++)
		memcpy(raw+i*newChunkSize, stream+i*chunkSize, chunkSize);

	return sPtr;
}

ByteStreamPtr PacketLib::ByteStream::getUnpaddedCopy(dword chunkSize, dword padSize)
{
	if(byteInTheStream % chunkSize != 0)
		throw new PacketException("getUnpadCopy() error. Chunk size must be a divisor of ByteStream::size().");
	if(chunkSize - padSize <= 0)
		throw new PacketException("getUnpadCopy() error. Chunk size - pad size gives a value <= 0.");

	dword nChunks = byteInTheStream / chunkSize;
	dword newChunkSize = chunkSize - padSize;

	ByteStreamPtr sPtr = ByteStreamPtr(new ByteStream(nChunks*(newChunkSize), bigendian));
	byte* raw = sPtr->getStream();

	for(dword i=0; i<nChunks; i++)
		memcpy(raw+i*newChunkSize, stream+i*chunkSize, newChunkSize);

	return sPtr;
}

void PacketLib::ByteStream::swapWord() {
	dword dim =  byteInTheStream;
	for(dword i = 0; i< dim; i+=2)
	{
		/// For odd dimensions
		if((dim - i) != 1)
		{
			byte btemp = stream[i];
			stream[i] = stream[i+1];
			stream[i+1] = btemp;
		}
	}
}

void PacketLib::ByteStream::swapWordForIntel() {
	swapWordIfStreamIsBigEndian();
}
