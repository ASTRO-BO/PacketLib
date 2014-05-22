/***************************************************************************
                          PacketLibDefinition.h  -  description
                             -------------------
    begin                : Tue Nov 27 2001
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
 
#ifndef _DEFINITION_H_H
#define _DEFINITION_H_H

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
#define PACKETNOTRECOGNIZED 0
/// define NULL 0

#define ARCH_BIGENDIAN 0

enum CompressionAlgorithms  { NONE, LZH };

/// define NOFIELDSNAME

///define PRINTDEBUG(strprint) if(DEBUGMODE) cout << strprint << endl;
#define PRINTDEBUG(strprint) if(DEBUGMODE) cout <<  strprint << endl;
#define PRINTERROR(strprint) if(ERRORMODE) cerr <<  strprint << endl;

namespace PacketLib
{
/// 1 byte for both 32 and 64 bit system
typedef unsigned char byte;     
///2 byte for both 32 and 64 bit system
typedef unsigned short word;     
/// 4 byte for both 32 and 64 bit system
typedef unsigned int dword;     

}

#define U24BITINTGEGERUNSIGNED_MAX 16777215
#define U24BITINTGEGERSIGNED_MIN -8388607
#define U24BITINTGEGERSIGNED_MAX 8388607

#define CONFIG_MAXNUMBER_OFCONFIGILES 20000
#define CONFIG_MAXNUMBEROFLINES_OFCONFIGILES 100000

/// typedef bool boolean;

using namespace std;
#endif
