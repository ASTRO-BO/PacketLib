/**
 * @(#) InputPacketStream.cpp
 */

#include "InputPacketStreamFile.h"

#include "FileStream.h"
#include <stdlib.h>
#include "PacketExceptionFileFormat.h"
#define FSP_STEP 5000

using namespace PacketLib;

//##ModelId=3DBFBFBE02E5
InputPacketStreamFile::InputPacketStreamFile(const char* fileNameConfig, const char* fileNameStream, long initialPosition) :
    InputPacketStream(fileNameConfig)
{
    this->initialPosition = initialPosition;
    this->fileNameStream = (char*) fileNameStream;
    inputStream = 0;
    numberOfFileStreamPointer = 0;
    listOfFileStreamPointer = (FileStreamPointer**)new FileStreamPointer* [FSP_STEP];
    for(int i=0; i<FSP_STEP; i++)
        listOfFileStreamPointer[i] = 0;
}


//##ModelId=3DBFBFBE0323
InputPacketStreamFile::InputPacketStreamFile() : InputPacketStream()
{
    this->initialPosition = 0;
    this->fileNameStream = 0;
    inputStream = 0;
    numberOfFileStreamPointer = 0;
    listOfFileStreamPointer = (FileStreamPointer**)new FileStreamPointer* [FSP_STEP];
    for(int i=0; i<FSP_STEP; i++)
        listOfFileStreamPointer[i] = 0;
}


//##ModelId=3DBFBFBE0324
InputPacketStreamFile::~InputPacketStreamFile()
{

    for(int i=0; i<numberOfFileStreamPointer; i++)
    {
        delete listOfFileStreamPointer[i];
        listOfFileStreamPointer[i] = 0;
    }
    delete[] listOfFileStreamPointer;

    delete inputStream;
    //delete fileNameStream;
}


//##ModelId=3DBFBFBE0353
bool InputPacketStreamFile::openInputStream() throw(PacketExceptionIO*)
{
    FileStream* f = new FileStream(prefix, bigendian, dimPrefix, initialPosition);
    try
    {
        f->open(fileNameStream);
        inputStream = f;
        return true;
    }
    catch(PacketExceptionIO* e)
    {
        delete f;
        e->add(" - ");
        e->add(fileNameStream);
        e->add("Stream file: ");
        throw e;
    }
}


//##ModelId=3DBFBFBE038F
bool InputPacketStreamFile::freeRun() throw(PacketExceptionIO*)
{
    ByteStream* b1 = 0, *b2 = 0, *b0 = 0;
    word pl, dim;
    long pointer;

    for(int i=0; i<numberOfFileStreamPointer; i++)
    {
        delete listOfFileStreamPointer[i];
        listOfFileStreamPointer[i] = 0;
    }

    numberOfFileStreamPointer = 0;
    inputStream->setFirstPos();
    long count = 0;
    unsigned dimHeader = headerReference->getDimension();
    while(!inputStream->isEOF())
    {
        int pindex = 0;
        pointer = inputStream->getpos();
        b0 = inputStream->readPrefix();
        if(inputStream->isEOF())
        {
            delete b0;
            return true;
        }
        b1 = inputStream->readHeader(dimHeader);
        if(b1->getDimension() != dimHeader)
        {
            if(b1->getDimension() != 0)
                pindex = 0;
            else
            {
                delete b0;
                delete b1;
                numberOfFileStreamPointer = count;
                return false;
            }
        }
        else
        {
            headerReference->setByteStream(b1);
            pl = headerReference->getPacketLength();
            b2 = inputStream->readDataField(pl);
            dim= b2->getDimension();
            if(dim != pl)
            {
                if(dim != 0)
                    pindex = 0;
                else
                {
                    delete b0;
                    delete b1;
                    delete b2;
                    numberOfFileStreamPointer = count;
                    return false;
                }
            }
            else
                pindex = detPacketType(b0, b1, b2);
        }
        delete b0;
        delete b1;
        delete b2;
        FileStreamPointer* fsp = new FileStreamPointer;
        fsp->typeOfPacket = pindex;
        fsp->pointerStart = pointer;
        fsp->index = count;
        fsp->nameOfPacket = (char*) (getPacketType(pindex)->getName());
        fsp->pointerEnd = inputStream->getpos() - 1;
        if(count%FSP_STEP == 0)
        {
            //resize
            FileStreamPointer** lfsp = (FileStreamPointer**)new FileStreamPointer* [count + FSP_STEP];
            for(int i=0; i<count; i++)
            {
                lfsp[i] = listOfFileStreamPointer[i];
            }
            for(int i=count; i<count + FSP_STEP; i++)
                lfsp[i] = 0;
            FileStreamPointer** lfsp_tmp = listOfFileStreamPointer;
            listOfFileStreamPointer = lfsp;
            delete[] lfsp_tmp;
        }

        listOfFileStreamPointer[count] = fsp;
        count++;
        numberOfFileStreamPointer = count;
    }
    numberOfFileStreamPointer = count;
    return true;
}


//##ModelId=3DBFBFBE0390
Packet* InputPacketStreamFile::getPacketFromFileStreamPointer(int index, bool newpointer) throw(PacketExceptionIO*)
{
    //int i;
    long pos;
    int type;
    ByteStream* b1 = 0, *b2 = 0, *b0 = 0;
    word pl;

    if(index > numberOfFileStreamPointer)
        index = numberOfFileStreamPointer;
    if(index < 0)
        index = 0;

    FileStreamPointer* it = listOfFileStreamPointer[index];

    type = it->typeOfPacket;
    pos = it->pointerStart;
    inputStream->setpos(pos);
    int dimHeader = headerReference->getDimension();
    b0 = inputStream->readPrefix();
    if((b1 = inputStream->readHeader(dimHeader)) == NULL)
        return NULL;
    headerReference->setByteStream(b1);
    pl = headerReference->getPacketLength();
    if((b2 = inputStream->readDataField(pl)) == NULL)
        return NULL;
    Packet* p = getPacketType(type);
    if(newpointer)
    {
        //make the full filename
        string sf = pathFileNameConfig;
        sf += "/";
        sf += p->getFileName();
        Packet* pnew;
        pnew = new Packet(bigendian);
        //cout << (char*)sf.c_str() << endl;
        pnew->createPacketType((char*)sf.c_str(), prefix, dimPrefix);
        p = pnew;
    }
    if(p->setPacketValue(b0, b1, b2))
        return p;
    else
        return NULL;
}


//##ModelId=3DBFBFBE0354
void InputPacketStreamFile::closeInputStream() throw(PacketExceptionIO*)
{
    inputStream->close();
}


//##ModelId=3DBFBFBE03C0
FileStreamPointer* InputPacketStreamFile::getFileStreamPointer(int index)
{
    if(index > numberOfFileStreamPointer)
        index = numberOfFileStreamPointer;
    if(index < 0)
        index = 0;

    FileStreamPointer* it = listOfFileStreamPointer[index];
    return it;
}


//##ModelId=3DBFBFBE03C2
void InputPacketStreamFile::setInitialPosition(long p)
{
    if(p>=0)
        initialPosition = p;
    else
        initialPosition = 0;
}


//##ModelId=3DBFBFBE0325
void InputPacketStreamFile::setFileNameStream(char* f)
{
    this->fileNameStream = f;
}


//##ModelId=3DBFBFBE038E
long InputPacketStreamFile::getNumberOfFileStreamPointer()
{
    return numberOfFileStreamPointer;
}


//##ModelId=3DBFBFBE0356
Packet* InputPacketStreamFile::getPacketFromStream() throw (PacketExceptionIO * )
{
    ByteStream* b1 = 0, *b2 = 0, *b0 = 0;
    word pl, dim;
    unsigned dimHeader = headerReference->getDimension();

    if(inputStream->isEOF())
        return 0;
    b0 = inputStream->readPrefix();
    if(inputStream->isEOF())
    {
        delete b0;
        return 0;
    }
    b1 = inputStream->readHeader(dimHeader);
    if(b1->getDimension() != dimHeader)
    {
        delete b0;
        delete b1;
        return 0;
    }

    headerReference->setByteStream(b1);
    pl = headerReference->getPacketLength();
    b2 = inputStream->readDataField(pl);
    dim = b2->getDimension();
    if(dim != pl)
    {
        delete b0;
        delete b1;
        delete b2;
        return 0;
    }

    Packet* p;
    for (int i = 1; i<numberOfPacketType; i++)
    {
        p = getPacketType(i);
        if(p->setAndVerifyPacketValue(b0, b1, b2))
        {
            return p;
        }
    }
    p->deleteExternalByteStream();
    return 0;

}


//##ModelId=3DBFBFBE0355
bool InputPacketStreamFile::isInputStreamEOF() throw(PacketExceptionIO*)
{
    return inputStream->isEOF();
}
