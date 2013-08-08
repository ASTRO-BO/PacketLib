/***************************************************************************
                          SDFNoBlockFixed.h  -  description
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
 
#ifndef _SDFNOBLOCKFIXED_H
#define _SDFNOBLOCKFIXED_H

#include "PacketLibDefinition.h"
#include "SourceDataField.h"
class ConfigurationFile;

namespace PacketLib
{

///	\brief Represents a source data field of packet where the structure is noblock
/// and with a fixed dimension. Layout 1 (see Interface Control Document).
class SDFNoBlockFixed : public SourceDataField
{
public:

    SDFNoBlockFixed();

    virtual ~SDFNoBlockFixed();

    virtual bool loadFields(InputText& fp) throw(PacketException*);

    virtual Field* getFields(word index);

    virtual word getFieldValue(word index);

    /// Sets the value of a field in the list of fields of this part of packet. Remember that
    /// if a predefined value is specified in the .stream, this method has not effect and the
    /// value contained in the .stream is used.
    /// \param index Represent the index in the list.
    /// \param value The value must be set.
    virtual void setFieldValue(word index, word value);

    virtual dword getMaxDimension();

};

}
#endif                           /* SDFNOBLOCKFIXED_H_HEADER_INCLUDED_F6C633EF */
