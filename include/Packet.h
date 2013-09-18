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
    /// \post A side effects of this method is that the value of fields of packet are set with
    /// correct value.
    virtual bool setAndVerifyPacketValue(ByteStream* prefix, ByteStream* packetHeader, ByteStream* packetDataField);

    /// This method verifies if the ByteStream on argument contains the correct value
    /// in the identifiers. If this is true, the method returns true and the stream
    /// contains a packet of this type. This method overloads another method.
    /// \post A side effect of this method is that the values of fields of packet are set with
    /// correct value
    virtual bool setAndVerifyPacketValue(ByteStream* prefix, ByteStream* packet);

    /// Sets all the fields of the packet with correct value contained into the input ByteStream.
    ///	\pre The structure of the stream must be loaded.
    /// \param prefix This is the prefix of the packet
    /// \param packetHeader This is the header of the packet
    /// \param packetDataField This is the data field of the packet
    /// \post If return is true all the fields are set with the correct value.
    virtual bool setPacketValue(ByteStream* prefix, ByteStream* packetHeader, ByteStream* packetDataField);

    /// Sets all the fields of the packet with correct value contained into the input ByteStream.
    ///	\pre The structure of the stream must be loaded.
    /// \param prefix This is the prefix of the packet
    /// \param packet This is the packet
    /// \post If return is true all the fields are set with the correct value.
    virtual bool setPacketValue(ByteStream* prefix, ByteStream* packet);

    /// Verifies if within the ByteStream passed with arguments it's present a correct packet.
    ///	\pre The structure of the stream must be loaded.
    /// \param prefix This is the prefix of the packet
    /// \param packet This is the packet
    /// \return True if the ByteStream contains a packet
    bool verifyPacketValue(ByteStream* prefix, ByteStream* packet);

    /// Verifies if within the byte* stream passed with arguments it's present a correct packet. The stream* contains also the prefix (if present)
    /// \param stream A pointer to the stream of byte, with prefix and packet
    bool verifyPacketValue(byte* stream);

    /// Sets all the fields of the packet with correct value contained into the input ByteStream.
    /// \param stream A pointer to the stream of byte, with prefix and packet
    bool setPacketValue(byte* stream);

    /// Verifies if within the ByteStream passed with arguments it's present a correct packet.
    ///	\pre The structure of the stream must be loaded.
    /// \param prefix This is the prefix of the packet.
    /// \param packetHeader This is the header of the packet.
    /// \param packetDataField This is the data field of the packet.
    /// \return True if the ByteStream contains a packet.
    bool verifyPacketValue(ByteStream* prefix, ByteStream* packetHeader, ByteStream* packetDataField);

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

    
    /// Gets the dimension in byte of the current packet.
    dword getDimension();

    
    /// Gets the max dimension in byte of the packet.
    dword getMaxDimension();

    
    /// Gets the ByteStream received as input
    ByteStream* getInputStream();

    
    /// Gets the packet generated with the generateStream() method. The output
    /// packet is generated during this call.
    ByteStream* getOutputStream();

    
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

    
    /// Deletes the ByteStream passed as arguments.
    virtual void deleteExternalByteStream();

    
    /// Writes property of byte packetID.
    virtual void setPacketID(const byte& value);

    
    /// Read property of byte packetID.
    virtual const byte& getPacketID();


    bool thereIsPrefix();

    
    /// This attribute represents the packet header.
    PacketHeader *header;

    
    /// This attribute represent the packet data field.
    PacketDataField *dataField;

    
    /// the prefix of the packet.
    ByteStream* prefix;

    
    /// The ByteStrem of the packet read
    ByteStream* packet;

    
    /// This is the ByteStream generated with generateStream().
    ByteStream* packet_output;


protected:

    
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

    bool setPacketValuePrefix(ByteStream* prefix);

    bool setPacketValueVerify(ByteStream* prefix, ByteStream* packetHeader, ByteStream* packetDataField);

    bool setPacketValueDataFieldHeader(ByteStream* packetDataField);

    bool setPacketValueSourceDataField(ByteStream* packetDataField);

    bool setPacketValueHeader(ByteStream* header);

    bool setPacketValueTail(ByteStream* packetDataField);

    void memByteStream(ByteStream* prefix, ByteStream* packetHeader, ByteStream* packetDataField);

    void memByteStream(ByteStream* prefix, ByteStream* packet);

    bool bigendian;

    bool thereisprefix;

    word dimPrefix;

    
    /// The name of the file .packet that contains the structure of the packet
    char* filename;

private:

    ByteStream* tempHeader;

    ByteStream* tempDataField;

    ByteStream* tempDataFieldHeader;

    ByteStream* tempPacketDataField;

    ByteStream* tempTail;

    bool first_output_stream_setted;

};

}

#endif
