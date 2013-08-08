/***************************************************************************
                          MSGQ.cpp  -  description
                             -------------------
    begin                : Wed Dec 4 2002
    copyright            : (C) 2002, 2013 by Andrea Bulgarelli
    email                : bulgarelli@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "MSGQ.h"
#include "PacketLibDemo.h"
#define PERMMSGQ 0666
#define MSG_TYPE  10

using namespace PacketLib;



MSGQ::MSGQ(bool bigendian) : Device(bigendian)
{
    created = 0;
}

MSGQ::~MSGQ()
{
    //delete[] buf.mtext;
}


bool MSGQ::create(long msgqkey, long dim) throw(PacketExceptionIO*)
{
    DEMORET0;
    try
    {
        if(created)
            throw new PacketExceptionIO("MSGQ: the message queue exists.");
        if((msgqid =  msgget(msgqkey, PERMMSGQ | IPC_CREAT | IPC_EXCL)) < 0)
        {
            if(errno == EEXIST)
            {
                throw new PacketExceptionIO("MSGQ: the message queue exists.");
            }
            else
            {
                throw new PacketExceptionIO("MSGQ: it is impossible to create the message queue.");
            }
        }
        this->msgqkey = msgqkey;
        // buf.mtext = (char*) new char[dim];
        dimmsg = dim;
        eof = true;              //non ha senso in questo contesto
        closed = false;           //corrisponde con attach
        created = true;
        return true;
    }
    catch(PacketExceptionIO* e)
    {
        throw e;
    }

}


bool MSGQ::open(long msgqkey, long dim) throw(PacketExceptionIO*)
{
    DEMORET0;
    try
    {
        /// It gets the message queue
        if(msgqkey != 0)
        {
            if((msgqid = msgget(msgqkey, PERMMSGQ)) < 0)
            {
                if(errno == EEXIST)
                {
                    throw new PacketExceptionIO("MSGQ: the shared queue exists.");
                }
                else
                    throw new PacketExceptionIO("MSGQ: it is impossible to open the message queue.");
            }
            this->msgqkey = msgqkey;
        }
        // buf.mtext = (char*) new char[dim];
        dimmsg=dim;
        eof = false;
        closed = false;
        return true;
    }
    catch(PacketExceptionIO* e)
    {
        throw e;
    }
}


bool MSGQ::close() throw(PacketExceptionIO*)
{
    eof = true;
    closed = true;
    return true;
}


bool MSGQ::destroy() throw(PacketExceptionIO*)
{
    try
    {
        if(msgctl(msgqid, IPC_RMID, 0) < 0)
            throw new PacketExceptionIO("MSGQ: it is impossible to deallocate the message queue.");
        eof = true;
        closed = true;
        created = false;
        return true;
    }
    catch(PacketExceptionIO* e)
    {
        throw e;
    }
}


bool MSGQ::isCreated() const
{
    return created;
}


void MSGQ::writeMessage(char* msg, long mtype) throw(PacketExceptionIO*)
{
    //msgbuf localbuf;
    //localbuf.mtype = mtype;
    //localbuf.mtext = msg;
    memcpy(&buf.mtext, msg, dimmsg);
    buf.mtype = mtype;
    try
    {
        if(closed)
            throw new PacketExceptionIO("MSGQ: it is impossible to write in a message queue not opened.");
        if(msgsnd(msgqid, &buf, dimmsg, 0) < 0)
            throw new PacketExceptionIO("MSGQ: it is impossible to write in this message queue.");
    }
    catch(PacketExceptionIO* e)
    {
        throw e;
    }
}


char* MSGQ::readMessage(long mtype) throw(PacketExceptionIO*)
{
    buf.mtype = mtype;
    try
    {
        if(closed)
            throw new PacketExceptionIO("MSGQ: it is impossible to read from a message queue not opened.");
        if(msgrcv(msgqid, &buf, dimmsg, mtype, 0) < 0)
            throw new PacketExceptionIO("MSGQ: it is impossible to write in this message queue.");
        return buf.mtext;
    }
    catch(PacketExceptionIO* e)
    {
        throw e;
    }
}
