/***************************************************************************
                          MSGQ.h  -  description
                             -------------------
    begin                : Wed Dec 4 2002
    copyright            : (C) 2002, 2013 by Andrea Bulgarelli
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

#ifndef _MSGQ_H
#define _MSGQ_H

#include "PacketLibDefinition.h"
#include "Device.h"
#include "PacketExceptionIO.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


namespace PacketLib
{

typedef struct  mesgbuf
{
    long    mtype;
    char    mtext[2048];
} msgbuf;

///	\brief Represent a shared queue
class MSGQ : public Device
{
public:

    MSGQ(bool bigendian);

    virtual ~MSGQ();

    virtual bool create(long shqkey, long dim) throw(PacketExceptionIO*);

    virtual bool open(long shqkey, long dim) throw(PacketExceptionIO*);

    virtual bool close() throw(PacketExceptionIO*);

    virtual bool destroy() throw(PacketExceptionIO*);

    virtual bool isCreated() const;

    virtual void writeMessage(char* msg, long mtype) throw(PacketExceptionIO*);

    virtual char* readMessage(long mtype) throw(PacketExceptionIO*);

public:

    /// id given by shmget
    int msgqid;              
    
    /// key given by the user
    long msgqkey;            

    bool created;

    long dimmsg;

    msgbuf buf;

};



}

#endif
