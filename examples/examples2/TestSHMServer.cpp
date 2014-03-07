/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Fri Jun 21 09:17:06 CEST 2002
    copyright            : (C) 2002 by Andrea Bulgarelli
    email                : bulgarel@tesre.bo.cnr.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream.h>
#include <stdlib.h>
#include "PacketExceptionIO.h"
#include "SHM.h"

typedef struct s {
	long pointer;
	char filename[200];
	char int[1000];
} str_idl;



#define SHM_PROCESSOR_SYNC 10000

#define KEY_SYNC(acq_type, ch)  SHM_PROCESSOR_SYNC+#acq_type*100 + #ch

int main(int argc, char *argv[])
{
try {
	cout << "Creazione della memoria condivisa" << endl;
	SHM* shm = new SHM(true);
	int i;
	shm->create(100000, 1, sizeof(shm_sync));
  shm->open();
/*	int arr[3];
	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;*/
	str_idl* s = (str_idl*) new str_idl;
	s->pointer=10;

	shm->writeSlot(0, (void*) s);
	scanf("writed ... %d", &i);
	shm->close();
	scanf("%d", &i);
	delete shm;
}
catch(PacketExceptionIO* e) {
	cout << e->geterror() << endl;
}

}
