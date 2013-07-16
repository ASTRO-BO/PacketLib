#include "SDFBVBlockFixed.h"

using namespace PacketLib;

//##ModelId=3C9AEDA50372
word SDFBVBlockFixed::getNumberOfRealElement()
{
    Field* f = getFields(indexOfNElement);
    return (word) f->value + addToNElement;
}


//##ModelId=3DA3E5C100AA
void SDFBVBlockFixed::setNumberOfRealElement(word value)
{
    Field* f = getFields(indexOfNElement);
    f->value = value -  addToNElement;
}


/** No descriptions */
//##ModelId=3C9AEDA60002
void SDFBVBlockFixed::setIndexOfNElement(word index)
{
    indexOfNElement = index;
}


//##ModelId=3C9AEDA601CA
void SDFBVBlockFixed::setAddToNElement(unsigned num)
{
    addToNElement = num;
}


//##ModelId=3DA3E5C101C2
void SDFBVBlockFixed::setMaxNumberOfElement(word num)
{
    maxNumberOfElement = num;
}


//##ModelId=3DA3E5C102D0
word SDFBVBlockFixed::getMaxNumberOfElement() const
{
    return maxNumberOfElement;
}
