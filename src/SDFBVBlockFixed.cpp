/***************************************************************************
                          SDFBVBlockFixed.cpp  -  description
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
 
#include "SDFBVBlockFixed.h"

using namespace PacketLib;


word SDFBVBlockFixed::getNumberOfRealElement()
{
    Field* f = getFields(indexOfNElement);
    return (word) f->value + addToNElement;
}



void SDFBVBlockFixed::setNumberOfRealElement(word value)
{
    Field* f = getFields(indexOfNElement);
    f->value = value -  addToNElement;
}



void SDFBVBlockFixed::setIndexOfNElement(word index)
{
    indexOfNElement = index;
}



void SDFBVBlockFixed::setAddToNElement(unsigned num)
{
    addToNElement = num;
}



void SDFBVBlockFixed::setMaxNumberOfElement(word num)
{
    maxNumberOfElement = num;
}



word SDFBVBlockFixed::getMaxNumberOfElement() const
{
    return maxNumberOfElement;
}
