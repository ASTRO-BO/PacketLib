#include "SDFBVBlock.h"

using namespace PacketLib;

//##ModelId=3C9AED6B007E
Field* SDFBVBlock::getFields(word index)
{
    word n1 = fixed.getNumberOfFields();
    word n2 = variables[0].getNumberOfFields();

    if(index <= n1-1)
        return fixed.getFields(index);
    else
    {
        word nblock = (index - n1) / n2;
        return variables[nblock].getFields(index-n1-nblock*n2);
    }
}

void SDFBVBlock::setFieldValue(word index, word value) {
Field* f = getFields(index);
	f->value = (value & pattern[f->dimension]);
}

//##ModelId=3DA3E5BF0352
word SDFBVBlock::getFieldValue(word index)
{
    return getFields(index)->value;
}


//##ModelId=3C9AED6B000F
word SDFBVBlock::getNumberOfFields()
{
    word nfv = 0;
    word nre = fixed.getNumberOfRealElement();
    for(word i=0; i<nre; i++)
        nfv += variables[i].getNumberOfFields();
    return fixed.getNumberOfFields() + nfv;
}


//##ModelId=3C9AED6B0226
word SDFBVBlock::getDimension()
{
    word nfv = 0;
    word nff = fixed.getDimension();
    word nre = fixed.getNumberOfRealElement();
    for(word i=0; i<nre; i++)
        nfv += variables[i].getDimension();
    return nff + nfv;
}


//##ModelId=3DA3E5C00046
word SDFBVBlock::getMaxDimension()
{
    word nfv = 0;
    word nff = fixed.getDimension();
    word ne = fixed.getMaxNumberOfElement();
    for(word i=0; i<ne; i++)
        nfv += variables[i].getDimension();
    return nff + nfv;

}


//##ModelId=3DA3E5C00082
bool SDFBVBlock::setOutputStream(ByteStream* os, word first)
{
    fixed.setOutputStream(os, first);
    word nrb = fixed.getNumberOfRealElement();
    word start = first + fixed.getDimension();
    for(word i = 0; i < nrb; i++)
    {
        variables[i].setOutputStream(os, start);
        start += variables[i].getDimension();
    }
    return true;
}


//##ModelId=3DA3E5C0026C
ByteStream*  SDFBVBlock::generateStream(bool bigendian)
{
    fixed.generateStream(bigendian);
    word nrb = fixed.getNumberOfRealElement();
    for(word i = 0; i < nrb; i++)
    {
        variables[i].generateStream(bigendian);
    }
    return outputstream;
}

word  SDFBVBlock::getNumberOfRealElement() {
	return fixed.getNumberOfRealElement();
}


void  SDFBVBlock::setNumberOfRealElement(word value) {
	fixed.setNumberOfRealElement(value);
}	

word  SDFBVBlock::getMaxNumberOfElements() {
	return fixed.getMaxNumberOfElement();
}

SDFBVBlockFixed* SDFBVBlock::getFixedPart() {
	return &fixed;
}
	
SDFBVBlockVariable* SDFBVBlock::getElement(word nelement) {
	if(nelement < fixed.getNumberOfRealElement())
		return &variables[nelement];
	return 0;

}
