/***************************************************************************
                          PacketStream.cpp  -  description
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
 
#include "PacketStream.h"
#include "ConfigurationFile.h"
#include "PacketExceptionFileFormat.h"
#include "PacketExceptionIO.h"
#include "PacketNotRecognized.h"
#include "PacketLibDemo.h"

using namespace PacketLib;





PacketStream::PacketStream(const char* fileNameConfig)
{
    this->filenameConfig = (char*) fileNameConfig;
    numberOfPacketType = 0;
    headerReference = 0;
    //TODO
    packetType = new Packet* [255];
    //TODO
    memset(packetType, 0, sizeof(Packet*)*255);
    pathFileNameConfig = 0;
	dimHeader = 0;
	createStreamStructure();
}



PacketStream::PacketStream()
{
    this->filenameConfig = 0;
    numberOfPacketType = 0;
    headerReference = 0;
    //TODO
    packetType =  new Packet* [255];
    //TODO
    memset(packetType, 0, sizeof(Packet*)*255);
    pathFileNameConfig = 0;
	dimHeader = 0;
}



PacketStream::~PacketStream()
{
    for(int i=0; i< numberOfPacketType; i++)
        delete packetType[i];
    delete[] packetType;
    delete headerReference;
    free(pathFileNameConfig);
}

dword PacketStream::getPacketDimension(ByteStreamPtr stream) {
	dword dimPre = 0;
	if(prefix)
		dimPre += dimPrefix;
	//ByteStreamPtr prefix = new ByteStream(stream, dimPre, bigendian);
	
	dword dim = 0;
	dword dimHeader = headerReference->size();
	dim += dimHeader;
	ByteStreamPtr tempHeader = ByteStreamPtr(new ByteStream());
	tempHeader->setStream(stream->stream+dimPre, dimHeader, bigendian);
	headerReference->setByteStream(tempHeader);
	dim += headerReference->getPacketLength();
	return dim;
}


int PacketStream::detPacketType(ByteStreamPtr prefix, ByteStreamPtr packetHeader, ByteStreamPtr packetDataField)
{
    ///  Iterate through list and output each element.
    ///  The packetType 0 is the packet not recognized
    for (int i = 1; i<numberOfPacketType; i++)
    {
        Packet* p = getPacketType(i);
		p->decode(prefix, packetHeader, packetDataField);
        if(p->verify())
            return i;
    }
    return 0;
}

int PacketStream::detPacketType(ByteStreamPtr prefix, ByteStreamPtr packet)
{
    /// Iterate through list and output each element.
    /// The packetType 0 is the packet not recognized
    for (dword i = 1; i<numberOfPacketType; i++)
    {
        Packet* p = getPacketType(i);
		p->decode(prefix, packet);
        if(p->verify())
            return i;
    }
    return 0;
}


int PacketStream::detPacketType(ByteStreamPtr packet)
{
    /// Iterate through list and output each element.
    /// The packetType 0 is the packet not recognized
    for (dword i = 1; i<numberOfPacketType; i++)
    {
        Packet* p = getPacketType(i);
		p->decode(packet);
        if(p->verify())
            return i;
    }
    return 0;
}



Packet* PacketStream::getPacket(ByteStreamPtr stream) throw(PacketException*){
	
	int index = detPacketType(stream);
	if(index > 0) {
		Packet* p = getPacketType(index);
		
		if(!p->decode(stream)) //gli stream diventano del packet
			throw new PacketExceptionIO("it is impossible to resolve the packet.");
		
		return p;
		
	}
	else
		return 0;
	
}



bool PacketStream::createStreamStructure() throw(PacketException*)
{
    ConfigurationFile config;
    char* line;
    char **argv = new char* [1];
    argv[0] = filenameConfig;
    //cout << "@@@@@@@@@@OPEN " << filenameConfig << endl;
    try
    {
        if(config.open(argv))
        {
            //delete[] argv;
            if(pathFileNameConfig) free(pathFileNameConfig);
            pathFileNameConfig = getcwd(NULL, 512L);
            /// prefix
            config.setpos(0);
            line = config.getLine();
            if(strcmp(line, "[Configuration]") == 0)
            {
                //delete[] line;
                line = config.getLine();
                if(strcmp(line, "false") == 0)
                    prefix = false;
                else
                {
                    if(strcmp(line, "true") == 0)
                        prefix = true;
                    else
                    {
                        //delete[] line;
                        throw new PacketExceptionFileFormat("Prefix selector format not correct. It's possible only true or false value.");
                        return false;
                    }
                }
                //delete[] line;
                /// bigendian
                line = config.getLine();
                if(strcmp(line, "false") == 0)
                    bigendian = false;
                else
                {
                    if(strcmp(line, "true") == 0)
                        bigendian = true;
                    else
                    {
                        throw new PacketExceptionFileFormat("Bigendian selector format not correct. It's possible only true or false value.");
                        return false;
                    }
                }
                /// dimensione of prefix
                //delete[] line;
                line = config.getLine();
				if(prefix == false)
					dimPrefix = 0;
				else
					dimPrefix = atoi(line);
            }
            else
                throw new PacketExceptionFileFormat("No [Configuration] section found.");
            /// [Header Format] section
            //delete[] line;
            line = config.getLine();
            if(strcmp(line, "[Header Format]") == 0)
            {
                //delete[] line;
                ///  Create headerReference of PacketHeader type. The method reads the structure of header from configuration file (named in filenameConfig)
                line = config.getLine();
                delete headerReference;
                headerReference = (PacketHeader*) new PacketHeader();
                if(!headerReference->loadHeader(line))
                {
                    //delete[] line;
                    throw new PacketExceptionFileFormat("No parameters in file header format");
                    return false;
                }
				dimHeader = headerReference->size();
                /// It creates the PACKET NOT RECOGNIZED
                PacketNotRecognized* p = new PacketNotRecognized(bigendian);
                if(!p->createPacketType(line, prefix, dimPrefix))
                {
                    //delete[] line;
                    throw new PacketExceptionFileFormat("Packet Not Recognized not created.");
                }
                else
                {
                    packetType[numberOfPacketType] = p;
                    numberOfPacketType++;
                }
                //delete[] line;
            }
            else
            {
                throw new PacketExceptionFileFormat("No [Header format] section");
                return false;
            }
            /// [Packet Format]
            line = config.getLine();
            if(strcmp(line, "[Packet Format]") == 0)
            {
                char* packetFileName = config.getLine();
                while(strlen(packetFileName) != 0)
                {
                    Packet* p;
                    p = new Packet(bigendian);
                    p->createPacketType(packetFileName, prefix, dimPrefix);
                    packetType[numberOfPacketType] = p;
                    p->setPacketID(numberOfPacketType);
                    numberOfPacketType++;
                    //delete[] packetFileName;
                    packetFileName = config.getLine();
                }
            }
            else
            {
                throw new PacketExceptionFileFormat("No [Packet Format] section");
                return false;
            }
            config.close();
        }
        else
            throw new PacketExceptionFileFormat("Header file configuration not found.");

        return true;
    }
    catch(PacketExceptionIO* e)
    {
        e->add(" - ");
        e->add(filenameConfig);
        e->add("Configuration file: ");
        throw e;
    }
    catch(PacketExceptionFileFormat* e)
    {
        e->add(" - ");
        e->add(filenameConfig);
        e->add("Configuration file: ");
        throw e;
    }
}

word PacketStream::getPrefixDimension() const
{
    if(prefix)
        return dimPrefix;
    else
        return 0;
}


word PacketStream::getHeaderDimension() const
{
	return dimHeader;
}


word PacketStream::getNumberOfPacketType()
{
    return numberOfPacketType;
}


Packet* PacketStream::getPacketType(int index)
{
    return packetType[index];
}

Packet* PacketStream::getPacketType(string name) {
	for(int i=1; i<numberOfPacketType; i++) {
		string pname = packetType[i]->getName();
		if(pname == name)
			return packetType[i];
	}
	throw new PacketException("Packet type not found in the PacketStream");
}

bool PacketStream::isBigEndian()
{
    return (bool) this->bigendian;
}


void PacketStream::setFileNameConfig(const char* f)
{
    this->filenameConfig = (char*) f;
    //this->pathFileNameConfig = Utility::extractPath(filenameConfig);
}


bool PacketStream::thereIsPrefix()
{
    return prefix;
}
