#include "FileStream.h"

using namespace PacketLib;

//##ModelId=3C1877500365
FileStream::FileStream(bool prefix, bool bigen, word dimprefix, long startposition)
    : File(bigen, startposition)
{
    thereIsPrefix = prefix;
    dimPrefix = dimprefix;
}


//##ModelId=3C205AF20368
ByteStream* FileStream::readHeader(unsigned int dimHeader)
{
    header = getNByte(dimHeader);
    return header;
}


//##ModelId=3C205AF2036F
ByteStream* FileStream::readDataField(unsigned int dimDataField)
{
    dataField = getNByte(dimDataField);
    return dataField;
}


/** No descriptions */
//##ModelId=3C87744100F3
ByteStream* FileStream::readPrefix()
{
    if(thereIsPrefix)
        prefix = getNByte(dimPrefix);
    else
        prefix = 0;
    return prefix;
}
