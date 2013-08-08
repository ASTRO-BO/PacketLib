/***************************************************************************
                          Utility.h  -  description
                             -------------------
    begin                : Thu Nov 29 2001
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

#ifndef _UTILITY_H
#define _UTILITY_H

#include "PacketLibDefinition.h"

namespace PacketLib
{

///	\brief A class with static method with common functionality.
class Utility
{
public:

    static int binaryToInteger(string bin);

    static int convertToInteger(string bin);

    static int convertToInteger(char* bin);


    /// It gives n bit (alligned at right of "x" from the p position). 
    /// Example: getbits(x,4,3) gives bit 4, 3, 2 (alligned at right)
    /// 7 6 5 4 3 2 1 0 */
    static unsigned getbits(word x, int p, int n);

    static unsigned getbits2(word x, int p, int n);

    static unsigned getbits32(dword x, int p, int n);

    static string* wordToBinary(word w, byte dim);

    static char* wordToBinary2(dword w, unsigned int dim);

    static char* format_output(dword data, bool dec, bool hex, bool bin);

    static char* integerToString(int n);


    static char* stringToHexadecimal(byte* s, dword dim, bool bigendian = true, bool addSpace = true);

    static long strlen(char* s);

    static char* byteToHexadecimal(byte b);

    static int hexadecimalToInteger(string hex);

    ///        static char* ftimeToChar(word MSB, word LSB, word ms);

    ///        static char* ftimeToChar(struct tm* res, word ms);

    static char* integerToString2(int n, char* str);

    static char* integerToString3(char* str, int n);

    static char* extractFileName(char* path);

    static char* extractPath(char* filename);

    static char* charcat(char*, char);

    static int getchildpid(int startpid, char* procname, int maxsearch=1000);

    static bool getchildpidlive(int pid);
};

}
#endif
