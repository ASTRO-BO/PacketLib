#include "OutputPacketStream.h"

using namespace PacketLib;

//##ModelId=3DBFBFC0007D
OutputPacketStream::OutputPacketStream() : PacketStream()
{
    out = 0;
}


//##ModelId=3DBFBFC000AA
OutputPacketStream::OutputPacketStream(const char* fileNameConfig) : PacketStream(fileNameConfig)
{
    out = 0;
}


//##ModelId=3DBFBFC000E6
bool OutputPacketStream::writePacket(Packet* p) throw(PacketExceptionIO*)
{
    ByteStream* bs;
    try
    {
        bs = p->getOutputStream();
        if(out == 0)
            throw new PacketExceptionIO("No output setted..");
        out->writeByteStream(bs);
        delete bs;
        return true;
    }
    catch(PacketExceptionIO* e)
    {
        e->add(" - ");
        e->add("OutputPacketStream::writePacket");
        throw e;
    }
}


//##ModelId=3DBFBFC00118
void OutputPacketStream::setOutput(Output* out)
{
    this->out = out;
}
