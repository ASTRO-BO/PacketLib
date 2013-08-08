/***************************************************************************
                          SDFNoBlockFixed.cpp  -  description
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
 
#include "SDFNoBlockFixed.h"
#include "ConfigurationFile.h"

using namespace PacketLib;


SDFNoBlockFixed::SDFNoBlockFixed() : SourceDataField("SDF NoBlock Fixed")
{
    fixed = true;
    isblock = false;
    rblock = false;
}



SDFNoBlockFixed::~SDFNoBlockFixed()
{
}



bool SDFNoBlockFixed::loadFields(InputText& fp) throw(PacketException*)
{
    char* line;
    line=fp.getLine();
    if(strcmp(line, "[SourceDataFieldList]") == 0)
    {
        return PartOfPacket::loadFields(fp);
    }
    else
        return false;
}



Field* SDFNoBlockFixed::getFields(word index)
{
    return PartOfPacket::getFields(index);
};


word SDFNoBlockFixed::getFieldValue(word index)
{
    return PartOfPacket::getFieldValue(index);
}


void SDFNoBlockFixed::setFieldValue(word index, word value)
{
    PartOfPacket::setFieldValue(index, value);
}



dword SDFNoBlockFixed::getMaxDimension()
{
    return getDimension();
}
