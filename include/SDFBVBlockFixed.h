/***************************************************************************
                          SDFBVBlockFixed.h  -  description
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
#ifndef SDFBVBLOCKFIXED_H_INCLUDED_C36FC736
#define SDFBVBLOCKFIXED_H_INCLUDED_C36FC736

#include "PacketLibDefinition.h"
#include "PartOfPacket.h"

namespace PacketLib
{

//##Documentation
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/SDFBVBlockFixed.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: SDFBVBlockFixed.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.2 $
//##	\brief Class wich represent the part of block with the number of field fixed.
class SDFBVBlockFixed : public PartOfPacket
{
private:

    //##ModelId=3EADC14203D4
    //##Documentation
    //## Represents the index of field which have the number of element in a
    //## source data field variable.
    word indexOfNElement;

    //##ModelId=3EADC14203DC
    //##Documentation
    //## Number to sum for obtaining the numbers of real elements.
    unsigned addToNElement;

    //##ModelId=3EADC14203E1
    //##Documentation
    //## Represents the max number of elements in a source data field variable.
    word maxNumberOfElement;

public:

    //##ModelId=3EADC1430001
    word getNumberOfRealElement() ;

    //##ModelId=3EADC1430003
    void setNumberOfRealElement(word value);

    //##ModelId=3EADC1430008
    void setIndexOfNElement(word index);

    //##ModelId=3EADC143000D
    //##Documentation
    //## Sets the number to sum for obtaining the numbers of real elements.
    void setAddToNElement(unsigned num);

    //##ModelId=3EADC1430013
    void setMaxNumberOfElement(word num);

    //##ModelId=3EADC1430018
    word getMaxNumberOfElement() const;

};

}
#endif                           /* SDFBVBLOCKFIXED_H_INCLUDED_C36FC736 */
