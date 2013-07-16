/***************************************************************************
                          PacktException.h  -  description
                             -------------------
    begin                : Tue Jan 15 2002
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

#ifndef PACKTEXCEPTION_H
#define PACKTEXCEPTION_H
#include "PacketLibDefinition.h"

namespace PacketLib {

//##ModelId=3EADC123017C
//##Documentation
//##	$Date: 2012/06/08 15:14:29 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/PacketException.h,v 1.4 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Id: PacketException.h,v 1.4 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Revision: 1.4 $
//##	\brief Exception class of the PacketLib
class PacketException
{
    public:

        //##ModelId=3EADC139032F
        PacketException(const char* error, int code = 0);

        //##ModelId=3EADC1390335
        virtual ~PacketException();

        //##ModelId=3EADC1390337
        virtual const char* geterror();

        //##ModelId=3EADC1390339
        void add(const char* error);

        //##ModelId=3EADC139033C
        int geterrorcode() const;


        //##ModelId=3EADC139033E
        void seterrorcode(int errorcode);

    protected:

        //##ModelId=3EADC1390326
        string* error;

        //##ModelId=3EADC139032C
        int errorcode;

};
}


#endif



