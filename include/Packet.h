/***************************************************************************
                          Packet.h  -  description
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
 
#ifndef _PACKET_H
#define _PACKET_H

#include "PacketLibDefinition.h"
#include "PacketDataField.h"
#include "PacketHeader.h"
#include "PacketIdentifier.h"
#include "ByteStream.h"
#include "ConfigurationFile.h"
#include "Utility.h"
#include "SDFBlockFixed.h"
#include "SDFBlockVariable.h"
#include "SDFNoBlockFixed.h"
#include "SDFRBlock.h"
#include "PacketException.h"
#include "PacketExceptionIO.h"
#include "PacketExceptionFileFormat.h"


namespace PacketLib
{

///	\brief Represent a single packet.
class Packet
{
public:

    /// Constructor
    Packet(bool bigendian);

    /// Distruttore
    virtual ~Packet();

    virtual bool createPacketType(char* fileName, bool prefix, word dimprefix) throw (PacketException*);

    /// This method verifies if the ByteStream on argument contains the correct value
    /// in the identifiers. If this is true, the method return true and the stream
    /// contains a packet of this type. This method overloads another method.
	/// \post the bytestream is decoded
    virtual bool setAndVerifyPacketValue(ByteStreamPtr prefix, ByteStreamPtr packetHeader, ByteStreamPtr packetDataField);

    /// This method verifies if the ByteStream on argument contains the correct value
    /// in the identifiers. If this is true, the method returns true and the stream
    /// contains a packet of this type. This method overloads another method.
    /// \post the bytestream is decoded
    virtual bool setAndVerifyPacketValue(ByteStreamPtr prefix, ByteStreamPtr packet);

    /// Sets all the fields of the packet with correct value contained into the input ByteStream.
    ///	\pre The structure of the stream must be loaded.
    /// \param prefix This is the prefix of the packet
    /// \param packetHeader This is the header of the packet
    /// \param packetDataField This is the data field of the packet
	/// \param decodeType (0) do not decode anything (1) decode only sections (prefix, header, data field header, source data field fixed part, source data field variable part) (2) decode blocks (all sections + all blocks of the ‘source data field variable part’)
    /// \post the bytestream is decoded
    virtual bool setPacketValue(ByteStreamPtr prefix, ByteStreamPtr packetHeader, ByteStreamPtr packetDataField, int decodeType);

    /// Sets all the fields of the packet with correct value contained into the input ByteStream.
    ///	\pre The structure of the stream must be loaded.
    /// \param prefix This is the prefix of the packet
    /// \param packet This is the packet
	/// \param decodeType (0) do not decode anything (1) decode only sections (prefix, header, data field header, source data field fixed part, source data field variable part) (2) decode blocks (all sections + all blocks of the ‘source data field variable part’)
    /// \post the bytestream is decoded
    virtual bool setPacketValue(ByteStreamPtr prefix, ByteStreamPtr packet, int decodeType);

    /// Verifies if within the ByteStream passed with arguments it's present a correct packet.
    ///	\pre The structure of the stream must be loaded.
    /// \param prefix This is the prefix of the packet
    /// \param packet This is the packet
    /// \return True if the ByteStream contains a packet
    virtual bool verifyPacketValue(ByteStreamPtr prefix, ByteStreamPtr packet);

    /// Verifies if within the byte* stream passed with arguments it's present a correct packet. The stream* contains also the prefix (if present)
    /// \param stream A pointer to the stream of byte, with prefix and packet
    virtual bool verifyPacketValue(byte* stream);

    /// Sets all the fields of the packet with correct value contained into the input ByteStream.
    /// \param stream A pointer to the stream of byte, with prefix and packet
	/// \param decode only the sections
	/// \param decodeType (0) do not decode anything (1) decode only sections (prefix, header, data field header, source data field fixed part, source data field variable part) (2) decode blocks (all sections + all blocks of the ‘source data field variable part’)
    virtual bool setPacketValue(ByteStreamPtr stream, int decodeType);

    /// Verifies if within the ByteStream passed with arguments it's present a correct packet.
    ///	\pre The structure of the stream must be loaded.
    /// \param prefix This is the prefix of the packet.
    /// \param packetHeader This is the header of the packet.
    /// \param packetDataField This is the data field of the packet.
    /// \return True if the ByteStream contains a packet.
    virtual bool verifyPacketValue(ByteStreamPtr prefix, ByteStreamPtr packetHeader, ByteStreamPtr packetDataField);
	
	///Get the prefix as a ByteStream
	ByteStreamPtr getBSPrefix();
	
	///Get the header as a ByteStream
	ByteStreamPtr getBSHeader();
	
	///Get the data field header as a ByteStream
	ByteStreamPtr getBSDataFieldHeader();
	
	///Get the fixed part of the source data field as a ByteStream
	ByteStreamPtr getBSSourceDataFieldsFixedPart();
	
	///Get the the variable part of the source data field as a ByteStream
	ByteStreamPtr getBSSourceDataFieldsVariablePart();
	
	///Get the tail as a ByteStream
	ByteStreamPtr getBSTail();

    /// Prints to stdout the value of packet data field in a formatted mode.
    virtual void printPacketValue();

    /// Prints the hexadecimal dump of the prefix.
    virtual  char* printPrefixStream();

    /// Prints the header values.
    virtual  char** printHeaderValue();

    /// Prints the hexadecimal dump of the header.
    virtual  char* printHeaderStream();

    /// Prints the data field header values.
    virtual  char** printDataFieldHeaderValue();

    /// Prints the hexadecimal dump of the data field header.
    virtual  char* printDataFieldHeaderStream();
    
    /// Prints the source data field values.
    virtual  char** printSourceDataFieldValue();

    /// Prints the hexadecimal dump of the source data field.
    virtual  char* printSourceDataFieldStream();
    
    /// Prints the tail values
    virtual  char** printTailValue();

    /// Print he hexadecimal dump of the tail.
    virtual  char* printTailStream();

    virtual  char* printPacketOutputStream();

    /// Gets the dimension in byte of the current packet (header + datafield (data field header + sdf + tail)
    dword getDimension();

	/// Get dimension in bytes of the fixed part (without tail) = dim(header) + dim(data field header) + dim(source data field fixed)
	inline dword getDimensionFixedPart() { return dimPacketStartingFixedPart; };
    
	/// Get dimension of the prefix
	inline dword getDimensionPrefix() { return dimPrefix; };
	
	/// Get dimension of the tail
    inline dword getDimensionTail() { return dimPacketTail; };
	
    /// Gets the max dimension in byte of the packet.
    dword getMaxDimension();

    
    /// Gets the ByteStream received as input
    ByteStreamPtr getInputStream();

    
    /// Gets the packet generated with the generateStream() method. The output
    /// packet is generated during this call.
    ByteStreamPtr getOutputStream();

    
    /// Gets the name of packet.
    virtual char* getName()
    {
        return name;
    }

    
    /// The name of the file .packet that contains the structure of the packet
    virtual char* getFileName()
    {
        return filename;
    }

    
    /// Prints to stdout the identifiers of the packet.
    virtual void printIdentifiers();

    
    /// Writes property of byte packetID.
    virtual void setPacketID(const byte& value);

    
    /// Read property of byte packetID.
    virtual const byte& getPacketID();


    bool thereIsPrefix();

    bool isBigendian() {
    	return bigendian;
    }

    
    /// This attribute represents the packet header.
    PacketHeader *header;

    
    /// This attribute represent the packet data field.
    PacketDataField *dataField;

    
    /// the prefix of the packet.
    ByteStreamPtr prefix;

    
    /// The ByteStrem of the packet read
    ByteStreamPtr packet;

    
    /// This is the ByteStream generated with generateStream().
    ByteStreamPtr packet_output;


protected:
	
	/// Set the internal prefix and packet.
	virtual void setByteStreamPointers(ByteStreamPtr prefix, ByteStreamPtr packetHeader, ByteStreamPtr packetDataField);
	
	/// Set the internal prefix and packet.
	virtual void setByteStreamPointers(ByteStreamPtr prefix, ByteStreamPtr packet);
    
    /// Generates the stream for output.
    /// \pre the number of block and the number of element for each block
    /// must be set (if appliable)
    virtual void generateStream();
    
    /// Loads the configuration of identifiers from file .packet.
    virtual bool loadIdentifiers(ConfigurationFile& file);
    
    /// This is the number that identifies the packet in the .stream file
    byte packetID;
    
    /// The name of the packet
    char* name;
    
    /// List of identifiers. This identifiers permits to identify if the stream contains
    /// a particular type of packet
    PacketIdentifier** identifiers;
    
    /// List of bool that indicates which part of packet are presents into one or more
    /// identifiers. 0 is the header, 1 is the data field header, 2 is the source data field
    bool type_of_identifier[3];

    unsigned number_of_identifier;

    bool setPacketValuePrefix(ByteStreamPtr prefix);

    bool setPacketValueVerify(ByteStreamPtr prefix, ByteStreamPtr packetHeader, ByteStreamPtr packetDataField);

    bool setPacketValueDataFieldHeader(ByteStreamPtr packetDataField);

	/// \param decodeType (0) do not decode anything (1) decode only sections (prefix, header, data field header, source data field fixed part, source data field variable part) (2) decode blocks (all sections + all blocks of the ‘source data field variable part’)
    bool setPacketValueSourceDataField(ByteStreamPtr packetDataField, int decodeType);

    bool setPacketValueHeader(ByteStreamPtr header);

    bool setPacketValueTail(ByteStreamPtr packetDataField);

    void memByteStream(ByteStreamPtr prefix, ByteStreamPtr packetHeader, ByteStreamPtr packetDataField);

    void memByteStream(ByteStreamPtr prefix, ByteStreamPtr packet);

    bool bigendian;

    bool thereisprefix;

    /// The name of the file .packet that contains the structure of the packet
    char* filename;

private:

    ByteStreamPtr tempHeader;

    ByteStreamPtr tempDataField;

    ByteStreamPtr tempDataFieldHeader;

    ByteStreamPtr tempPacketDataField;

    ByteStreamPtr tempTail;

    bool first_output_stream_setted;
	
	///dimension in byte of the fixed part - calculated during the load
	dword dimPrefix;
	
	dword dimPacketHeader;
	
	dword dimPacketDataFieldHeader;
	
	dword dimPacketSourceDataFieldFixed;
	
	dword dimPacketTail;
	
	///dimPacketHeader + dimPacketDataFieldHeader + dimPacketSourceDataFieldFixed
	dword dimPacketStartingFixedPart;

};

}

#endif
