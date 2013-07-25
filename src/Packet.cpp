#include "Packet.h"
#include "Field.h"
#include "PacketLibDemo.h"

using namespace PacketLib;

//##ModelId=3C0F6C1A0187
Packet::Packet(bool bigendian) {
    header = (PacketHeader*) new PacketHeader();
    dataField = (PacketDataField*) new PacketDataField();
    name = 0;
    prefix = 0;
//    tail = new PartOfPacket();
    number_of_identifier = 0;
    identifiers = 0;
    prefix = 0;
    packet = 0;
    packet_output = 0;
    this->bigendian = bigendian;
    //temp
    tempHeader = new ByteStream();
    tempDataField = new ByteStream();
    tempDataFieldHeader = new ByteStream();
    tempPacketDataField = new ByteStream();
    tempTail = new ByteStream();
    first_output_stream_setted = false;

}


//##ModelId=3DA3E5830032
Packet::~Packet() {
	  PRINTDEBUG("Delete Packet " << name << "-----");
    delete header; header = 0;
    delete dataField; dataField = 0;
    delete[] name; name = 0;
    for(unsigned i = 0; i < number_of_identifier; i++)
        delete identifiers[i];
    delete[] identifiers;
    delete packet_output; packet_output = 0;
    delete tempHeader; tempHeader = 0;
    delete tempDataField;  tempDataField = 0;
    //ANDREA: ricordato di indagare perch�non si riesce ad effettuare il delete
    delete tempDataFieldHeader; tempDataFieldHeader = 0;
    delete tempPacketDataField; tempPacketDataField = 0;
    delete tempTail; tempTail = 0;
}


//##ModelId=3C14BA710151
bool Packet::createPacketType(char* fileName, bool isprefix, word dimprefix) throw (PacketException*) {
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
            //retrieve name of packet header
            name = file.getLine();
            //find the PacketHeader section
            line=file.getLine("[PacketHeader]");
            if(strlen(line) != 0)
            {
                //delete[] line;
                PRINTDEBUG("Found [PacketHeader]");
                line = file.getLine();
                if(header->loadHeader(line))
                {
                    //delete[] line;
                    //find the DataFieldHeader section
                    line=file.getLine("[DataFieldHeader]");
                    if(strlen(line) != 0)
                    {
                        //delete[] line;
                        //section found
                        if(dataField->dataFieldHeader->loadFields(file))
                        {
                            //cout << (dataField->dataFieldHeader->printStructure())->c_str();
                            line=file.getLastLineRead();
                            char *typeOfPacket = 0;
                            if(strcmp(line, "[SourceDataField]") == 0)
                            {
                                //delete[] line;
                                //determinazione del tipo di source data field
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

                                delete[] block;
                                delete[] typeOfPacket;

                                if(dataField->sourceDataField->loadFields(file))
                                {
                                    //cout << (dataField->sourceDataField->printStructure())->c_str();
                                    line=file.getLastLineRead();
                                    if(strcmp(line, "[Identifiers]") == 0)
                                    {
                                        //section found
                                        if(loadIdentifiers(file))
                                        {

                                            line = file.getLastLineRead();
                                            //Caricamento della sezione tail
                                            if(strcmp(line, "[Tail]") == 0) {
                                              if(!dataField->tail->loadFields(file)) {
                                                	throw new PacketExceptionFileFormat("Error in [Tail] section");
						}
                                            }                  
                                            //TODO: chiudere il file anche negli altri casi
                                            file.close();
                                            //allocate memory for output stream
                                            dword dimpo = getMaxDimension();
                                            dword dimpr = (isprefix?dimprefix:0);
                                            packet_output = new ByteStream(dimpo + dimpr, bigendian);

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
                                //section not found
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
                        //section not found
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



//##ModelId=3C1877510044

bool Packet::loadIdentifiers(ConfigurationFile& fp) {

    type_of_identifier[0] = false;
    type_of_identifier[1] = false;


    type_of_identifier[2] = false;
    number_of_identifier = 0;

    MemoryBuffer* buffer = new MemoryBuffer();
    char* line = fp.getLine();
    while(!fp.isEOF() && strcmp(line, "[Tail]") != 0)
    {
        buffer->setbuffer(line);
        line = fp.getLine();
    }
    //delete[] line; //AB
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
    delete buffer;
    return true;
}


//##ModelId=3C187751008D
void Packet::printIdentifiers() {
    // Create constant iterator for list.
    //list<PacketIdentifier>::iterator iter;
    // Iterate through list and output each element.
    //for (iter=identifiers.begin(); iter != identifiers.end(); iter++)
    for(unsigned i = 0; i< number_of_identifier; i++)
    {

        //Tstatic bool first = false;ODO
        //PacketIdentifier f = (PacketIdentifier) *iter;
        //cout << "fieldNumber: " << f.fieldNumber << " - type: " << (int)f.type << " - value: " << f.value << endl;
    }
}


//##ModelId=3C301E890023
bool Packet::setPacketValue(ByteStream* prefix, ByteStream* packetHeader, ByteStream* packetDataField) {
	cout << "@ " << packetDataField->getDimension() << endl;
    memByteStream(prefix, packetHeader, packetDataField);
    ByteStream* packet = new ByteStream(packetHeader, packetDataField, 0);
    memByteStream(prefix, packet);
    //1)
    if(!setPacketValueVerify(prefix, packetHeader, packetDataField)) {
    	PRINTERROR("Error in packet value verify");
        return false;
    }
    //2)
    if(!setPacketValuePrefix(prefix)) {
    	PRINTERROR("Error in set packet value prefix");
        return false;
    }
    //3)
    if(!setPacketValueHeader(packetHeader)) {
        PRINTERROR("Error in set packet value header");
        return false;
    }
    //4)
    if(!setPacketValueDataFieldHeader(packetDataField)) {
        PRINTERROR("Error in set packet value data field header");
        return false;
    }
    //5)
    if(!setPacketValueSourceDataField(packetDataField)) {
        PRINTERROR("Error in set packet value source data field");
        return false;
    }
    //6)
    if(!setPacketValueTail(packetDataField)) {
    	PRINTERROR("Error in set packet value tail");
        return false;
    }
    //7) fine
    return true;
}


//##ModelId=3DA3E5890136
bool Packet::setPacketValue(ByteStream* prefix, ByteStream* packet) {
    dword dimHeader = header->getDimension();
    memByteStream(prefix, packet);
    tempHeader->setStream(packet, 0, dimHeader-1);
    tempDataField->setStream(packet, dimHeader, packet->getDimension());
    return setPacketValue(prefix, tempHeader, tempDataField);
}


//##ModelId=3DA3E58A0320
bool Packet::verifyPacketValue(ByteStream* prefix, ByteStream* packet) {
    dword dimHeader = header->getDimension();
    memByteStream(prefix, packet);
    tempHeader->setStream(packet, 0, dimHeader-1);
    tempDataField->setStream(packet, dimHeader, packet->getDimension());
    return verifyPacketValue(prefix, tempHeader, tempDataField);
}


//##ModelId=3DA3E58C00AA
bool Packet::verifyPacketValue(ByteStream* prefix, ByteStream* packetHeader, ByteStream* packetDataField) {
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
    // Iterate through list and verify each element.

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


//##ModelId=3DA3E58600B4
bool Packet::setAndVerifyPacketValue(ByteStream* prefix, ByteStream* packet) {
    dword dimHeader = header->getDimension();
    memByteStream(prefix, packet);
    tempHeader->setStream(packet, 0, dimHeader-1);
    tempDataField->setStream(packet, dimHeader, packet->getDimension());
    return setAndVerifyPacketValue(prefix, tempHeader, tempDataField);
}


//##ModelId=3DA3E5840212
bool Packet::setAndVerifyPacketValue(ByteStream* prefix, ByteStream* packetHeader, ByteStream* packetDataField) {
    memByteStream(prefix, packetHeader, packetDataField);
    ByteStream* packet = new ByteStream(packetHeader, packetDataField, 0);
    memByteStream(prefix, packet);    
    if(verifyPacketValue(prefix, packetHeader, packetDataField)==false) {
        PRINTERROR("Error in verify packet value");
        return false;
    }
    //se arrivo qui, allora devo settare il resto
    if(type_of_identifier[2] == false)
    {

        if(type_of_identifier[0] == false)
        {
            if(!setPacketValueHeader(packetHeader)) {
	    	PRINTERROR("Error in set packet value header");
                return false;
	    }
        }



        if(type_of_identifier[1] == false)
        {
            if(!setPacketValueDataFieldHeader(packetDataField)) {
	        PRINTERROR("Error in set packet value data field header");
                return false;
	    }
        }

        if(!setPacketValueSourceDataField(packetDataField)) {
	    PRINTERROR("Error in set packet value source data field");
            return false;
	}
	    
	if(!setPacketValueTail(packetDataField)) {
	    PRINTERROR("Error in set packet value tail");
            return false;
	}

    }
    return true;

}


//##ModelId=3DA3E58E005A
void Packet::printPacketValue() {
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
    if(dataField->tail->getDimension() != 0) {
      pr = (char**) dataField->tail->printValue();
      for(int i = 0; pr[i] != 0; i++)
        cout << pr[i] << endl;      
    }
      
}


//##ModelId=3DA3E58E024E
dword Packet::getDimension() {
    return header->getDimension() + dataField->getDimension();
}


//##ModelId=3DA3E58E0398
dword Packet::getMaxDimension() {
    dword dimh = header->getDimension();
    dword dimdf = dataField->getMaxDimension();
    return dimh + dimdf;
}


//##ModelId=3DA3E590029E
void Packet::generateStream() {
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

	//PACKET DIMENSIONE MANAGEMENT
	header->setPacketLength(dataField->getDimension());
    //Field* f = header->getFieldWithPacketDimension();
    //f->value = dataField->getDimension() - 1;

    header->generateStream(bigendian);
    dataField->generateStream(bigendian);
}


//##ModelId=3DA3E59600DC
bool Packet::setPacketValueVerify(ByteStream* prefix, ByteStream* packetHeader, ByteStream* packetDataField) {
    //1) verifiche
    //prima verifica: controlli sui puntatori
    if(packetHeader == NULL || packetDataField == NULL)
        return false;
    //seconda verifica: controllo sulle dimensioni
    if(header->getDimension() != packetHeader->getDimension())
        return false;
    return true;
}


//##ModelId=3DA3E5940352
bool Packet::setPacketValuePrefix(ByteStream* prefix) {
    //2) prefix
    this->prefix = prefix;
    return true;
}


/** No descriptions */
//##ModelId=3DA3E599012C
bool Packet::setPacketValueDataFieldHeader(ByteStream* packetDataField) {
    bool b;
    dword packetLength;
    //4) data field header
    packetLength = dataField->dataFieldHeader->getDimension();
    //si legge e si setta il data field header
    b = tempDataFieldHeader->setStream(packetDataField, 0, packetLength-1);
    //libera la memoria da b solamente se va male
    if(b)
    {
        return dataField->dataFieldHeader->setByteStream(tempDataFieldHeader);
    }
    else
        return false;
}


//##ModelId=3DA3E59A033E
bool Packet::setPacketValueSourceDataField(ByteStream* packetDataField) {
    bool b;
    dword packetLength;
    dword packetLength2;

    //5) source data field

    //se necessario, si setta il numero di blocchi reali presenti
    if(dataField->sourceDataField->isBlock()) {
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
        bool ret = dataField->sourceDataField->setByteStream(tempPacketDataField);
        //word nrd = dataField->sourceDataField->getNumberOfRealDataBlock();
        return ret;
    }
    else
        return false;



}

bool Packet::setPacketValueTail(ByteStream* packetDataField) {
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



//##ModelId=3DA3E59C0172
bool Packet::setPacketValueHeader(ByteStream* packetHeader) {
    //3) header
    //si legge e si setta l'header del pacchetto
    if(!header->setByteStream(packetHeader))
        return false;
    else
        return true;
}


//##ModelId=3DA3E5900046
void Packet::deleteExternalByteStream() {
    if(prefix != 0)
        if(prefix->getMemAllocation())
    {
        delete prefix; prefix = 0;
    }
    if(packet !=0)
        if(packet->getMemAllocation())
    {
        delete packet; packet = 0;
    }
    if(dataField->stream != 0)
        if(dataField->stream->getMemAllocation())
    {
        delete dataField->stream; dataField->stream = 0;
    }
    if(header->stream != 0)
        if(header->stream->getMemAllocation())
    {
        delete header->stream; header->stream = 0;
    }
}


//##ModelId=3DA3E5A10140
void Packet::memByteStream(ByteStream* prefix, ByteStream* packet) {
    this->prefix = prefix;
    this->packet = packet;
}


//##ModelId=3DA3E59D038E
void Packet::memByteStream(ByteStream* prefix, ByteStream* packetHeader, ByteStream* packetDataField) {
    this->prefix = prefix;
    //this->packet = 0;   
    this->header->stream = packetHeader;
    this->dataField->stream = packetDataField;
}


//##ModelId=3DBFBFC003AC
ByteStream* Packet::getOutputStream() {
    generateStream();
    ByteStream* b = new ByteStream(packet_output->stream, getDimension() + (thereisprefix?dimPrefix:0), bigendian);
    return b;
}

ByteStream* Packet::getInputStream() {
	if(packet == 0)
		packet = new ByteStream(header->stream, dataField->stream, 0);
	return packet;
}


/** Read property of byte packetID. */
//##ModelId=3DBFBFC10370
const byte& Packet::getPacketID() {
    return packetID;
}


/** Write property of byte packetID. */
//##ModelId=3DBFBFC1006E
void Packet::setPacketID( const byte& _newVal) {
    packetID = _newVal;
}


//##ModelId=3DA3E5930280
bool Packet::thereIsPrefix() {
    return thereisprefix;
}

char* Packet::printPrefixStream() {
  if(prefix)
    return prefix->printStreamInHexadecimal();
  else
    return 0; 
}

char** Packet::printHeaderValue() {
    return (char**) header->printValue();
}

char* Packet::printHeaderStream() {
    return (char*)header->stream->printStreamInHexadecimal();
}

char** Packet::printDataFieldHeaderValue() {
  return (char**) dataField->dataFieldHeader->printValue();
}

char* Packet::printDataFieldHeaderStream() {
  return (char*)dataField->dataFieldHeader->stream->printStreamInHexadecimal();
}

char** Packet::printSourceDataFieldValue() {
  return (char**)dataField->sourceDataField->printValue();
}

char* Packet::printSourceDataFieldStream() {
  return (char*)dataField->sourceDataField->printInHexadecimal();
}

char** Packet::printTailValue() {
  if(dataField->tail->getDimension() != 0)
    return (char**)dataField->tail->printValue();
  else
    return 0;  
}

char* Packet::printTailStream() {
  if(dataField->tail->getDimension() != 0)
    return dataField->tail->stream->printStreamInHexadecimal();

  else
    return 0;
}

char* Packet::printPacketOutputStream() {
dword dim = getDimension();
if(thereisprefix)
	dim += dimPrefix;
ByteStream b(packet_output->stream, dim, bigendian);
char* c = b.printStreamInHexadecimal();
	return c;
}
