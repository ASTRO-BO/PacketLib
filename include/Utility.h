/***************************************************************************
                          Utility.h  -  description
                             -------------------
    begin                : Thu Nov 29 2001
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

#ifndef UTILITY_H
#define UTILITY_H

#include "PacketLibDefinition.h"

namespace PacketLib {

//##ModelId=405AA8630391
//##Documentation
//##	$Date: 2005/05/09 12:24:29 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/Utility.h,v 1.5 2005/05/09 12:24:29 bulgarelli Exp $
//##	$Id: Utility.h,v 1.5 2005/05/09 12:24:29 bulgarelli Exp $
//##	$Revision: 1.5 $
//##	\brief A class with static method with common functionality.
class Utility
{
    public:

        //##ModelId=405AA86F00B2
        static int binaryToInteger(string bin);

        //##ModelId=405AA86F00B5
        static int convertToInteger(string bin);

        //##ModelId=405AA86F00B9
        static int convertToInteger(char* bin);

        //##ModelId=405AA86F00BC
        //##Documentation
        //## Restituisce n bit (allineati a destra di x a partire dalla posizione p).
        //## Esempio: getbits(x,4,3) restituisce bit 4, 3, 2 (allinemanto a destra)
        //## 7 6 5 4 3 2 1 0 */
        static unsigned getbits(word x, int p, int n);

        //##ModelId=405AA86F00C2
        static unsigned getbits2(word x, int p, int n);
	
		static unsigned getbits32(dword x, int p, int n);

        //##ModelId=405AA86F00C7
        static string* wordToBinary(word w, byte dim);

	      //##ModelId=405AA86F00CB
		static char* wordToBinary2(dword w, unsigned int dim);

	      //##ModelId=405AA86F00D0
		static char* format_output(dword data, bool dec, bool hex, bool bin);		

        //##ModelId=405AA86F00D8
        static char* integerToString(int n);


        //##ModelId=405AA86F00DB
        static char* stringToHexadecimal(byte* s, dword dim, bool bigendian = true, bool addSpace = true);

        //##ModelId=405AA86F00E1
        static long strlen(char* s);

        //##ModelId=405AA86F00E5
        static char* byteToHexadecimal(byte b);

        //##ModelId=405AA86F00E8
        static int hexadecimalToInteger(string hex);

        //##ModelId=405AA86F00EB
//        static char* ftimeToChar(word MSB, word LSB, word ms);

        //##ModelId=3EADC15C019B
//        static char* ftimeToChar(struct tm* res, word ms);

        //##ModelId=3EADC15C0240
        static char* integerToString2(int n, char* str);

        static char* integerToString3(char* str, int n);

        //##ModelId=405AA86F00F0
        static char* extractFileName(char* path);
	
		static char* extractPath(char* filename);

        //##ModelId=405AA86F00F3
        static char* charcat(char*, char);

	      //##ModelId=405AA86F00F7
        static int getchildpid(int startpid, char* procname, int maxsearch=1000);

	      //##ModelId=405AA86F00FC
        static bool getchildpidlive(int pid);
};

}
#endif
