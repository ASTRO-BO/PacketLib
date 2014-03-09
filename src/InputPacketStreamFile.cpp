/***************************************************************************
                          InputPacketStreamFile.cpp  -  description
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


#include "InputPacketStreamFile.h"

#include "FileStream.h"
#include <stdlib.h>
#include "PacketExceptionFileFormat.h"
#define FSP_STEP 5000

using namespace PacketLib;


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


bool InputPacketStreamFile::freeRun() throw(PacketExceptionIO*)
{
    ByteStreamPtr b0, b1, b2;
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
    unsigned dimHeader = headerReference->size();
    while(!inputStream->isEOF())
    {
        int pindex = 0;
        pointer = inputStream->getpos();
        b0 = inputStream->readPrefix();
        if(inputStream->isEOF())
            return true;

        b1 = inputStream->readHeader(dimHeader);
        if(b1->size() != dimHeader)
        {
            if(b1->size() != 0)
                pindex = 0;
            else
            {
                numberOfFileStreamPointer = count;
                return false;
            }
        }
        else
        {
            headerReference->setByteStream(b1);
            pl = headerReference->getPacketLength();
            b2 = inputStream->readDataField(pl);
            dim= b2->size();
            if(dim != pl)
            {
                if(dim != 0)
                    pindex = 0;
                else
                {
                    numberOfFileStreamPointer = count;
                    return false;
                }
            }
            else
                pindex = detPacketType(b0, b1, b2);
        }
        FileStreamPointer* fsp = new FileStreamPointer;
        fsp->typeOfPacket = pindex;
        fsp->pointerStart = pointer;
        fsp->index = count;
        fsp->nameOfPacket = (char*) (getPacketType(pindex)->getName());
        fsp->pointerEnd = inputStream->getpos() - 1;
        if(count%FSP_STEP == 0)
        {
            /// resize
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


Packet* InputPacketStreamFile::getPacketFromFileStreamPointer(int index, bool newpointer) throw(PacketExceptionIO*)
{
    //int i;
    long pos;
    int type;
    ByteStreamPtr b0, b1, b2;
    word pl;

    if(index > numberOfFileStreamPointer)
        index = numberOfFileStreamPointer;
    if(index < 0)
        index = 0;

    FileStreamPointer* it = listOfFileStreamPointer[index];

    type = it->typeOfPacket;
    pos = it->pointerStart;
    inputStream->setpos(pos);
    int dimHeader = headerReference->size();
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
        /// make the full filename
        string sf = pathFileNameConfig;
        sf += "/";
        sf += p->getFileName();
        Packet* pnew;
        pnew = new Packet(bigendian);
        //cout << (char*)sf.c_str() << endl;
        pnew->createPacketType((char*)sf.c_str(), prefix, dimPrefix);
        p = pnew;
    }
    if(p->set(b0, b1, b2))
        return p;
    else
        return NULL;
}



void InputPacketStreamFile::closeInputStream() throw(PacketExceptionIO*)
{
    inputStream->close();
}



FileStreamPointer* InputPacketStreamFile::getFileStreamPointer(int index)
{
    if(index > numberOfFileStreamPointer)
        index = numberOfFileStreamPointer;
    if(index < 0)
        index = 0;

    FileStreamPointer* it = listOfFileStreamPointer[index];
    return it;
}



void InputPacketStreamFile::setInitialPosition(long p)
{
    if(p>=0)
        initialPosition = p;
    else
        initialPosition = 0;
}



void InputPacketStreamFile::setFileNameStream(char* f)
{
    this->fileNameStream = f;
}



long InputPacketStreamFile::getNumberOfFileStreamPointer()
{
    return numberOfFileStreamPointer;
}



Packet* InputPacketStreamFile::getPacketFromStream() throw (PacketExceptionIO * )
{
    ByteStreamPtr b0, b1, b2;
    word pl, dim;
    unsigned dimHeader = headerReference->size();

    if(inputStream->isEOF())
        return 0;
    b0 = inputStream->readPrefix();
    if(inputStream->isEOF())
        return 0;
    b1 = inputStream->readHeader(dimHeader);
    if(b1->size() != dimHeader)
        return 0;

    headerReference->setByteStream(b1);
    pl = headerReference->getPacketLength();
    b2 = inputStream->readDataField(pl);
    dim = b2->size();
    if(dim != pl)
        return 0;

    Packet* p;
    for (int i = 1; i<numberOfPacketType; i++)
    {
        p = getPacketType(i);
		p->set(b0, b1, b2);
        if(p->verify())
        {
            return p;
        }
    }
    return 0;
}



bool InputPacketStreamFile::isInputStreamEOF() throw(PacketExceptionIO*)
{
    return inputStream->isEOF();
}
