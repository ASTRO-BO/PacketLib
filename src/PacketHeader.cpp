#include "PacketHeader.h"
#include "ConfigurationFile.h"

using namespace PacketLib;


//##ModelId=3DA3E5A701D6
PacketHeader::PacketHeader() : PartOfPacket("Packet Header")
{
    name = 0;
}

//##ModelId=3DA3E5A7012C
PacketHeader::~PacketHeader()
{
    delete[] name;
}


//##ModelId=3C14980F00F2
bool PacketHeader::loadHeader(char* fileName) throw(PacketException*)
{
    ConfigurationFile header;
    char **argv = new char* [1];
    argv[0] = (char*)fileName;
    if(header.open(argv))
    {
        delete[] argv; 
        char* line = header.getLine();
        //retrieve name of packet header
        name = line;

        line = header.getLine();
        numberOfFieldWithPacketDimension = atoi(line);
        delete[] line; 

                                 //find the start position of the fields
        line = header.getLine("[Field]");
        delete[] line; 

        if(loadFields(header))
        {
            header.close();
            return true;
        }
        else
            throw new PacketExceptionIO("Can't create the header.");;

    }
    else {
    	delete[] argv; 
        throw new PacketExceptionIO("Can't open the header file configuration.");;
    }
}


//##ModelId=3C15ED930064
word PacketHeader::getPacketLength()
{
    Field* f = getFields(numberOfFieldWithPacketDimension);
    //standard ESA Nel packet lenght bisogna aggiungere 1
    return f->value + 1;
}




//##ModelId=3DA3E5A70208
Field * PacketHeader::getFieldWithPacketDimension()
{
    return getFields(numberOfFieldWithPacketDimension);
}
