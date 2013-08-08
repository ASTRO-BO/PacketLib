/***************************************************************************
                          SHM.h  -  description
                             -------------------
    begin                : Fri Jun 21 2002
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

#ifndef _SHM_H
#define _SHM_H

#include "PacketLibDefinition.h"
#include "Device.h"
#include "PacketExceptionIO.h"
#include <sys/shm.h>
#include <sys/stat.h>

namespace PacketLib
{

///	\brief This class represents generic SHM
class SHM : public Device
{
public:
    SHM(bool bigendian);

    virtual ~SHM();

    virtual bool create(long shmkey, dword num_slot, dword slot_dim) throw(PacketExceptionIO*);

    virtual bool open(long shmkey = 0, dword num_slot = 0, dword slot_dim = 0) throw(PacketExceptionIO*);

    virtual bool close() throw(PacketExceptionIO*);

    virtual bool destroy() throw(PacketExceptionIO*);

    virtual bool isCreated() const;

    virtual void writeSlot(dword n_slot, void* element) throw(PacketExceptionIO*);

    virtual void* readSlot(dword n_slot) throw(PacketExceptionIO*);

protected:
    /// id given by shmget
    int shmid;               

    /// key passed by the user
    long shmkey;             

    /// number of slots of the shm
    dword num_slot;          

    /// slot dimension
    dword slot_dim;          

    bool created;
    
    /// pointer to the first element of the shared memory
    byte* shm;               
};

}

#endif
