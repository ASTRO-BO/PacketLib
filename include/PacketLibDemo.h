#ifndef Demo_h_h
#define Demo_h_h
#include <stdio.h>
#define DEMOMODE 0

#define STARTTIME 1114771000
#define NSECDEMO 2592000
#define DEMORET if(DEMOMODE) if(difftime(time(NULL), STARTTIME) > NSECDEMO) { cerr << "PacketLib: demo period expired. Contact: bulgarelli@bo.iasf.cnr.it" << endl; return; };
#define DEMORET0_STRONG if(DEMOMODE) \
	if(difftime(time(NULL), STARTTIME) > NSECDEMO || fopen("/tmp/SYM34TU3IOP", "r") != 0 ) { \
	 fopen("/tmp/SYM34TU3IOP", "w"); \
	 cerr << "PacketLib: demo period expired. Contact: bulgarelli@bo.iasf.cnr.it" << endl; return 0; };
#define DEMORET0 if(DEMOMODE) \
	if(difftime(time(NULL), STARTTIME) > NSECDEMO ) { \
	 cerr << "PacketLib: demo period expired. Contact: bulgarelli@bo.iasf.cnr.it" << endl; return 0; };
#endif
