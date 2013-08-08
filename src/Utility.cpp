/***************************************************************************
                          Utility.cpp  -  description
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001, 2013 by Andrea Bulgarelli
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

#include "Utility.h"
#include "File.h"
#include "PacketExceptionIO.h"
#include <time.h>

using namespace PacketLib;

int Utility::convertToInteger(string bin)
{
    string::size_type pos;

    pos = bin.find("0b",0);
    if(pos == 0)
    {
        /// is a binary number
        return binaryToInteger(bin);
    }
    else
    {
        /// is a decimal number
        return atoi(bin.c_str());
    }

}

char* Utility::extractPath(char* filename)
{
    int len = Utility::strlen(filename);
    int index;
    for(index=len-1; index>=0; index--)
    {
        //I		char c = filename[index];
        if(filename[index] == '/')
            break;
    }
    char* path = new char[index+2];
    for(int i=0; i<=index; i++)
        path[i]=filename[i];
    path[index+1] = '\0';
    return path;
}


int Utility::convertToInteger(char* bin)
{
    string s;
    s = bin;
    int r = Utility::convertToInteger(s);
    return r;
}


/// Return the integer or -1 if the string isn't a binary number 
int Utility::binaryToInteger(string bin)
{
    string::size_type pos;
    pos = bin.find("0b",0);
    if(pos == 0)
    {
        ///is a binary number
        int size = bin.size();
        int pos = 1;
        int decimal = 0;
        const char* start;
        const char* c = bin.c_str();
        start = c+2;
        c += (size-1);
        while(c >= start)
        {
            decimal += (*c - 48) * pos;
            c--;
            pos *= 2;
        }
        //PRINTDEBUG(decimal);
        return decimal;
    }
    else
        return -1;
}


/// Return the integer or -1 if the string isn't a binary number 
int Utility::hexadecimalToInteger(string hex)
{
    string::size_type pos;
    pos = hex.find("0x",0);
    if(pos == 0)
    {
        ///is a binary number
        int size = hex.size();
        int pos = 1;
        int decimal = 0;
        const char* start;
        const char* c = hex.c_str();
        start = c+2;
        c += (size-1);
        while(c >= start)
        {
            /*decimal += (*c - 48) * pos;
            c--;
            pos *= 16;*/
            int val;
            if(*c >=97)
                val = *c - 32;
            else
                val = *c;
            if(val>=65)
                val=val-55;
            else
                val=val-48;
            decimal += val * pos;
            c--;
            pos *= 16;
        }
        //PRINTDEBUG(decimal);
        return decimal;
    }
    else
        return -1;
}

char* Utility::format_output(dword data, bool dec, bool hex, bool bin)
{
    string q, qdata, qn;
    char* c1 = new char[1];
    char* c2 = new char[1];
    q = "";
    if(dec)
    {
        q = "(";
        sprintf(c2, "%d", (int) data);
        q = q + c2;
        q = q + ")";
    }
    if(hex)
    {
        sprintf(c1, "0x%4.4x", (int) data);
        q = q + c1;
    }
    if(bin)
    {
        qdata = wordToBinary2(data,16);
        q = q + qdata;
    }
    return (char*) q.c_str();

}

/// It gives n bit (alligned at right of "x" from the p position). 
/// Example: getbits(x,4,3) gives bit 4, 3, 2 (alligned at right)
/// 7 6 5 4 3 2 1 0 */
unsigned Utility::getbits(word x, int p, int n)
{
    return (x >> (p + 1 - n)) & ~(~0 << n);
}

unsigned Utility::getbits32(dword x, int p, int n)
{
    return (x >> (p + 1 - n)) & ~(~0 << n);
}

/// It gives n bit (alligned at right of "x" from the p position). 
/// Example: getbits(x,4,3) gives bit 4, 5, 6 (alligned at right but with packet numbering)
/// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

unsigned Utility::getbits2(word x, int p, int n)
{
    return getbits(x, 15 - p, n);
}


string* Utility::wordToBinary(word w, byte dim)
{
    string* temp = new string("");
    unsigned valuetemp;
    /// It starts from LSB
    for(int i=0; i<dim; i++)
    {
        valuetemp = getbits(w, i, 1);
        if(valuetemp)
            *temp = "1" + *temp;
        else
            *temp = "0" + *temp;
    }
    return temp;
    /* versione che restituisce un char*
        char *temp = (char*) new char[dim+1];
        unsigned valuetemp;
    		unsigned int i;
        for(i=0; i<dim+1; i++) temp[i]='\0';
        //si parte da LSB
        for(i=0; i<dim; i++)
        {
            valuetemp = getbits(w, 15-i, 1);
            if(valuetemp)
                temp[i] = '1';
            else
                temp[i] = '0';
        }
    		i++;
    		temp[i]='\0';
        return temp;*/
}

char* Utility::wordToBinary2(dword w, unsigned int dim)
{
    unsigned int dimchar = dim+1+(dim/4+10);
    char *temp = (char*) new char[dimchar];
    unsigned valuetemp;
    unsigned int i;
    for(i=0; i<dimchar; i++) temp[i]='\0';
    /// It starts from LSB
    int j=-1;
    for(i=0; i<dim; i++)
    {
        j++;
        if(i%4==0)
        {
            temp[j]='-';
            j++;
        }
        valuetemp = getbits32(w, 31-i, 1);
        if(valuetemp)
            temp[j] = '1';
        else
            temp[j] = '0';
    }
    return temp;
}



char* Utility::integerToString(int n)
{
    char* c = new char[20];
    sprintf(c, "%d", n);
    ///string* s = new string;
    return c;
}



char* Utility::stringToHexadecimal(byte* b, dword dim, bool bigendian, bool addSpace)
{
    string s, s1, s2;
    char* c1 = new char[1];
    char* c2 = new char[1];
    s = "";
    for(dword i=0; i<dim; i+=2)
    {
        if(bigendian)
        {
            sprintf(c1, "%2x", b[i]);
            sprintf(c2, "%2x", b[i+1]);
        }
        else
        {
            sprintf(c1, "%2x", b[i+1]);
            sprintf(c2, "%2x", b[i]);
        }
        if(c1[0] == ' ') c1[0] = '0';
        if(c2[0] == ' ') c2[0] = '0';
        if(c1[0] >= 'a' && c1[0] <= 'f')
            c1[0] -= 32;
        if(c1[1] >= 'a' && c1[1] <= 'f')
            c1[1] -= 32;
        if(c2[0] >= 'a' && c2[0] <= 'f')
            c2[0] -= 32;
        if(c2[1] >= 'a' && c2[1] <= 'f')
            c2[1] -= 32;
        s1 = c1;
        s2 = s1;
        if(addSpace)
            s2 += ' ';
        s1 = c2;
        s += s2 + s1;
        if(addSpace)
            s += ' ';

    }
    //s += '\n';
    char* cc = (char*) s.c_str();
    return cc;
}



char* Utility::byteToHexadecimal(byte b)
{
    string s;
    char* c1 = new char[1];
    sprintf(c1, "%2x", b);
    if(c1[0] == ' ') c1[0] = '0';
    if(c1[0] >= 'a' && c1[0] <= 'f')
        c1[0] -= 32;
    if(c1[1] >= 'a' && c1[1] <= 'f')
        c1[1] -= 32;
    s = c1;
    char* cc = (char*) s.c_str();
    return cc;
}



long Utility::strlen(char* s)
{
    long i = 0;
    while(s[i] != '\0')
        i++;
    return i;
}


/*
char* Utility::ftimeToChar(word MSB, word LSB, word ms)
{
    char*s = new char[1];
    struct tm* res;
    time_t timep;
    timep = (time_t) MSB;
    timep = (timep << 16) + (time_t) LSB;
    res = localtime(&timep);
    string time;
    sprintf(s, "%d/%d/%d - %d:%d:%d:%d", res->tm_year + 1900,res->tm_mon + 1, res->tm_mday, res->tm_hour,res->tm_min, res->tm_sec, ms);
    return s;
}



char* Utility::ftimeToChar(struct tm* res, word ms)
{
    char*s = new char[1];
    sprintf(s, "%d/%d/%d - %d:%d:%d:%d", res->tm_year + 1900,res->tm_mon + 1, res->tm_mday, res->tm_hour,res->tm_min, res->tm_sec, ms);
    return s;
}


*/



char* Utility::integerToString2(int n, char* str)
{
    char* c = new char[1];
    //string s;
    char s[10] ;
    strcpy(s, "%");
    strcat(s, str);
    strcat(s, "d");
    //	s += str;
    //	s += "d";
    sprintf(c, (char*) s, n);
    return c;
}

char* Utility::integerToString3(char* str, int n)
{
    char* c = new char[1];
    sprintf(c, (char*) str, n);
    return c;
}


char* Utility::extractFileName(char* path)
{
    int i = 0;
    int index = -1;
    while(path[i] != '\0')
    {

        if(path[i] == '/')
            index = i;
        i++;
    }
    char* filename = new char[i - index+1];
    for(int j=index+1; j<=i+1; j++)
        filename[j-(index+1)] = path[j];
    return filename;
}



char* Utility::charcat(char* c1, char c2)
{
    int l = strlen(c1);
    c1[l] = c2;
    c1[l+1] = '\0';
    return c1;
}

int Utility::getchildpid(int startpid, char* procname, int maxsearch)
{
    int tmppid = startpid;
    int nsearch = 0;
    File f(false);
    bool ok;
    char c[50] ;
    while(nsearch <= maxsearch)
    {
        sprintf(c, "/proc/%d/cmdline", tmppid);
        try
        {
            ok = true;
            f.open(c, "r");
            char* name = f.getLine();
            if(strcmp(name, procname) != 0)
                ok = false;
        }
        catch(PacketExceptionIO* e)
        {
            ok = false;
        }
        if(ok)
            break;
        else
        {
            nsearch++;
            tmppid++;
        }
    }
    if(nsearch > maxsearch)
        return 0;
    else
        return tmppid;
}

bool Utility::getchildpidlive(int pid)
{
    File f(false);
    bool ok;
    char c[50] ;

    sprintf(c, "/proc/%d/cmdline", pid);
    try
    {
        ok = true;
        f.open(c, "r");
    }
    catch(PacketExceptionIO* e)
    {
        ok = false;
    }
    return ok;
}
