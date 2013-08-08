/***************************************************************************
                          PacketLibDemo.h  -  description
                             -------------------
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

#ifndef _DEMO_H_H
#define _DEMO_H_H
#include <stdio.h>
#define DEMOMODE 0

#define STARTTIME 1114771000
#define NSECDEMO 2592000
#define DEMORET if(DEMOMODE) if(difftime(time(NULL), STARTTIME) > NSECDEMO) { cerr << "PacketLib: demo period expired. Contact: bulgarelli@iasfbo.inaf.it" << endl; return; };
#define DEMORET0_STRONG if(DEMOMODE) \
	if(difftime(time(NULL), STARTTIME) > NSECDEMO || fopen("/tmp/SYM34TU3IOP", "r") != 0 ) { \
	 fopen("/tmp/SYM34TU3IOP", "w"); \
	 cerr << "PacketLib: demo period expired. Contact: bulgarelli@iasfbo.inaf.it" << endl; return 0; };
#define DEMORET0 if(DEMOMODE) \
	if(difftime(time(NULL), STARTTIME) > NSECDEMO ) { \
	 cerr << "PacketLib: demo period expired. Contact: bulgarelli@iasfbo.inaf.it" << endl; return 0; };
#endif
