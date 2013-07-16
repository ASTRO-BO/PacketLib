#include "Output.h"

using namespace PacketLib;

//##ModelId=3DA3E57C0082
Output::Output(bool bigendian)
{
    isclosed = true;
    this->bigendian = bigendian;
}


bool Output::isClosed()
{
    return isclosed;
}


//##ModelId=3DBFBFBF01CC
bool Output::isBigendian()
{
    return bigendian;
}
