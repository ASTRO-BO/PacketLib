/***************************************************************************
                          FileStream.h  -  description
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
#ifndef FILESTREAM_H_INCLUDED_9A29CA8E
#define FILESTREAM_H_INCLUDED_9A29CA8E
#include "File.h"
#include "ByteStream.h"

namespace PacketLib {

//##ModelId=3C187750014C
//##Documentation
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/FileStream.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: FileStream.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.2 $
//##	\brief This class represent a stream of byte into a file.
class FileStream : public File
{
    public:

        //##ModelId=3C1877500365
        FileStream(bool prefix, bool bigen, word dimprefix, long startposition = 0);

        //##ModelId=3C87744100F3
        ByteStream* readPrefix();

        //##ModelId=3C205AF20368
        ByteStream* readHeader(unsigned int dimHeader);

        //##ModelId=3C205AF2036F
        ByteStream* readDataField(unsigned int dimDataField);

    private:

        //##ModelId=3C18775002D6
        //##Documentation
        //## Indicates if it's present a prefix for each packet
        //## \li true if it's present
        //## \li false if it isn't present
        bool thereIsPrefix;

        ByteStream* header;

        ByteStream* dataField;

        ByteStream* prefix;

        word dimPrefix;

};

}

#endif                           /* FILESTREAM_H_INCLUDED_9A29CA8E */
