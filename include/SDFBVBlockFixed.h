/***************************************************************************
                          SDFBVBlockFixed.h  -  description
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
 
#ifndef _SDFBVBLOCKFIXED_H
#define _SDFBVBLOCKFIXED_H

#include "PacketLibDefinition.h"
#include "PartOfPacket.h"

namespace PacketLib
{

///	\brief Class wich represent the part of block with the number of field fixed.
class SDFBVBlockFixed : public PartOfPacket
{
private:

    /// Represents the index of field which have the number of element in a
    /// source data field variable.
    word indexOfNElement;

    /// Number to sum for obtaining the numbers of real elements.
    unsigned addToNElement;

    /// Represents the max number of elements in a source data field variable.
    word maxNumberOfElement;

public:

    word getNumberOfRealElement() ;

    void setNumberOfRealElement(word value);

     void setIndexOfNElement(word index);

    /// Sets the number to sum for obtaining the numbers of real elements.
    void setAddToNElement(unsigned num);

    void setMaxNumberOfElement(word num);

    word getMaxNumberOfElement() const;

};

}
#endif                           /* SDFBVBLOCKFIXED_H_INCLUDED_C36FC736 */
