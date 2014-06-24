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
#include "SourceDataField.h"
#include "PacketException.h"
#include "PacketExceptionIO.h"
#include "PacketExceptionFileFormat.h"

//Packet::size()
//stream = prefix + packet
//Packet::set(ByteStreamPtr stream)
//Packet::set(ByteStreamPtr prefix, ByteStream packet)
//Packet::set(ByteStreamPtr prefix, ByteStreamPtr header, ByteStreamPtr dataField)
//check if the stream
//bool Packet::verify()
//char** Packet::printFields()
//char* Packet::printStream();

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
	
	/// Decode the packet
    /// \param stream A pointer to the stream of byte, with prefix and packet
	/// \param checkPacketLenght if true check the packet lenght and set the packet stream, if false do not check the packet lenght
    virtual bool decode(ByteStreamPtr stream, bool checkPacketLenght = false);
	
	/// Decode the packet
    /// \param prefix A pointer to the stream of byte, with the prefix
	/// \param packet A pointer to the stream of byte, with the packet
	/// \param checkPacketLenght if true check the packet lenght and set the packet stream, if false do not check the packet lenght
    virtual bool decode(ByteStreamPtr prefix, ByteStreamPtr packet, bool checkPacketLenght = false);
	
	/// Decode the packet
    /// \param prefix A pointer to the stream of byte, with the prefix
	/// \param packetHeader A pointer to the stream of byte, with the packet header
	/// \param packetHeader A pointer to the stream of byte, with the packet data field
	/// \param checkPacketLenght if true check the packet lenght and set the packet stream, if false do not check the packet lenght
    virtual bool decode(ByteStreamPtr prefix, ByteStreamPtr packetHeader, ByteStreamPtr packetDataField, bool checkPacketLenght = false);
	
	/// Verify the content of the packet (after the decode)
	///\return true is the packet contained into the stream is recognized using identifiers.
	///\pre the ByteStream is set with one of decode(ByteStream) methods
	virtual bool verify();
	
	///\return compress the data section and change the packet (the variable part of the "source data field")
	///\post the variable part of the "source data field" is compressed and should be sent or stored
	virtual ByteStreamPtr compressData(enum CompressionAlgorithms compressionAlgorithm, byte compressionLevel);
	
	///\return decompress the data section without changing the packet  (the variable part of the "source data field")
	virtual ByteStreamPtr decompressData();
	
	///Get the compression algorithm used for this packet
	virtual enum CompressionAlgorithms getCompressionAlgorithm();
	
	///Get the compression level used for this packet
	virtual word getCompressionLevel();
	
	///\return true if the packet is compressed
	bool isCompressed() {
		if(compressible && getCompressionAlgorithm() != NONE)
			return true;
		else
			return false;
	}
	
	///\return true is the packet is compressible, i.e. there are the useful fields that can store the information of the compression
	bool isCompressible() {
		return compressible;
	}
		
	///Get the prefix as a ByteStream
	ByteStreamPtr getBSPrefix();
	
	///Get the packet as a ByteStream
	ByteStreamPtr getBSPacket();
	
	///Get the header as a ByteStream
	ByteStreamPtr getBSHeader();
	
	///Get the data field header as a ByteStream
	ByteStreamPtr getBSDataFieldHeader();
	
	///Get the fixed part of the source data field as a ByteStream
	ByteStreamPtr getBSSourceDataFieldsFixedPart();
	
	///Get the the variable part of the source data field as a ByteStream
	ByteStreamPtr getBSSourceDataFieldsVariablePart();
	
	///Get the the variable part of the source data field as a ByteStream that contains the data
	ByteStreamPtr getData();
	
	///Get the the source data field as a ByteStream
	ByteStreamPtr getBSSourceDataField();
		
	///Get the tail as a ByteStream
	ByteStreamPtr getBSTail();
	
	///Get the header
	PacketHeader* getPacketHeader();
	
	///Get the data field header
	DataFieldHeader* getPacketDataFieldHeader();
	
	///Get the source data field
	SourceDataField* getPacketSourceDataField();
	
	///Get the tail
	PartOfPacket* getPacketTail();
	
	/// Gets the dimension in byte of the current packet (header + datafield (data field header + sdf + tail)
    dword size();
	
	/// Get dimension in bytes of the fixed part (without tail) = dim(header) + dim(data field header) + dim(source data field fixed)
	inline dword sizeFixedPart() { return dimPacketStartingFixedPart; };
    
	/// Get dimension of the prefix
	inline dword sizePrefix() { return dimPrefix; };
	
	/// Get dimension of the tail
    inline dword sizeTail() { return dimPacketTail; };
	
    /// Gets the max dimension in byte of the packet.
    dword sizeMax();
    
    /// Gets the ByteStream received as input
    ByteStreamPtr getInputStream();

    
    /// Encode the packet before write. The output packet is generated during this call.
	/// \param sourceDataVariable Is a ByteStream that is copied in the source data field fixed part
	/// \return the encoded stream
    ByteStreamPtr encodeAndSetData(ByteStreamPtr sourceDataVariable);
	
	/// Encode the packet before write. The output packet is generated during this call.
	/// \return the encoded stream
    ByteStreamPtr encode();

	/// Get the ByteStream of the encoded/compressed packet
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
	
protected:
	
	/// This is the ByteStream generated with generateStream().
    ByteStreamPtr packet_output;
	
	/// Sets all the fields of the packet with correct value contained into the input ByteStream.
    ///	\pre The structure of the stream must be loaded.
    /// \param prefix This is the prefix of the packet
    /// \param packetHeader This is the header of the packet
    /// \param packetDataField This is the data field of the packet
	/// \param decodeType (0) do not decode anything (1) decode only sections (prefix, header, data field header, source data field fixed part, source data field variable part) (2) decode blocks (all sections + all blocks of the ‘source data field variable part’)
    /// \post the bytestream is decoded
    virtual bool setPacketValue(ByteStreamPtr prefix, ByteStreamPtr packetHeader, ByteStreamPtr packetDataField, int decodeType);

    
    /// This attribute represents the packet header.
    PacketHeader *header;

    
    /// This attribute represent the packet data field.
    PacketDataField *dataField;

    
    /// the prefix of the packet.
    ByteStreamPtr prefix;

    
    /// The ByteStrem of the packet read
    ByteStreamPtr packet;
	
	/// The ByteStrem of the packet read
    ByteStreamPtr stream;
	
	
	void setByteStreamSections();

    
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
	
	bool decodedPacketHeader;
	
	bool decodedPacketDataFieldHeader;
	
	bool decodedPacketSourceDataField;
	
	bool decodedPacketTail;
	
	int compressionAlgorithmsSection;
	
	int compressionAlgorithmsIndex;
	
	int compressionLevelSection;
	
	int compressionLevelIndex;
	
	bool compressible;

};

}

#endif
