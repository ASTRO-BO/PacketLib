/***************************************************************************
                          Packet.cpp  -  description
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001-2013 by Andrea Bulgarelli
                               2013-2014 by Andrea Bulgarelli, Andrea Zoli
    email                : bulgarelli@iasfbo.inaf.it, zoli@iasfbo.inaf.it
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

#define DECODETYPE 2

Packet::Packet(bool bigendian)
	: prefix(0), packet(0), stream(0), packetID(0), name(0), identifiers(0),
      number_of_identifiers(0), bigendian(bigendian), thereisprefix(false),
      filename(0), first_output_stream_setted(false), dimPrefix(0),
      dimPacketHeader(0), dimPacketDataFieldHeader(0),
      dimPacketSourceDataFieldFixed(0), dimPacketTail(0),
      dimPacketStartingFixedPart(0), decodedPacketHeader(false),
      decodedPacketDataFieldHeader(false), decodedPacketSourceDataField(false),
      decodedPacketTail(false), compressionAlgorithmsSection(0),
      compressionAlgorithmsIndex(0), compressionLevelSection(0),
      compressionLevelIndex(0), compressible(false)
{
    header = (PacketHeader*) new PacketHeader();
    dataField = (PacketDataField*) new PacketDataField();
    tempHeader = ByteStreamPtr(new ByteStream);
    tempDataField = ByteStreamPtr(new ByteStream);
    tempDataFieldHeader = ByteStreamPtr(new ByteStream);
    tempPacketDataField = ByteStreamPtr(new ByteStream);
    tempTail = ByteStreamPtr(new ByteStream);
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
					dimPacketHeader = header->size();
                    /// find the DataFieldHeader section
                    line=file.getLine("[DataFieldHeader]");
                    if(strlen(line) != 0)
                    {
                        /// delete[] line;
                        /// section found
                        if(dataField->getPacketDataFieldHeader()->loadFields(file))
                        {
							dimPacketDataFieldHeader = dataField->getPacketDataFieldHeader()->size();
                            //cout << (dataField->dataFieldHeader->printStructure())->c_str();
                            line=file.getLastLineRead();
                            if(strcmp(line, "[SourceDataField]") == 0)
                            {
                                /// determination of the source data field type
                                char *block = file.getLine();
                                bool section_found = false;
                                if(strcmp(block, "rblock") == 0)
                                {
                                    dataField->setPacketSourceDataField((SourceDataField*) new SourceDataField(dataField->getPacketDataFieldHeader()));
                                    section_found = true;
                                }
                                if(!section_found)
                                    throw new PacketExceptionFileFormat("It's impossibile to identify the type of source data field. Expected rblock keyword.");

                                if(dataField->getPacketSourceDataField()->loadFields(file))
                                {
                                    //cout << (dataField->sourceDataField->printStructure())->c_str();
									dimPacketSourceDataFieldFixed = dataField->getPacketSourceDataField()->sizeFixedPart();
									dimPacketStartingFixedPart = dimPacketHeader + dimPacketDataFieldHeader + dimPacketSourceDataFieldFixed;
									
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
                                                if(!dataField->getPacketTail()->loadFields(file))
                                                {
                                                    throw new PacketExceptionFileFormat("Error in [Tail] section");
                                                } else
												{
													dimPacketTail = dataField->getPacketTail()->size();
													line = file.getLastLineRead();
													if(strcmp(line, "[Compression]") == 0) {
														compressible = true;
														compressionAlgorithmsIndex = atoi(file.getLine());
														compressionAlgorithmsSection = atoi(file.getLine());
														compressionLevelIndex = atoi(file.getLine());
														compressionLevelSection = atoi(file.getLine());
													}
												}
                                            }
                                            //TODO: chiudere il file anche negli altri casi
                                            file.close();
                                            /// Memory allocation for the output stream
                                            dword dimpo = sizeMax();
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




bool Packet::setPacketValue(ByteStreamPtr prefix, ByteStreamPtr packetHeader, ByteStreamPtr packetDataField, int decodeType)
{

	if(decodeType == 0)
		return true;
	
    //cout << "@ " << packetDataField->size() << endl;
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
    if(!setPacketValueSourceDataField(packetDataField, decodeType))
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



bool Packet::verify()
{
    bool verified = true;
	
	ByteStreamPtr packetHeader = header->getByteStream();
	ByteStreamPtr packetDataField = dataField->getByteStream();
    
    if(type_of_identifier[2] == true)
    {
        if(!setPacketValue(prefix, packetHeader, packetDataField, DECODETYPE))
        {
            return false;
        }
    }
    else
    {
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
        Field* f = NULL;
        switch(pi->type)
        {
			case 0:
				f = header->getFields(pi->fieldNumber);
				break;
			case 1:
				f = dataField->getPacketDataFieldHeader()->getFields(pi->fieldNumber);
				break;
			case 2:
				
				f = dataField->getPacketSourceDataField()->getFields(pi->fieldNumber);
				break;
        }
        if(f == NULL || f->value != pi->value)
        {
            verified = false;
            break;
        }
    }
	return verified;
}



void Packet::printPacketValue()
{
    char** pr;
    pr = (char**) header->printValue();
    for(int i = 0; pr[i] != 0; i++)
        cout << pr[i] << endl;
    //delete pr;
    pr = (char**) dataField->getPacketDataFieldHeader()->printValue();
    for(int i = 0; pr[i] != 0; i++)
        cout << pr[i] << endl;
    //delete pr;
    pr = (char**) dataField->getPacketSourceDataField()->printValue();
    for(int i = 0; pr[i] != 0; i++)
        cout << pr[i] << endl;
    if(dataField->getPacketTail()->size() != 0)
    {
        pr = (char**) dataField->getPacketTail()->printValue();
        for(int i = 0; pr[i] != 0; i++)
            cout << pr[i] << endl;
    }

}



dword Packet::size()
{
	if(packet && !decodedPacketHeader) {
		setPacketValueHeader(getBSHeader());
		decodedPacketHeader = true;
		return dimPacketHeader + header->getPacketLength();
	}
	//return dimPacketHeader + header->getPacketLength();
	//else
	return header->size() + dataField->size();
}


dword Packet::sizeMax()
{
    dword dimh = dimPacketHeader;
    dword dimdf = dataField->sizeMax();
    return dimh + dimdf;
}


void Packet::generateStream()
{
    word dimHeader = header->size();

    if(first_output_stream_setted == false)
    {
        //	header->setOutputStream(packet_output, 0);
        first_output_stream_setted = true;
    }
    //TODO: richiamarlo quando  un block se first_output_stream_setted == true
    if(dataField->getPacketSourceDataField()->get_reset_output_stream())
    {
        header->setOutputStream(packet_output, thereisprefix?dimPrefix:0);
        dataField->setOutputStream(packet_output, dimHeader + (thereisprefix?dimPrefix:0));

        dataField->getPacketSourceDataField()->set_reset_output_stream(false);
    }

    /// PACKET DIMENSIONE MANAGEMENT
    header->setPacketLength(dataField->size());
    //Field* f = header->getFieldWithPacketDimension();
    //f->value = dataField->size() - 1;

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
    if(header->size() != packetHeader->size())
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
    /// Reading and setting the data field header
    b = tempDataFieldHeader->setStream(packetDataField, 0, dimPacketDataFieldHeader-1);
    /// It releases the memory from b only if it goes wrong
    if(b)
    {
        return dataField->getPacketDataFieldHeader()->setByteStream(tempDataFieldHeader);
    }
    else
        return false;
}


bool Packet::setPacketValueSourceDataField(ByteStreamPtr packetDataField, int decodeType)
{
    bool b;
    dword packetLength;
    dword packetLength2;
	
    /// 5) source data field

    /// If necessary, it sets the number of real blocks present
	/*
    if(dataField->sourceDataField->isBlock())
    {
        dword  nrd = dataField->getNumberOfRealDataBlock();
        dataField->sourceDataField->setNumberOfBlocks(nrd);
    }
	 */
    /*if(dataField->sourceDataField->isRBlock()) {
      word nrd = dataField->sourceDataField->getNumberOfRealDataBlock();
      dataField->sourceDataField->setNumberOfBlocks(nrd);
    }*/


    packetLength = dataField->getPacketDataFieldHeader()->size();
    dword pl1 = header->getPacketLength();
    dword pl3 = dataField->getPacketDataFieldHeader()->size();
    dword pl4 = dataField->getPacketTail()->size();
    packetLength2 = pl1 - pl3 -pl4;
    b = tempPacketDataField->setStream(packetDataField, packetLength, packetLength+packetLength2-1);
    if(b)
    {
		/*
		if(isCompressed()) {
			decompress();
			//6) generate a new tempPacketDataField
			packetLength = dataField->getPacketDataFieldHeader()->size();
			dword pl1 = header->getPacketLength();
			dword pl3 = dataField->getPacketDataFieldHeader()->size();
			dword pl4 = dataField->getPacketTail()->size();
			packetLength2 = pl1 - pl3 -pl4;
			b = tempPacketDataField->setStream(packetDataField, packetLength, packetLength+packetLength2-1);
		}
		*/
		
		decodedPacketSourceDataField = true;
        bool ret = dataField->getPacketSourceDataField()->setByteStream(tempPacketDataField, decodeType);
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
    if(dataField->getPacketTail()->size() == 0)
        return true;
    /* NON CANCELLLARE: questo codice sotto funziona bene. Si utilizza
    l'altro solo perche' si suppone che il tail sia sempre posizionato alla fine
    del packet
    word s1 = dataField->dataFieldHeader->size();
    word s2 = dataField->sourceDataField->size();
    s = s1 + s2;
    e = s  + dataField->tail->size() - 1;
    */
    s = packetDataField->size() - dataField->getPacketTail()->size();
    e = packetDataField->size() - 1;
    b = tempTail->setStream(packetDataField, s, e);
    if(b)
        return dataField->getPacketTail()->setByteStream(tempTail);
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





ByteStreamPtr Packet::encodeAndSetData(ByteStreamPtr sourceDataVariable)
{
	//TODO: check
    generateStream();
	
	dword dimpacket = dimPacketHeader + header->getPacketLength();
	
    ByteStreamPtr b = ByteStreamPtr(new ByteStream(packet_output->stream, dimpacket + (thereisprefix?dimPrefix:0), bigendian));
	
	//copy the sourceDataVariable
	if(sourceDataVariable != 0) {
		//the variable part of the sourcedatafield
		//cout << "packet size " << size() << " " << dimpacket << " " << dimPacketStartingFixedPart << " " << sourceDataVariable->size() << endl;
		
		if(sourceDataVariable->size() != size() - dimPacketStartingFixedPart - dimPacketTail)
			throw new PacketException("the size of the sourceDataVariable is wrong");
		bool swapped = false;
		if((!ARCH_BIGENDIAN && bigendian) || (ARCH_BIGENDIAN && !bigendian)) {
			sourceDataVariable->swapWord();
			swapped = true;
		}
		memcpy( packet_output->stream + (thereisprefix?dimPrefix:0) + dimPacketStartingFixedPart, sourceDataVariable->stream, sourceDataVariable->size());
		if(swapped)
			sourceDataVariable->swapWord();
		b = ByteStreamPtr(new ByteStream(packet_output->stream, dimpacket + (thereisprefix?dimPrefix:0), bigendian));
	}
	
    return b;
}

ByteStreamPtr Packet::encode()
{
	//TODO: check
    generateStream();
	
	dword dimpacket = dimPacketHeader + header->getPacketLength();
	
    ByteStreamPtr b = ByteStreamPtr(new ByteStream(packet_output->stream, dimpacket + (thereisprefix?dimPrefix:0), bigendian));
	
    return b;
}

ByteStreamPtr Packet::getOutputStream() {
	dword dimpacket = dimPacketHeader + header->getPacketLength();
	
    ByteStreamPtr b = ByteStreamPtr(new ByteStream(packet_output->stream, dimpacket + (thereisprefix?dimPrefix:0), bigendian));

	return b;
}

ByteStreamPtr Packet::getInputStream()
{
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
    return (char**) dataField->getPacketDataFieldHeader()->printValue();
}

char* Packet::printDataFieldHeaderStream()
{
    return (char*)dataField->getPacketDataFieldHeader()->getByteStream()->printStreamInHexadecimal();
}

char** Packet::printSourceDataFieldValue()
{
    return (char**)dataField->getPacketSourceDataField()->printValue();
}

char* Packet::printSourceDataFieldStream()
{
    return (char*)dataField->getPacketSourceDataField()->printInHexadecimal();
}

char** Packet::printTailValue()
{
    if(dataField->getPacketTail()->size() != 0)
        return (char**)dataField->getPacketTail()->printValue();
    else
        return 0;
}

char* Packet::printTailStream()
{
    if(dataField->getPacketTail()->size() != 0)
        return dataField->getPacketTail()->getByteStream()->printStreamInHexadecimal();

    else
        return 0;
}

char* Packet::printPacketOutputStream()
{
    dword dim = size();
    if(thereisprefix)
        dim += dimPrefix;
    ByteStream b(packet_output->stream, dim, bigendian); //FIXME
    char* c = b.printStreamInHexadecimal();
    return c;
}



bool Packet::decode(ByteStreamPtr stream, bool checkPacketLength) {

	//save a pointer to the current stream to avoid shareptr deallocation
	this->stream = stream;
	decodedPacketHeader = false;
	decodedPacketDataFieldHeader = false;
	decodedPacketSourceDataField = false;
	decodedPacketTail = false;
	
	if(!checkPacketLength)
	{
		
		if(thereisprefix) {
			prefix = ByteStreamPtr(new ByteStream(stream->stream, dimPrefix, bigendian));
			packet = ByteStreamPtr(new ByteStream(stream->stream + dimPrefix, stream->size() - dimPrefix, bigendian));
			//return true;
		}
		else
		{
			prefix = 0;
			packet = stream;
			//return true;
		}
	}
	else
	{
		if(thereisprefix)
			prefix = ByteStreamPtr(new ByteStream(stream->stream, dimPrefix, bigendian));
		else
			prefix = 0;
		
		tempHeader->setStream(stream->stream + dimPrefix, dimPacketHeader, bigendian);
		header->setByteStream(tempHeader);
		dword dim = dimPacketHeader + header->getPacketLength();
		if(dimPrefix + dim > stream->size()) {
			this->packet = 0;
			throw new PacketException("Packet::set - the ByteStream is too small for the packet lenght of this packet");
		}
		
		packet = ByteStreamPtr(new ByteStream(stream->stream + dimPrefix, dim, bigendian));
	}
	//TODO OPTIMIZATION: set the followin method only when is needed
	setByteStreamSections(); //10 per cent of time loss but safer
	return true;

}

bool Packet::decode(ByteStreamPtr prefix, ByteStreamPtr packet, bool checkPacketLength) {
	
	this->stream = 0;
	decodedPacketHeader = false;
	decodedPacketDataFieldHeader = false;
	decodedPacketSourceDataField = false;
	decodedPacketTail = false;
	
	if(!checkPacketLength)
	{
		this->prefix = prefix;
		this->packet = packet;
	}
	else
	{
		this->prefix = prefix;
		tempHeader->setStream(packet->stream + dimPrefix, dimPacketHeader, bigendian);
		header->setByteStream(tempHeader);
		dword dim = dimPacketHeader + header->getPacketLength();
		if(dimPrefix + dim > packet->size()) {
			this->packet = 0;
			throw new PacketException("Packet::set - the ByteStream is too small for the packet lenght of this packet");
		}
		this->packet = packet;
	}
	//TODO OPTIMIZATION: set the following method only when is needed
	setByteStreamSections(); //10 per cent of time loss but safer
	return true;
	
}



bool Packet::decode(ByteStreamPtr prefix, ByteStreamPtr packetHeader, ByteStreamPtr packetDataField, bool checkPacketLenght) {
	//merge packetHeader and packetDataField
	ByteStreamPtr tmpPacket = ByteStreamPtr(new ByteStream(packetHeader, packetDataField, 0));
	return decode(prefix, tmpPacket, checkPacketLenght);
	
}


void Packet::setByteStreamSections()
{

	//ByteStreamPtr tempHeader = ByteStreamPtr(new ByteStream(packet, 0, dimPacketHeader-1));
	//ByteStreamPtr tempDataField = ByteStreamPtr(new ByteStream(packet, dimPacketHeader, packet->size()));
	tempHeader->setStream(packet, 0, dimPacketHeader-1);
    tempDataField->setStream(packet, dimPacketHeader, packet->size());
    this->header->memByteStream(tempHeader);
    this->dataField->memByteStream(tempDataField);
}


ByteStreamPtr Packet::getBSPrefix() {
	return prefix;
}

ByteStreamPtr Packet::getBSPacket() {
	return packet;
}

ByteStreamPtr Packet::getBSHeader() {
	ByteStreamPtr header = ByteStreamPtr(new ByteStream(packet->stream + dimPrefix, dimPacketHeader, bigendian));
	return header;
}

ByteStreamPtr Packet::getBSDataFieldHeader() {
	ByteStreamPtr dfh = ByteStreamPtr(new ByteStream(packet->stream + dimPrefix + dimPacketHeader, dimPacketDataFieldHeader, bigendian));
	return dfh;
}

ByteStreamPtr Packet::getBSSourceDataFieldsFixedPart() {
	ByteStreamPtr sdff = ByteStreamPtr(new ByteStream(packet->stream + dimPrefix + dimPacketHeader + dimPacketDataFieldHeader, dimPacketSourceDataFieldFixed, bigendian));
	return sdff;
}

ByteStreamPtr Packet::getBSSourceDataFieldsVariablePart() {
	dword dimvariablepart = packet->size() - dimPrefix - dimPacketStartingFixedPart - dimPacketTail;
	ByteStreamPtr sdff = ByteStreamPtr(new ByteStream(packet->stream + dimPrefix + dimPacketStartingFixedPart, dimvariablepart, bigendian));
	return sdff;
}

ByteStreamPtr Packet::getData() {
	return getBSSourceDataFieldsVariablePart();
}

ByteStreamPtr Packet::getBSSourceDataField() {
	dword dimvariablepart = packet->size() - dimPrefix - (dimPacketStartingFixedPart - dimPacketSourceDataFieldFixed) - dimPacketTail;
	ByteStreamPtr sdff = ByteStreamPtr(new ByteStream(packet->stream + dimPrefix + dimPacketStartingFixedPart - dimPacketSourceDataFieldFixed, dimvariablepart, bigendian));
	return sdff;
}


enum CompressionAlgorithms Packet::getCompressionAlgorithm() {
	switch(compressionAlgorithmsSection)
	{
		case 0:
			return (enum CompressionAlgorithms) header->getFieldValue(compressionAlgorithmsIndex);
			break;
		case 1:
			return (enum CompressionAlgorithms) dataField->getPacketDataFieldHeader()->getFieldValue(compressionAlgorithmsIndex);
			break;
		default:
			throw new PacketException("Error in the compression algorithm section field specification");
	}
}

word Packet::getCompressionLevel() {
	switch(compressionLevelSection)
	{
		case 0:
			return header->getFieldValue(compressionLevelIndex);
			break;
		case 1:
			return dataField->getPacketDataFieldHeader()->getFieldValue(compressionLevelIndex);
			break;
		default:
			throw new PacketException("Error in the compression level section field specification");
	}
}

ByteStreamPtr Packet::compressData(enum CompressionAlgorithms compressionAlgorithm, byte compressionLevel) {
	
	if(!isCompressible())
		return 0;
	
	//set the algorithm
	switch(compressionAlgorithmsSection)
	{
		case 0:
			header->setFieldValue(compressionAlgorithmsIndex, compressionAlgorithm);
			header->generateStream(bigendian);
			break;
		/*
		 TODO
		case 1:
			dataField->getPacketDataFieldHeader()->setFieldValue(compressionAlgorithmsIndex, compressionAlgorithm);
			dataField->getPacketDataFieldHeader()->generateStream(bigendian);
			break;
		case 2:
			dataField->getPacketSourceDataField()->setFieldValue(compressionAlgorithmsIndex, compressionAlgorithm);
			break;
		 */
		default:
			throw new PacketException("Error in the compression algorithm section field specification");
	}
	switch(compressionLevelSection)
	{
		case 0:
			header->setFieldValue(compressionLevelIndex, compressionLevel);
			header->generateStream(bigendian);
			break;
		/*
		 TODO
		case 1:
			dataField->getPacketDataFieldHeader()->setFieldValue(compressionLevelIndex, compressionLevel);
			dataField->getPacketDataFieldHeader()->generateStream(bigendian);
			break;
		case 2:
			 dataField->getPacketSourceDataField()->setFieldValue(compressionAlgorithmsIndex, compressionAlgorithm);
			 break;
			 */
		default:
			throw new PacketException("Error in the compression level section field specification");
	}
	//cout << compressionAlgorithmsSection << " " << compressionAlgorithmsIndex << " " << compressionAlgorithm << " - " << compressionLevelSection << " " << compressionLevelIndex << " " << (int)compressionLevel << endl;
	
	dword dimvariablepart = header->getPacketLength() + dimPacketHeader - dimPacketStartingFixedPart - dimPacketTail;
	ByteStreamPtr original = ByteStreamPtr(new ByteStream(packet_output->stream  + (thereisprefix?dimPrefix:0) + dimPacketStartingFixedPart, dimvariablepart, bigendian));

	ByteStreamPtr compressed = original->compress(compressionAlgorithm, compressionLevel);
	//cout << "original: " << original->size() << " compressed: " << compressed->size() << endl;
	
	ByteStreamPtr tail = 0;
	if(dimPacketTail > 0)
		tail = ByteStreamPtr(new ByteStream(packet_output->stream + (thereisprefix?dimPrefix:0) + header->getPacketLength() + dimPacketHeader - dimPacketTail , dimPacketTail, bigendian));
	
	ByteStreamPtr b;
	
	if(compressed != 0) {
		//the variable part of the sourcedatafield
		//cout << "packet size " << size() << " " << dimpacket << " " << dimPacketStartingFixedPart << " " << sourceDataVariable->size() << endl;

		memcpy( packet_output->stream + (thereisprefix?dimPrefix:0) + dimPacketStartingFixedPart, compressed->stream, compressed->size());
		dword dimpacket = dimPacketStartingFixedPart + compressed->size() + dimPacketTail;
		if(dimPacketTail != 0)
			memcpy( packet_output->stream + (thereisprefix?dimPrefix:0) + dimpacket - dimPacketTail, tail->stream, dimPacketTail);
		
		//set packet length
		dword dimDataField = dimPacketDataFieldHeader + dimPacketSourceDataFieldFixed + dimPacketTail + compressed->size();
		header->setPacketLength(dimDataField);
		header->generateStream(bigendian);
		
		b = ByteStreamPtr(new ByteStream(packet_output->stream, dimpacket + (thereisprefix?dimPrefix:0), bigendian));
	}
	
	return compressed;
}

ByteStreamPtr Packet::getBSTail() {
	//dword dimvariablepart = packet->size() - dimPrefix - dimPacketStartingFixedPart - dimPacketTail;
	ByteStreamPtr tail = 0;
	if(dimPacketTail > 0)
		ByteStreamPtr tail = ByteStreamPtr(new ByteStream(packet->stream + packet->size() - dimPacketTail, dimPacketTail, bigendian));
	return tail;
}


PacketHeader* Packet::getPacketHeader() {
	if(packet && !decodedPacketHeader) {
		setPacketValueHeader(getBSHeader());
		decodedPacketHeader = true;
	}
	return header;
}


DataFieldHeader* Packet::getPacketDataFieldHeader() {
	if(!decodedPacketDataFieldHeader) {
		setPacketValueDataFieldHeader(dataField->getByteStream());
		decodedPacketDataFieldHeader = true;
	}
	return dataField->getPacketDataFieldHeader();
}



SourceDataField* Packet::getPacketSourceDataField() {
	if(!decodedPacketSourceDataField) {
		setPacketValueSourceDataField(dataField->getByteStream(), DECODETYPE);
		decodedPacketSourceDataField = true;
	}
	return dataField->getPacketSourceDataField();
}


PartOfPacket* Packet::getPacketTail() {
	if(!decodedPacketTail) {
		setPacketValueTail(getBSTail());
		decodedPacketTail = true;
	}
	return dataField->getPacketTail();
}

ByteStreamPtr Packet::decompressData() {
	//ALGORITHM FOR AUTOMATIC DECOMPRESSION: NOT IMPLEMENTED NOW. TODO
	//decompression algorithm here
	//1) get the fixed and variable part of the source data field, get the tail
	//2) decompress the variable part of the source data field into a new ByteStream
	//3) rebuild a new "newstream" bytestream, taking into account the prefix, (if any) and the tail
	//4) change the size of the packet into the header (manually)
	//5) change the field the indicate if the packet is compressed = 0
	//5) call decode(newstream)
	
	//DECOMPRESS ONLY THE DATA
	if(!isCompressed())
		return getData();
	ByteStreamPtr compressed = getData();
	ByteStreamPtr decompressed = compressed->decompress(getCompressionAlgorithm(), getCompressionLevel(), sizeMax());

	return decompressed;
	
}

