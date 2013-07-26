/***************************************************************************
                          SHM.h  -  description
                             -------------------
    begin                : Fri Jun 21 2002
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

#ifndef SHM_H
#define SHM_H

#include "PacketLibDefinition.h"
#include "Device.h"
#include "PacketExceptionIO.h"
#include <sys/shm.h>
#include <sys/stat.h>

namespace PacketLib
{

//##ModelId=3C87743F03C1
//##Documentation
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/SHM.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: SHM.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.2 $
//##	\brief This class represents generic SHM
class SHM : public Device
{
public:
    //##ModelId=3AA649A2005A
    SHM(bool bigendian);

    //##ModelId=3AA649A200A0
    virtual ~SHM();

    //##ModelId=3EADC1430288
    virtual bool create(long shmkey, dword num_slot, dword slot_dim) throw(PacketExceptionIO*);

    //##ModelId=3AA649A200B4
    virtual bool open(long shmkey = 0, dword num_slot = 0, dword slot_dim = 0) throw(PacketExceptionIO*);

    //##ModelId=3AA649A200FA
    virtual bool close() throw(PacketExceptionIO*);

    //##ModelId=3EADC143038F
    virtual bool destroy() throw(PacketExceptionIO*);

    //##ModelId=3EADC14303AE
    virtual bool isCreated() const;

    //##ModelId=3EADC14303CF
    virtual void writeSlot(dword n_slot, void* element) throw(PacketExceptionIO*);

    //##ModelId=3EADC144005C
    virtual void* readSlot(dword n_slot) throw(PacketExceptionIO*);

protected:

    //##ModelId=3EADC14301AD
    int shmid;               //id restituito dalla shmget

    //##ModelId=3EADC14301D3
    long shmkey;             //chiave passata dall'utente

    //##ModelId=3EADC14301FC
    dword num_slot;          //numero di slot della shm

    //##ModelId=3EADC1430211
    dword slot_dim;          //dimensione di ogni slot

    //##ModelId=3EADC1430224
    bool created;

    //##ModelId=3EADC1430250
    byte* shm;               //puntatore al primo elemento della shared memory
};

}

#endif
