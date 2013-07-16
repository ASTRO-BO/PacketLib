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
#include <unistd.h>

typedef struct s1 {
	long pointer;
	char filename[200];
//	char int[1000];
} str_idl;

typedef struct s {
	unsigned short status;
	unsigned long fits_raw_number;
	unsigned long run_id;
	char filename[500];
} shm_sync;

int main(int argc, char *argv[])
{
try {
	//2
	cout << "Aggancio alla memoria condivisa" << endl;
	SHM* shm = new SHM(true);
	int i;

	shm->open(10301, 1, sizeof(shm_sync));
	//scanf("%d", &i);	
	while(true) {
	shm_sync* arr = (shm_sync*) shm->readSlot(0);
//	for(int i = 0; i < 3; i++)
		cout << arr->status << endl;
		cout << arr->fits_raw_number << endl;
		cout << arr->run_id << endl;
		cout << arr->filename << endl;
		cout << "-------------------" << endl;
		sleep(1);
	}
	scanf("%d", &i);
	shm->close();
	delete shm;
}
catch(PacketExceptionIO* e) {
	cout << e->geterror() << endl;
}

}
