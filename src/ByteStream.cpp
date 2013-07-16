/**
 * @(#) ByteStream.cpp
 */

#include "ByteStream.h"
#include "PacketLibDemo.h"
#include "Utility.h"
using namespace PacketLib;
                                 //oggetti che devono deallocare memoria
dword ByteStream::count_object = 0;
                                 //oggetti che non devono deallocare memoria
dword ByteStream::count_object2 = 0;
//##ModelId=3DA3E55D032A
dword ByteStream::count_object_deleted = 0;
//##ModelId=3DA3E55E005A
dword ByteStream::count_object_deleted2 = 0;
//long ByteStream::count_object_wrong = 0;

/*
  mem_allocation = true indica che  presente memoria allocata che deve essere liberata
    dal distruttore.
    In tutti i metodi costruttori o di tipo set che accettano un byte*, nel caso in cui
    memory_sharing=false significa che viene effettuato lo swap.
    Nei metodi costruttori e di tipo set che accettano ByteStream* non viene mai
    effettuato lo swap.
*/

//##ModelId=3C0F6BDB003B
PacketLib::ByteStream::ByteStream(bool bigendian)
{
    mem_allocation_constructor = true;

    byteInTheStream = 0;
    this->stream = 0;
    this->bigendian = bigendian;

    setMemoryAllocated(false);
    mem_allocation_constructor = false;
}


//##ModelId=3EADC12501CA
PacketLib::ByteStream::ByteStream(long dim, bool bigendian)
{
    mem_allocation_constructor = true;

    byteInTheStream = dim;
    stream = (byte*) new byte[dim];
    //memset(stream, 0, dim); ok
    this->bigendian = bigendian;

    setMemoryAllocated(true);
    mem_allocation_constructor = false;
}


//##ModelId=3EADC125023B
PacketLib::ByteStream::ByteStream(byte* stream, long dim, bool bigendian, bool memory_sharing)
{
    mem_allocation_constructor = true;

    byteInTheStream = dim;
    this->stream = stream;
    this->bigendian = bigendian;
    if(!memory_sharing)
	swap();
    //se memory_sharing == false significa che la responsabilit della memoria diviene
    //di questo oggetto
    setMemoryAllocated(!memory_sharing);
    mem_allocation_constructor = false;
}


//##ModelId=3EADC125031B
PacketLib::ByteStream::ByteStream(ByteStream* b0, ByteStream* b1, ByteStream* b2)
{
    //si suppone che gli stream siano gi swappati
    unsigned i = 0;
    unsigned dim = 0;
    if(b0 == 0 && b1 == 0 && b2 == 0)
    {

        setMemoryAllocated(false);

        byteInTheStream  = 0;
        stream = 0;
        return;
    }
    byteInTheStream = (b0!=0?b0->getDimension():0) + (b1!=0?b1->getDimension():0) + (b2!=0?b2->getDimension():0);
    stream = (byte*) new byte[byteInTheStream];
    this->bigendian = (b0!=0?b0->isBigendian():(b1!=0?b1->isBigendian():(b2!=0?b2->isBigendian():false)));
    if(b0 != 0)
    {
        dim = b0->getDimension();
        for(;i<b0->getDimension(); i++)
            stream[i] = b0->stream[i];
    }
    if(b1!=0)
    {
        dim += b1->getDimension();
        unsigned istart = i;
        for(;i<dim; i++)
        {
            unsigned pos = i-istart;
            stream[i] = b1->stream[pos];
        }
    }
    if(b2!=0)
    {
        dim += b2->getDimension();
        unsigned istart = i;
        for(;i<dim; i++)
        {
            unsigned pos = i-istart;
            stream[i] = b2->stream[pos];
        }
    }
    setMemoryAllocated(true);
}


//##ModelId=3C205AF201F8
PacketLib::ByteStream::~ByteStream()
{
    if(mem_allocation)
    {
        ByteStream::count_object_deleted++;
	//cout << "ByteStream::~ByteStream() delete[] stream;" << endl;
        delete[] stream; stream = 0;
    }
    else
    	;
       // ByteStream::count_object_deleted2++;
    //cout <<  "ByteStream::~ByteStream()" << endl;
}


//##ModelId=3C0F6BDB0041
byte PacketLib::ByteStream::getByte( unsigned byteNumber)
{
    DEMORET0;
    if(byteNumber >= 0 && byteNumber <= byteInTheStream)
        return stream[byteNumber];
    else
        return 0;
}


//##ModelId=3C18775001BB
long PacketLib::ByteStream::getValue(unsigned start, unsigned dim)
{
    DEMORET0;
    byte b1, b2;
    //only 1 or 2 bytes
    if(dim <=0 || dim > 2)
        return -1;               //errore
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
                //posto pari
                b1=stream[start+1];
                b2=stream[start];
            }
            else
            {
                b1 = (start-1)<0?0:stream[start-1];
                b2 = (start+2)>byteInTheStream?0:stream[start+2];
            }
        }
    }
    return b2 + b1*256;
}


//##ModelId=3C301E8800C7
ByteStream* PacketLib::ByteStream::getSubByteStream(word first, word last)
{
    DEMORET0;
    if(first > last)
        return NULL;
    if(last > byteInTheStream)
        return NULL;
    ByteStream* b = new ByteStream((stream + first), last-first+1, bigendian, true);
    return b;
}


//##ModelId=3EADC126003A
ByteStream* PacketLib::ByteStream::getSubByteStreamCopy(word first, word last)
{
    DEMORET0;
    if(first > last)
        return NULL;
    if(last > byteInTheStream)
        return NULL;
    byte* streamtemp = (byte*) new byte[last-first+1];
    for(int i=0; i<last-first+1; i++)
        streamtemp[i] = stream[first+i];
    ByteStream* b = new ByteStream(streamtemp, last-first+1, bigendian, false);
    return b;
}


//##ModelId=3EADC12503D4
byte* PacketLib::ByteStream::getStream()
{
    return stream;
}


//##ModelId=3EADC1260005
byte* PacketLib::ByteStream::getOutputStream()
{
    swap();
    return stream;
}


//##ModelId=3EADC126001E
void PacketLib::ByteStream::endOutputStream()
{
    swap();
}


//##ModelId=3C87744001D8
unsigned PacketLib::ByteStream::getDimension()
{
    return byteInTheStream;
}


//##ModelId=3C87744001EC
char* PacketLib::ByteStream::printStreamInHexadecimal()
{
    return Utility::stringToHexadecimal(stream, byteInTheStream);
}


//##ModelId=3EADC1260244
void PacketLib::ByteStream::setStreamCopy(byte* b, unsigned dim)
{
    deleteStreamMemory();

    byteInTheStream = dim;
    stream = (byte*) new byte[dim];
    for(unsigned i=0; i<dim; i++)
        stream[i] = b[i];
    swap();
    setMemoryAllocated(true);
}


//##ModelId=3C87744001F6
bool PacketLib::ByteStream::setStream(byte* b, unsigned dim, bool bigendian, bool memory_sharing)
{
    deleteStreamMemory();

    byteInTheStream = dim;
    this->bigendian = bigendian;
    this->stream = b;

    if(!memory_sharing) swap();
    setMemoryAllocated(!memory_sharing);
    return true;
}


//##ModelId=3EADC1260157
bool PacketLib::ByteStream::setStream(ByteStream* b, word first, word last)
{
    if(first > last)
        return false;
    if(last > b->getDimension())
        return false;

    deleteStreamMemory();

    this->stream = (b->stream + first);
    this->byteInTheStream = last-first+1;
    this->bigendian = b->isBigendian();

    setMemoryAllocated(false);

    return true;
}


//##ModelId=3EADC1270079
bool PacketLib::ByteStream::getMemAllocation()
{
    return mem_allocation;
}


//##ModelId=3EADC127009D
bool PacketLib::ByteStream::isBigendian() const
{
    return bigendian;
}


//##ModelId=3EADC12603A5
void PacketLib::ByteStream::setByte(unsigned start, word value)
{
    stream[start] = value;
}


//##ModelId=3EADC12602F1
bool PacketLib::ByteStream::setWord(unsigned start, word value)
{
    byte b1, b2;
    //solo posizioni pari
    if(start%2 != 0)
        return false;
    //non deve superare la dimensione dello stream
    if(start+1 > byteInTheStream)
        return false;
    //estrazione dei byte
    b1 = (byte) value;           //LSByte
    b2 = (byte) (value >> 8);    //MSByte
    if((bigendian && !ARCH_BIGENDIAN) || (!bigendian && ARCH_BIGENDIAN))
    {
        //swap
        stream[start] = b2;
        stream[start+1] = b1;
    }
    else
    {
        //no swap per x86
        stream[start] = b1;
        stream[start+1] = b2;
    }
    return true;

}


//##ModelId=3EADC12700E8
void PacketLib::ByteStream::swap()
{
    if(!bigendian)
    {
        word dim =  byteInTheStream;
        for(word i = 0; i< dim; i+=2)
        {
            if((dim - i) != 1)   //per dimensioni dispari
            {
                byte btemp = stream[i];
                stream[i] = stream[i+1];
                stream[i+1] = btemp;
            }
        }
    }
}


//##ModelId=3EADC127010D
void PacketLib::ByteStream::setMemoryAllocated(bool allocated)
{

    if(allocated)
    {
        if(mem_allocation_constructor)
        {
            ByteStream::count_object ++;
        }
        else
        {
            if(mem_allocation == false)
            {
                ByteStream::count_object2 --;
                ByteStream::count_object ++;
            }
        }
        mem_allocation = allocated;
    }
    else
    {
        if(mem_allocation_constructor)
        {
            ByteStream::count_object2 ++;
        }
        else
        {
            if(mem_allocation == true)
            {
                ByteStream::count_object --;
                ByteStream::count_object2 ++;
            }
        }
        mem_allocation = allocated;
    }
}


//##ModelId=3EADC12701A5
void PacketLib::ByteStream::deleteStreamMemory()
{
    if(!mem_allocation_constructor && mem_allocation)
        delete[] stream;
}
