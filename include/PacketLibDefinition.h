/***************************************************************************
                          Definition.h  -  description
                             -------------------
    begin                : Tue Nov 27 2001
    copyright            : (C) 2001 by Andrea Bulgarelli
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
#ifndef Definition_h_h
#define Definition_h_h

#include <string>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <time.h>
#define TRUE 1
#define FALSE 0
#define EOI -1
#define DEBUGMODE 0
#define ERRORMODE 1
#define EXCEPTION_ENABLED 1
//#define NULL 0

#define ARCH_BIGENDIAN 0

//#define NOFIELDSNAME

//#define PRINTDEBUG(strprint) if(DEBUGMODE) cout << strprint << endl;
#define PRINTDEBUG(strprint) if(DEBUGMODE) cout <<  strprint << endl;
#define PRINTERROR(strprint) if(ERRORMODE) cerr <<  strprint << endl;
//##ModelId=3C0F6C190397

namespace PacketLib {

//##ModelId=3EADC124020F
typedef unsigned char byte;      //1 byte for both 32 and 64 bit system
//##ModelId=3C187750017C
typedef unsigned short word;     //2 byte for both 32 and 64 bit system
//##ModelId=3EADC124021D
typedef unsigned int dword;     //4 byte for both 32 and 64 bit system

}

#define U24BITINTGEGERUNSIGNED_MAX 16777215
#define U24BITINTGEGERSIGNED_MIN -8388607
#define U24BITINTGEGERSIGNED_MAX 8388607

#define CONFIG_MAXNUMBER_OFCONFIGILES 20000
#define CONFIG_MAXNUMBEROFLINES_OFCONFIGILES 100000

//typedef bool boolean;

using namespace std;
#endif
