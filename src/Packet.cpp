/***************************************************************************
                          Packet.cpp  -  description
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001, 2013 by Andrea Bulgarelli
    email                : bulgarelli@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/
 
#include "Packet.h"
#include "Field.h"
#include "PacketLibDemo.h"

using namespace PacketLib;


Packet::Packet(bool bigendian)
{
    header = (PacketHeader*) new PacketHeader();
    dataField = (PacketDataField*) new PacketDataField();
    name = 0;
//    tail = new PartOfPacket();
    number_of_identifier = 0;
    identifiers = 0;
    this->bigendian = bigendian;
    /// temp
    tempHeader = ByteStreamPtr(new ByteStream);
    tempDataField = ByteStreamPtr(new ByteStream);
    tempDataFieldHeader = ByteStreamPtr(new ByteStream);
    tempPacketDataField = ByteStreamPtr(new ByteStream);
    tempTail = ByteStreamPtr(new ByteStream);
    first_output_stream_setted = false;

}



Packet::~Packet()
{
    PRINTDEBUG("Delete Packet " << name << "-----");
    delete header;
    header = 0;
    delete dataField;
    dataField = 0;
    for(unsigned i = 0; i < number_of_identifier; i++)
        delete identifiers[i];
    delete[] identifiers;
}



bool Packet::createPacketType(char* fileName, bool isprefix, word dimprefix) throw (PacketException*)
{
    DEMORET0;
    ConfigurationFile file;
    char* line;
    char **argv = new char* [1];
    argv[0] = fileName;
    this->filename = fileName;

    thereisprefix = isprefix;
    dimPrefix = dimprefix;

    try
    {
        if(file.open(argv))
        {
            delete[] argv;
            file.setpos(0);
            /// retrieve name of packet header
            name = file.getLine();
            /// find the PacketHeader section
            line=file.getLine("[PacketHeader]");
            if(strlen(line) != 0)
            {
                /// delete[] line;
                PRINTDEBUG("Found [PacketHeader]");
                line = file.getLine();
                if(header->loadHeader(line))
                {
                    /// delete[] line;
                    /// find the DataFieldHeader section
                    line=file.getLine("[DataFieldHeader]");
                    if(strlen(line) != 0)
                    {
                        /// delete[] line;
                        /// section found
                        if(dataField->dataFieldHeader->loadFields(file))
                        {
                            //cout << (dataField->dataFieldHeader->printStructure())->c_str();
                            line=file.getLastLineRead();
                            char *typeOfPacket = 0;
                            if(strcmp(line, "[SourceDataField]") == 0)
                            {
                                /// delete[] line;
                                /// determination of the source data field type
                                char *block = file.getLine();
                                bool section_found = false;
                                if(strcmp(block, "noblock") == 0)
                                {
                                    typeOfPacket = file.getLine();
                                    if(strcmp(typeOfPacket, "fixed") == 0)
                                        dataField->sourceDataField = (SDFNoBlockFixed*) new SDFNoBlockFixed();
                                    else
                                    {
                                        /*if(strcmp(typeOfPacket, "variable") == 0)
                                            dataField->sourceDataField = (SDFNoBlockVariable*) new SDFNoBlockVariable();
                                        else*/
                                        throw new PacketExceptionFileFormat("It's impossibile to identify the type of source data field. Expected fixed or variable keyword.");
                                    }
                                    section_found = true;
                                }
                                if(strcmp(block, "block") == 0)
                                {
                                    typeOfPacket = file.getLine();
                                    if(strcmp(typeOfPacket, "fixed") == 0)
                                        dataField->sourceDataField = (SDFBlockFixed*) new SDFBlockFixed();
                                    else
                                    {
                                        if(strcmp(typeOfPacket, "variable") == 0)
                                            dataField->sourceDataField = (SDFBlockVariable*) new SDFBlockVariable();
                                        else
                                            throw new PacketExceptionFileFormat("It's impossibile to identify the type of source data field. Expected fixed or variable keyword.");
                                    }
                                    section_found = true;
                                }
                                if(strcmp(block, "rblock") == 0)
                                {
                                    dataField->sourceDataField = (SDFRBlock*) new SDFRBlock(dataField->dataFieldHeader);
                                    section_found = true;
                                }
                                if(!section_found)
                                    throw new PacketExceptionFileFormat("It's impossibile to identify the type of source data field. Expected block, noblock or rblock keyword.");

                                //delete[] block;
                                //delete[] typeOfPacket;

                                if(dataField->sourceDataField->loadFields(file))
                                {
                                    //cout << (dataField->sourceDataField->printStructure())->c_str();
                                    line=file.getLastLineRead();
                                    if(strcmp(line, "[Identifiers]") == 0)
                                    {
                                        /// section found
                                        if(loadIdentifiers(file))
                                        {

                                            line = file.getLastLineRead();
                                            /// Loading of the tail section
                                            if(strcmp(line, "[Tail]") == 0)
                                            {
                                                if(!dataField->tail->loadFields(file))
                                                {
                                                    throw new PacketExceptionFileFormat("Error in [Tail] section");
                                                }
                                            }
                                            //TODO: chiudere il file anche negli altri casi
                                            file.close();
                                            /// Memory allocation for the output stream
                                            dword dimpo = getMaxDimension();
                                            dword dimpr = (isprefix?dimprefix:0);
                                            packet_output = ByteStreamPtr(new ByteStream(dimpo + dimpr, bigendian));

                                            file.close();
                                            return true;
                                        }
                                        else
                                            return false;
                                    }
                                    else
                                    {
                                        throw new PacketExceptionFileFormat("Identifiers section not found");
                                    }
                                }
                                else
                                {
                                    return false;
                                }
                            }
                            else
                            {
                                /// section not found
                                throw new PacketExceptionFileFormat("SourceDataField section not found");
                            }
                        }
                        else
                        {
                            return false;
                        };
                    }
                    else
                    {
                        /// section not found
                        throw new PacketExceptionFileFormat("DataFieldHeader section not found");
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                throw new PacketExceptionFileFormat("Packet header section not found");
            }
        }
        else
        {
            delete[] argv;
            throw new PacketExceptionIO("File packet not opened.");
        }

        return true;
    }
    catch(PacketException* e)
    {
        e->add(": ");
        e->add(fileName);
        throw e;
    }
}





bool Packet::loadIdentifiers(ConfigurationFile& fp)
{

    type_of_identifier[0] = false;
    type_of_identifier[1] = false;


    type_of_identifier[2] = false;
    number_of_identifier = 0;

    MemoryBuffer* buffer = new MemoryBuffer();
    char* line = fp.getLine();
    while(strcmp(line, "[Tail]") != 0)
    {
        buffer->setbuffer(line);
        line = fp.getLine();
        bool eof = fp.isEOF();
        if(eof == true || line[0] == 0)
        	break;
    }
    ///delete[] line; 
    //AB
    number_of_identifier = buffer->getBufferDimension()/3;
    if(number_of_identifier != 0)
    {
        identifiers = new PacketIdentifier* [number_of_identifier];
        int nf;
        byte type;
        word v;
        for(unsigned i=0; i< number_of_identifier; i++)
        {
            nf = atoi(buffer->getbuffer());
            type = atoi(buffer->getbuffer());
            v = Utility::convertToInteger(buffer->getbuffer());
            type_of_identifier[type] = true;
            PacketIdentifier* p = new PacketIdentifier(nf, type, v);
            identifiers[i] = p;
        }
    }
    //delete buffer;
    return true;
}



void Packet::printIdentifiers()
{
    /// Create constant iterator for list.
    /// list<PacketIdentifier>::iterator iter;
    /// Iterate through list and output each element.
    /// for (iter=identifiers.begin(); iter != identifiers.end(); iter++)
    for(unsigned i = 0; i< number_of_identifier; i++)
    {

        //Tstatic bool first = false;ODO
        //PacketIdentifier f = (PacketIdentifier) *iter;
        //cout << "fieldNumber: " << f.fieldNumber << " - type: " << (int)f.type << " - value: " << f.value << endl;
    }
}


bool Packet::setPacketValue(ByteStreamPtr prefix, ByteStreamPtr packetHeader, ByteStreamPtr packetDataField, bool onlySections)
{
    //cout << "@ " << packetDataField->getDimension() << endl;
    memByteStream(prefix, packetHeader, packetDataField);
    ByteStreamPtr packet = ByteStreamPtr(new ByteStream(packetHeader, packetDataField, 0));
    memByteStream(prefix, packet);
    /// 1)
    if(!setPacketValueVerify(prefix, packetHeader, packetDataField))
    {
        PRINTERROR("Error in packet value verify");
        return false;
    }
    /// 2)
    if(!setPacketValuePrefix(prefix))
    {
        PRINTERROR("Error in set packet value prefix");
        return false;
    }
    /// 3)
    if(!setPacketValueHeader(packetHeader))
    {
        PRINTERROR("Error in set packet value header");
        return false;
    }
    /// 4)
    if(!setPacketValueDataFieldHeader(packetDataField))
    {
        PRINTERROR("Error in set packet value data field header");
        return false;
    }
    /// 5)
    if(!setPacketValueSourceDataField(packetDataField, onlySections))
    {
        PRINTERROR("Error in set packet value source data field");
        return false;
    }
    /// 6)
    if(!setPacketValueTail(packetDataField))
    {
        PRINTERROR("Error in set packet value tail");
        return false;
    }
    /// 7) end
    return true;
}



bool Packet::setPacketValue(ByteStreamPtr prefix, ByteStreamPtr packet, bool onlySections)
{
    dword dimHeader = header->getDimension();
    memByteStream(prefix, packet);
    tempHeader->setStream(packet, 0, dimHeader-1);
    tempDataField->setStream(packet, dimHeader, packet->getDimension());
    return setPacketValue(prefix, tempHeader, tempDataField, onlySections);
}



bool Packet::verifyPacketValue(ByteStreamPtr prefix, ByteStreamPtr packet)
{
    dword dimHeader = header->getDimension();
    memByteStream(prefix, packet);
    tempHeader->setStream(packet, 0, dimHeader-1);
    tempDataField->setStream(packet, dimHeader, packet->getDimension());
    return verifyPacketValue(prefix, tempHeader, tempDataField);
}



bool Packet::verifyPacketValue(ByteStreamPtr prefix, ByteStreamPtr packetHeader, ByteStreamPtr packetDataField)
{
    bool verified = true;
    memByteStream(prefix, packetHeader, packetDataField);
    if(type_of_identifier[2] == true)
    {
        if(!setPacketValue(prefix, packetHeader, packetDataField))
        {
            return false;
        }
    }
    else
    {
        if(!setPacketValueVerify(prefix, packetHeader, packetDataField))
            return false;
        if(type_of_identifier[1] == true)
        {
            if(!setPacketValueDataFieldHeader(packetDataField))
                return false;
        }
        if(type_of_identifier[0] == true)
            if(!setPacketValueHeader(packetHeader))
                return false;

        if(!setPacketValuePrefix(prefix))
            return false;


    }
    ///  Iterate through list and verify each element.

    for(unsigned i = 0; i< number_of_identifier; i++)
    {
        PacketIdentifier* pi = identifiers[i];
        Field* f;
        switch(pi->type)
        {
        case 0:
            f = header->getFields(pi->fieldNumber);
            break;
        case 1:
            f = dataField->dataFieldHeader->getFields(pi->fieldNumber);
            break;
        case 2:

            f = dataField->sourceDataField->getFields(pi->fieldNumber);
            break;
        }
        if(f->value != pi->value)
        {
            verified = false;
            break;
        }
    }
    if(verified==false)
        return false;
    else
        return true;
}


bool Packet::setAndVerifyPacketValue(ByteStreamPtr prefix, ByteStreamPtr packet)
{
    dword dimHeader = header->getDimension();
    memByteStream(prefix, packet);
    tempHeader->setStream(packet, 0, dimHeader-1);
    tempDataField->setStream(packet, dimHeader, packet->getDimension());
    return setAndVerifyPacketValue(prefix, tempHeader, tempDataField);
}


bool Packet::setAndVerifyPacketValue(ByteStreamPtr prefix, ByteStreamPtr packetHeader, ByteStreamPtr packetDataField)
{
    memByteStream(prefix, packetHeader, packetDataField);
    ByteStreamPtr packet = ByteStreamPtr(new ByteStream(packetHeader, packetDataField, 0));
    memByteStream(prefix, packet);
    if(verifyPacketValue(prefix, packetHeader, packetDataField)==false)
    {
        PRINTERROR("Error in verify packet value");
        return false;
    }
    // se arrivo qui, allora devo settare il resto
    if(type_of_identifier[2] == false)
    {

        if(type_of_identifier[0] == false)
        {
            if(!setPacketValueHeader(packetHeader))
            {
                PRINTERROR("Error in set packet value header");
                return false;
            }
        }



        if(type_of_identifier[1] == false)
        {
            if(!setPacketValueDataFieldHeader(packetDataField))
            {
                PRINTERROR("Error in set packet value data field header");
                return false;
            }
        }

        if(!setPacketValueSourceDataField(packetDataField))
        {
            PRINTERROR("Error in set packet value source data field");
            return false;
        }

        if(!setPacketValueTail(packetDataField))
        {
            PRINTERROR("Error in set packet value tail");
            return false;
        }

    }
    return true;

}



void Packet::printPacketValue()
{
    char** pr;
    pr = (char**) header->printValue();
    for(int i = 0; pr[i] != 0; i++)
        cout << pr[i] << endl;
    //delete pr;
    pr = (char**) dataField->dataFieldHeader->printValue();
    for(int i = 0; pr[i] != 0; i++)
        cout << pr[i] << endl;
    //delete pr;
    pr = (char**) dataField->sourceDataField->printValue();
    for(int i = 0; pr[i] != 0; i++)
        cout << pr[i] << endl;
    if(dataField->tail->getDimension() != 0)
    {
        pr = (char**) dataField->tail->printValue();
        for(int i = 0; pr[i] != 0; i++)
            cout << pr[i] << endl;
    }

}



dword Packet::getDimension()
{
    return header->getDimension() + dataField->getDimension();
}


dword Packet::getMaxDimension()
{
    dword dimh = header->getDimension();
    dword dimdf = dataField->getMaxDimension();
    return dimh + dimdf;
}


void Packet::generateStream()
{
    word dimHeader = header->getDimension();

    if(first_output_stream_setted == false)
    {
        //	header->setOutputStream(packet_output, 0);
        first_output_stream_setted = true;
    }
    //TODO: richiamarlo quando  un block se first_output_stream_setted == true
    if(dataField->sourceDataField->get_reset_output_stream())
    {
        header->setOutputStream(packet_output, thereisprefix?dimPrefix:0);
        dataField->setOutputStream(packet_output, dimHeader + (thereisprefix?dimPrefix:0));

        dataField->sourceDataField->set_reset_output_stream(false);
    }

    /// PACKET DIMENSIONE MANAGEMENT
    header->setPacketLength(dataField->getDimension());
    //Field* f = header->getFieldWithPacketDimension();
    //f->value = dataField->getDimension() - 1;

    header->generateStream(bigendian);
    dataField->generateStream(bigendian);
}



bool Packet::setPacketValueVerify(ByteStreamPtr prefix, ByteStreamPtr packetHeader, ByteStreamPtr packetDataField)
{
    /// 1) Checking
    /// First check: pointers control
    if(packetHeader == NULL || packetDataField == NULL)
        return false;
    /// Second check: dimension control
    if(header->getDimension() != packetHeader->getDimension())
        return false;
    return true;
}



bool Packet::setPacketValuePrefix(ByteStreamPtr prefix)
{
    //2) prefix
    this->prefix = prefix;
    return true;
}



bool Packet::setPacketValueDataFieldHeader(ByteStreamPtr packetDataField)
{
    bool b;
    dword packetLength;
    /// 4) data field header
    packetLength = dataField->dataFieldHeader->getDimension();
    /// Reading and setting the data field header
    b = tempDataFieldHeader->setStream(packetDataField, 0, packetLength-1);
    /// It releases the memory from b only if it goes wrong
    if(b)
    {
        return dataField->dataFieldHeader->setByteStream(tempDataFieldHeader);
    }
    else
        return false;
}


bool Packet::setPacketValueSourceDataField(ByteStreamPtr packetDataField, bool onlySections)
{
    bool b;
    dword packetLength;
    dword packetLength2;

    /// 5) source data field

    /// If necessary, it sets the number of real blocks present
    if(dataField->sourceDataField->isBlock())
    {
        dword  nrd = dataField->getNumberOfRealDataBlock();
        dataField->sourceDataField->setNumberOfRealDataBlock(nrd);
    }
    /*if(dataField->sourceDataField->isRBlock()) {
      word nrd = dataField->sourceDataField->getNumberOfRealDataBlock();
      dataField->sourceDataField->setNumberOfRealDataBlock(nrd);
    }*/


    packetLength = dataField->dataFieldHeader->getDimension();
    dword pl1 = header->getPacketLength();
    dword pl3 = dataField->dataFieldHeader->getDimension();
    dword pl4 = dataField->tail->getDimension();
    packetLength2 = pl1 - pl3 -pl4;
    b = tempPacketDataField->setStream(packetDataField, packetLength, packetLength+packetLength2-1);
    if(b)
    {
        bool ret = dataField->sourceDataField->setByteStream(tempPacketDataField, onlySections);
        //word nrd = dataField->sourceDataField->getNumberOfRealDataBlock();
        return ret;
    }
    else
        return false;



}

bool Packet::setPacketValueTail(ByteStreamPtr packetDataField)
{
    bool b;
    dword s, e;
    if(dataField->tail->getDimension() == 0)
        return true;
    /* NON CANCELLLARE: questo codice sotto funziona bene. Si utilizza
    l'altro solo perche' si suppone che il tail sia sempre posizionato alla fine
    del packet
    word s1 = dataField->dataFieldHeader->getDimension();
    word s2 = dataField->sourceDataField->getDimension();
    s = s1 + s2;
    e = s  + dataField->tail->getDimension() - 1;
    */
    s = packetDataField->getDimension() - dataField->tail->getDimension();
    e = packetDataField->getDimension() - 1;
    b = tempTail->setStream(packetDataField, s, e);
    if(b)
        return dataField->tail->setByteStream(tempTail);
    else
        return false;
}




bool Packet::setPacketValueHeader(ByteStreamPtr packetHeader)
{
    /// 3) Header
	/// Reading and setting the packet header
    if(!header->setByteStream(packetHeader))
        return false;
    else
        return true;
}

void Packet::memByteStream(ByteStreamPtr prefix, ByteStreamPtr packet)
{
    this->prefix = prefix;
    this->packet = packet;
}



void Packet::memByteStream(ByteStreamPtr prefix, ByteStreamPtr packetHeader, ByteStreamPtr packetDataField)
{
    this->prefix = prefix;
    //this->packet = 0;
    this->header->memByteStream(packetHeader);
    this->dataField->memByteStream(packetDataField);
}



ByteStreamPtr Packet::getOutputStream()
{
    generateStream();
    ByteStreamPtr b = ByteStreamPtr(new ByteStream(packet_output->stream, getDimension() + (thereisprefix?dimPrefix:0), bigendian));
    return b;
}

ByteStreamPtr Packet::getInputStream()
{
    if(packet == 0)
        packet = ByteStreamPtr(new ByteStream(header->getByteStream(), dataField->getByteStream(), 0));
    return packet;
}



const byte& Packet::getPacketID()
{
    return packetID;
}


void Packet::setPacketID( const byte& _newVal)
{
    packetID = _newVal;
}


bool Packet::thereIsPrefix()
{
    return thereisprefix;
}

char* Packet::printPrefixStream()
{
    if(prefix)
        return prefix->printStreamInHexadecimal();
    else
        return 0;
}

char** Packet::printHeaderValue()
{
    return (char**) header->printValue();
}

char* Packet::printHeaderStream()
{
    return (char*)header->getByteStream()->printStreamInHexadecimal();
}

char** Packet::printDataFieldHeaderValue()
{
    return (char**) dataField->dataFieldHeader->printValue();
}

char* Packet::printDataFieldHeaderStream()
{
    return (char*)dataField->dataFieldHeader->getByteStream()->printStreamInHexadecimal();
}

char** Packet::printSourceDataFieldValue()
{
    return (char**)dataField->sourceDataField->printValue();
}

char* Packet::printSourceDataFieldStream()
{
    return (char*)dataField->sourceDataField->printInHexadecimal();
}

char** Packet::printTailValue()
{
    if(dataField->tail->getDimension() != 0)
        return (char**)dataField->tail->printValue();
    else
        return 0;
}

char* Packet::printTailStream()
{
    if(dataField->tail->getDimension() != 0)
        return dataField->tail->getByteStream()->printStreamInHexadecimal();

    else
        return 0;
}

char* Packet::printPacketOutputStream()
{
    dword dim = getDimension();
    if(thereisprefix)
        dim += dimPrefix;
    ByteStream b(packet_output->stream, dim, bigendian);
    char* c = b.printStreamInHexadecimal();
    return c;
}

bool Packet::verifyPacketValue(byte* stream) {


	dword dimPre = 0;
	if(thereisprefix)
	        dimPre += dimPrefix;
	ByteStreamPtr prefix = ByteStreamPtr(new ByteStream(stream, dimPre, bigendian));

	dword dim = 0;
	dword dimHeader = header->getDimension();
	dim += dimHeader;
	tempHeader->setStream(stream+dimPre, dimHeader, bigendian);
	header->setByteStream(tempHeader);
	dim += header->getDimensionOfPacketLength() + 1;
	ByteStreamPtr packet = ByteStreamPtr(new ByteStream(stream+dimPre, dim, bigendian));

	return verifyPacketValue(prefix, packet);
}

bool Packet::setPacketValue(byte* stream, bool onlySections) {
	dword dimPre = 0;
	if(thereisprefix)
			dimPre = dimPrefix;
	ByteStreamPtr prefix = ByteStreamPtr(new ByteStream(stream, dimPre, bigendian));

	dword dim = 0;
	dword dimHeader = header->getDimension();
	dim += dimHeader;
	tempHeader->setStream(stream+dimPre, dimHeader, bigendian);
	header->setByteStream(tempHeader);
	dim += header->getPacketLength() + 1;
	ByteStreamPtr packet = ByteStreamPtr(new ByteStream(stream+dimPre, dim, bigendian));

	return setPacketValue(prefix, packet, onlySections);

}
