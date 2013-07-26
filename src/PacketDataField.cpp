#include "PacketDataField.h"

using namespace PacketLib;

//##ModelId=3DA3E5A4033E
PacketDataField::PacketDataField() : PartOfPacket("Packet Data Field")
{
    dataFieldHeader = (DataFieldHeader*) new DataFieldHeader();
    tail = new PartOfPacket();
    sourceDataField = 0;
};

//##ModelId=3DA3E5A4037A
PacketDataField::~PacketDataField()
{
    delete dataFieldHeader;
    delete sourceDataField;
    delete tail;
}


//##ModelId=3DA3E5A500D2
dword PacketDataField::getDimension()
{
    if(sourceDataField != 0)
        return dataFieldHeader->getDimension() + sourceDataField->getDimension() + tail->getDimension();
    else
        return dataFieldHeader->getDimension() + tail->getDimension();
}


//##ModelId=3DA3E5A5010E
dword PacketDataField::getMaxDimension()
{
    if(sourceDataField != 0)
        return dataFieldHeader->getDimension() + sourceDataField->getMaxDimension() + tail->getDimension();
    else
        return dataFieldHeader->getDimension() + tail->getDimension();
}


//##ModelId=3DA3E5A403AC
word PacketDataField::getNumberOfRealDataBlock()
{
    //nel caso del packet block, deve essere presente un campo in cui �indicato
    //il numero di blocchi presenti, solo se numero di blocchi fissi = false
    if(sourceDataField->isBlock())
    {
        if(!sourceDataField->isNumberOfBlockFixed())
        {
            word index = (sourceDataField)->getIndexOfNBlock();
            Field* f = dataFieldHeader->getFields(index);
            return (word) f->value + sourceDataField->getSubFromNBlock();
        }
        else
        {
            //se numero di blocchi fissi �true, allora si prende il max
            return sourceDataField->getMaxNumberOfBlock();
        }
    }

    return (word) 0;
}


//##ModelId=3DA3E5A50000
void PacketDataField::setNumberOfRealDataBlock(word number)
{
    if(number > sourceDataField->getMaxNumberOfBlock())
        number =  sourceDataField->getMaxNumberOfBlock();
    if(sourceDataField->isBlock())
    {
        //sourceDataField->getDimension();
        word index = sourceDataField->getIndexOfNBlock();
        //word index = dataFieldHeader->getIndexOfNBlock();
        Field* f = dataFieldHeader->getFields(index);
        f->value = number - sourceDataField->getSubFromNBlock();
        sourceDataField->setNumberOfRealDataBlock(number);
    }
}


//##ModelId=3DA3E5A5017C
bool PacketDataField::setOutputStream(ByteStream* os, word first)
{
    delete outputstream;
    outputstream = new ByteStream((os->stream + first), getDimension(), os->isBigendian());
    dataFieldHeader->setOutputStream(os, first);
    word sdfstart = first + dataFieldHeader->getDimension();
    sourceDataField->setOutputStream(os, sdfstart);
    word tailstart = sdfstart;
    if(sourceDataField != 0)
        tailstart += sourceDataField->getDimension();
    if(tail->getDimension() != 0)
        tail->setOutputStream(os, tailstart);
    return true;
}


//##ModelId=3DA3E5A60028
ByteStream* PacketDataField::generateStream(bool bigendian)
{
    dataFieldHeader->generateStream(bigendian);
    sourceDataField->generateStream(bigendian);
    tail->generateStream(bigendian);
    return outputstream;
}
