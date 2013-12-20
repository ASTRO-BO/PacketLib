/***************************************************************************
                          FileStream.cpp  -  description
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
 
#include "FileStream.h"

using namespace PacketLib;

FileStream::FileStream(bool prefix, bool bigen, word dimprefix, long startposition)
    : File(bigen, startposition)
{
    thereIsPrefix = prefix;
    dimPrefix = dimprefix;
}


ByteStreamPtr FileStream::readHeader(unsigned int dimHeader)
{
    header = getNByte(dimHeader);
    return header;
}


ByteStreamPtr FileStream::readDataField(unsigned int dimDataField)
{
    dataField = getNByte(dimDataField);
    return dataField;
}


ByteStreamPtr FileStream::readPrefix()
{
    if(thereIsPrefix)
        prefix = getNByte(dimPrefix);
    else
        prefix = 0;
    return prefix;
}
