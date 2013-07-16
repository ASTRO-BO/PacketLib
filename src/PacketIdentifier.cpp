#include "PacketIdentifier.h"

using namespace PacketLib;

//##ModelId=3C18775100C8
PacketIdentifier::PacketIdentifier(int fn, byte t, word v)
{
    fieldNumber = fn;
    type = t;
    value = v;
}


//##ModelId=3DA3E5A800F0
PacketIdentifier::~PacketIdentifier()
{
    //	cout << "Delete identifier" << endl;
}
