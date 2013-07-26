/***************************************************************************
                          SHQ.h  -  description
                             -------------------
    begin                : Wed Dec 4 2002
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

#ifndef MSGQ_H
#define MSGQ_H

#include "PacketLibDefinition.h"
#include "Device.h"
#include "PacketExceptionIO.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


namespace PacketLib
{

//##ModelId=3EADC124022B
typedef struct  mesgbuf
{
    long    mtype;
    char    mtext[2048];
} msgbuf;

//##Documentation
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/MSGQ.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: MSGQ.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.2 $
//##	\brief Represent a shared queue
class MSGQ : public Device
{
public:

    //##ModelId=3EADC12A0052
    MSGQ(bool bigendian);

    //##ModelId=3EADC12A0056
    virtual ~MSGQ();

    //##ModelId=3EADC12A0058
    virtual bool create(long shqkey, long dim) throw(PacketExceptionIO*);

    //##ModelId=3EADC12A0061
    virtual bool open(long shqkey, long dim) throw(PacketExceptionIO*);

    //##ModelId=3EADC12A0069
    virtual bool close() throw(PacketExceptionIO*);

    //##ModelId=3EADC12A006B
    virtual bool destroy() throw(PacketExceptionIO*);

    //##ModelId=3EADC12A006E
    virtual bool isCreated() const;

    //##ModelId=3EADC12A0070
    virtual void writeMessage(char* msg, long mtype) throw(PacketExceptionIO*);

    //##ModelId=3EADC12A0078
    virtual char* readMessage(long mtype) throw(PacketExceptionIO*);

public:

    //##ModelId=3EADC12A0040
    int msgqid;               //id restituito dalla shmget

    //##ModelId=3EADC12A0042
    long msgqkey;             //chiave passata dall'utente

    //##ModelId=3EADC12A0044
    bool created;

    //##ModelId=3EADC12A0045
    long dimmsg;

    //##ModelId=3EADC12A0048
    msgbuf buf;

};



}

#endif
