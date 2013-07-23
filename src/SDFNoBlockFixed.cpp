#include "SDFNoBlockFixed.h"
#include "ConfigurationFile.h"

using namespace PacketLib;

//##ModelId=3C357A480024
SDFNoBlockFixed::SDFNoBlockFixed() : SourceDataField("SDF NoBlock Fixed")
{
    fixed = true;
    isblock = false;
    rblock = false;
}


//##ModelId=3C357A4F028B
SDFNoBlockFixed::~SDFNoBlockFixed()
{
}


//##ModelId=3A5D82EC0030
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


//##ModelId=3DA3E5F40136
Field* SDFNoBlockFixed::getFields(word index)
{
    return PartOfPacket::getFields(index);
};

//##ModelId=3DA3E5F40320
word SDFNoBlockFixed::getFieldValue(word index)
{
    return PartOfPacket::getFieldValue(index);
}

//##ModelId=3DA3E5F5019A
void SDFNoBlockFixed::setFieldValue(word index, word value)
{
    PartOfPacket::setFieldValue(index, value);
}

//##ModelId=3DA3E5F60154

dword SDFNoBlockFixed::getMaxDimension()
{
    return getDimension();
}
