#include "PacketHeader.h"
#include "ConfigurationFile.h"

using namespace PacketLib;


//##ModelId=3DA3E5A701D6
PacketHeader::PacketHeader() : PartOfPacket("Packet Header")
{
    name = 0;
    dimensionOfPacketLenght = 16;
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
        //delete[] line;

        line = header.getLine();
        if(strcmp(line, "[Field]") == 0)
            dimensionOfPacketLenght = 16;
        else
            dimensionOfPacketLenght = atoi(line);

        if(!(dimensionOfPacketLenght == 16 || dimensionOfPacketLenght == 32))
            throw new PacketExceptionIO("Dimension of packet length, 16 or 32 bit");;

        header.setpos(0);

        //find the start position of the fields
        line = header.getLine("[Field]");
        //delete[] line;

        if(loadFields(header))
        {
            header.close();
            return true;
        }
        else
            throw new PacketExceptionIO("Can't create the header.");

    }
    else
    {
        delete[] argv;
        throw new PacketExceptionIO("Can't open the header file configuration.");
    }
}


//##ModelId=3C15ED930064
dword PacketHeader::getPacketLength()
{
    if(dimensionOfPacketLenght == 16)
    {
        Field* f = getFields(numberOfFieldWithPacketDimension);
        //standard ESA Nel packet lenght bisogna aggiungere 1
        return f->value + 1;
    }
    else
    {
        return getFieldValue_4_14(numberOfFieldWithPacketDimension) + 1;
    }
}

void PacketHeader::setPacketLength(dword dim)
{
    if(dimensionOfPacketLenght == 16)
    {
        Field* f = getFields(numberOfFieldWithPacketDimension);
        //standard ESA Nel packet lenght bisogna aggiungere 1
        f->value = (word) dim-1;
    }
    else
    {
        setFieldValue_4_14(numberOfFieldWithPacketDimension, dim-1);
    }
}


//##ModelId=3DA3E5A70208
Field * PacketHeader::getFieldWithPacketDimension()
{
    return getFields(numberOfFieldWithPacketDimension);
}
