/***************************************************************************
                          SHM.cpp  -  description
                             -------------------
    begin                : Fri Jun 21 2002
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

#include "SHM.h"
#include "PacketLibDemo.h"
#define PERM 0777

using namespace PacketLib;


SHM::SHM(bool bigendian) : Device (bigendian)
{
    created = false;
}



SHM::~SHM()
{
    shmctl(shmid, IPC_RMID, 0);
    //cout << "removed form ~" << endl;
}



bool SHM::create(long shmkey, dword num_slot, dword slot_dim) throw(PacketExceptionIO*)
{
    DEMORET0;
    try
    {
        if(created)
            return false;

        if((shmid = shmget(shmkey, num_slot*slot_dim, PERM | IPC_CREAT | IPC_EXCL)) < 0)
        {
            if(errno == EEXIST)
            {
                throw new PacketExceptionIO("SHM: the shared memory exists.");
            }
            else
            {
                throw new PacketExceptionIO("SHM: it is impossible to create the shared memory.");
            }
        }
        this->shmkey = shmkey;
        this->num_slot = num_slot;
        this->slot_dim = slot_dim;
        eof = true;              //non ha senso in questo contesto
        closed = true;           //corrisponde con attach
        created = true;
        return true;
    }
    catch(PacketExceptionIO* e)
    {
        throw e;
    }
}



bool SHM::open(long shmkey, dword num_slot, dword slot_dim) throw(PacketExceptionIO*)
{
    DEMORET0;
    //attach
    try
    {
        /// It gets the shared memory
        if(shmkey != 0)
        {
            if((shmid = shmget(shmkey, num_slot*slot_dim, 0)) < 0)
            {
                if(errno == EEXIST)
                {
                    throw new PacketExceptionIO("SHM: the shared memory exists.");
                }
                else
                    throw new PacketExceptionIO("SHM: it is impossible to create the shared memory.");
            }
            this->shmkey = shmkey;
            this->num_slot = num_slot;
            this->slot_dim = slot_dim;
        }
        /// It connects the shared memory

        if((shm = (byte*) shmat(shmid, 0, 0)) == (byte*) -1)
            throw new PacketExceptionIO("SHM: it is impossible to connect with the shared memory.");

        eof = false;
        closed = false;
        return true;
    }
    catch(PacketExceptionIO* e)
    {
        throw e;
    }
}



bool SHM::close() throw(PacketExceptionIO*)
{
    //detach
    try
    {
        if(shmdt(shm) < 0)
            throw new PacketExceptionIO("SHM: it is impossible to disconnect the shared memory.");
        eof = true;
        closed = true;
        return true;
    }
    catch(PacketExceptionIO* e)
    {
        throw e;
    }
}



bool SHM::destroy() throw(PacketExceptionIO*)
{
    try
    {
        if(shmctl(shmid, IPC_RMID, 0) < 0)
            throw new PacketExceptionIO("SHM: it is impossible to deallocate the shared memory.");
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


bool SHM::isCreated() const
{
    return created;
}



void SHM::writeSlot(dword n_slot, void* element) throw(PacketExceptionIO*)
{
    try
    {
        if(closed)
            throw new PacketExceptionIO("SHM: it is impossible to write in a shared memory not connected.");
        if(n_slot > this->num_slot)
            throw new PacketExceptionIO("SHM: out of writing index.");
        byte* ext_temp = (byte*) element;
        for(dword i = 0; i < slot_dim; i++)
            shm[n_slot*slot_dim + i] = ext_temp[i];
    }
    catch(PacketExceptionIO* e)
    {
        throw e;
    }
}



void* SHM::readSlot(dword n_slot) throw(PacketExceptionIO*)
{
    try
    {
        if(closed)
            throw new PacketExceptionIO("SHM: it is impossible to read from a shared memory not connected.");
        if(n_slot > this->num_slot)
            throw new PacketExceptionIO("SHM: out of reading index.");
        return (void*) (shm + n_slot*slot_dim);
    }
    catch(PacketExceptionIO* e)
    {
        throw e;
    }
}
