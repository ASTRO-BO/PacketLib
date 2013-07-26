/***************************************************************************
                          SDFNoBlockFixed.h  -  description
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
#ifndef SDFNOBLOCKFIXED_H_HEADER_INCLUDED_F6C633EF
#define SDFNOBLOCKFIXED_H_HEADER_INCLUDED_F6C633EF

#include "PacketLibDefinition.h"
#include "SourceDataField.h"
class ConfigurationFile;

namespace PacketLib
{

//##Documentation
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/SDFNoBlockFixed.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: SDFNoBlockFixed.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.2 $
//##	\brief Represents a source data field of packet where the structure is noblock
//## and with a fixed dimension. Layout 1 (see Interface Control Document).
class SDFNoBlockFixed : public SourceDataField
{
public:

    //##ModelId=3EADC1430143
    SDFNoBlockFixed();

    //##ModelId=3EADC1430144
    virtual ~SDFNoBlockFixed();

    //##ModelId=3EADC1430146
    virtual bool loadFields(InputText& fp) throw(PacketException*);

    //##ModelId=3EADC1430149
    virtual Field* getFields(word index);

    //##ModelId=3EADC143014D
    virtual word getFieldValue(word index);

    //##Documentation
    //## Sets the value of a field in the list of fields of this part of packet. Remember that
    //## if a predefined value is specified in the .stream, this method has not effect and the
    //## value contained in the .stream is used.
    //## \param index Represent the index in the list.
    //## \param value The value must be set.
    virtual void setFieldValue(word index, word value);

    //##ModelId=3EADC1430154
    virtual dword getMaxDimension();

};

}
#endif                           /* SDFNOBLOCKFIXED_H_HEADER_INCLUDED_F6C633EF */
