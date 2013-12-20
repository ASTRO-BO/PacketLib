/***************************************************************************
                          FileStream.h  -  description
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
 
#ifndef _FILESTREAM_H
#define _FILESTREAM_H
#include "File.h"
#include "ByteStream.h"

namespace PacketLib
{

/// 	\brief This class represent a stream of byte into a file.
class FileStream : public File
{
public:

    FileStream(bool prefix, bool bigen, word dimprefix, long startposition = 0);

    ByteStreamPtr readPrefix();

    ByteStreamPtr readHeader(unsigned int dimHeader);

    ByteStreamPtr readDataField(unsigned int dimDataField);

private:
    ///  Indicates if it's present a prefix for each packet
    ///  \li true if it's present
    ///  \li false if it isn't present
    bool thereIsPrefix;

    ByteStreamPtr header;

    ByteStreamPtr dataField;

    ByteStreamPtr prefix;

    word dimPrefix;

};

}

#endif                           /* FILESTREAM_H_INCLUDED_9A29CA8E */
