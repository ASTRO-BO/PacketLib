/***************************************************************************
                          Packet.h  -  description
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001 by Andrea Bulgarelli
    email                : bulgarelli@bo.iasf.cnr.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/
#ifndef PACKET_H_HEADER_INCLUDED_C37705A5
#define PACKET_H_HEADER_INCLUDED_C37705A5

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

//##ModelId=3C0F6C19034E
//##Documentation
//## Memory management: the ByteStrem passed to an object of this class isn't delete
//## to this class. The responsibility to delete the ByteStream is of the caller.
//## For deleting the external ByteStream of this class it's possible to call the
//## deleteExternalByteStream() method.
//##	$Date: 2012/06/08 15:14:29 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/Packet.h,v 1.6 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Id: Packet.h,v 1.6 2012/06/08 15:14:29 bulgarelli Exp $
//##	$Revision: 1.6 $
//##	\brief Represent a single packet.
class Packet
{
public:

    //##ModelId=3C0F6C1A0187
    //##Documentation
    //## Constructor
    Packet(bool bigendian);

    //##ModelId=3EADC12C026C
    //##Documentation
    //## Distruttore
    virtual ~Packet();

    //##ModelId=3C14BA710151
    virtual bool createPacketType(char* fileName, bool prefix, word dimprefix) throw (PacketException*);

    //##Documentation
    //## This method verifies if the ByteStream on argument contains the correct value
    //## in the identifiers. If this is true, the method return true and the stream
    //## contains a packet of this type. This method overloads another method.
    //## \post A side effects of this method is that the value of fields of packet are set with
    //## correct value.
    virtual bool setAndVerifyPacketValue(ByteStream* prefix, ByteStream* packetHeader, ByteStream* packetDataField);

    //##ModelId=3EADC12E0025
    //##Documentation
    //## This method verifies if the ByteStream on argument contains the correct value
    //## in the identifiers. If this is true, the method returns true and the stream
    //## contains a packet of this type. This method overloads another method.
    //## \post A side effect of this method is that the values of fields of packet are set with
    //## correct value
    virtual bool setAndVerifyPacketValue(ByteStream* prefix, ByteStream* packet);

    //##ModelId=3C301E890023
    //##Documentation
    //## 	Sets all the fields of the packet with correct value contained into the input ByteStream.
    //##	\pre The structure of the stream must be loaded.
    //##  \param prefix This is the prefix of the packet
    //##  \param packetHeader This is the header of the packet
    //## \param packetDataField This is the data field of the packet
    //## \post If return is true all the fields are set with the correct value.
    virtual bool setPacketValue(ByteStream* prefix, ByteStream* packetHeader, ByteStream* packetDataField);

    //##ModelId=3EADC12F0160
    //##Documentation
    //## 	Sets all the fields of the packet with correct value contained into the input ByteStream.
    //##	\pre The structure of the stream must be loaded.
    //##  \param prefix This is the prefix of the packet
    //##  \param packet This is the packet
    //## \post If return is true all the fields are set with the correct value.
    virtual bool setPacketValue(ByteStream* prefix, ByteStream* packet);

    //##ModelId=3EADC12F03B1
    //##Documentation
    //## 	Verifies if within the ByteStream passed with arguments it's present a correct packet.
    //##	\pre The structure of the stream must be loaded.
    //##  \param prefix This is the prefix of the packet
    //##  \param packet This is the packet
    //## \return True if the ByteStream contains a packet
    bool verifyPacketValue(ByteStream* prefix, ByteStream* packet);

    //##ModelId=3EADC13001D3
    //##Documentation
    //## 	Verifies if within the ByteStream passed with arguments it's present a correct packet.
    //##	\pre The structure of the stream must be loaded.
    //##  \param prefix This is the prefix of the packet.
    //##  \param packetHeader This is the header of the packet.
    //## 	\param packetDataField This is the data field of the packet.
    //## 	\return True if the ByteStream contains a packet.
    bool verifyPacketValue(ByteStream* prefix, ByteStream* packetHeader, ByteStream* packetDataField);

    //##ModelId=3EADC13100D6
    //##Documentation
    //## Prints to stdout the value of packet data field in a formatted mode.
    virtual void printPacketValue();

    //##Documentation
    //## Prints the hexadecimal dump of the prefix.
    virtual  char* printPrefixStream();

    //##Documentation
    //## Prints the header values.
    virtual  char** printHeaderValue();

    //##Documentation
    //## Prints the hexadecimal dump of the header.
    virtual  char* printHeaderStream();

    //##Documentation
    //## Prints the data field header values.
    virtual  char** printDataFieldHeaderValue();

    //##Documentation
    //## Prints the hexadecimal dump of the data field header.
    virtual  char* printDataFieldHeaderStream();

    //##Documentation
    //## Prints the source data field values.
    virtual  char** printSourceDataFieldValue();

    //##Documentation
    //## Prints the hexadecimal dump of the source data field.
    virtual  char* printSourceDataFieldStream();

    //##Documentation
    //## Prints the tail values
    virtual  char** printTailValue();

    //##Documentation
    //## Print he hexadecimal dump of the tail.
    virtual  char* printTailStream();

    virtual  char* printPacketOutputStream();

    //##ModelId=3EADC131018A
    //##Documentation
    //## Gets the dimension in byte of the current packet.
    dword getDimension();

    //##ModelId=3EADC13101E9
    //##Documentation
    //## Gets the max dimension in byte of the packet.
    dword getMaxDimension();

    //##Documentation
    //## Gets the ByteStream received as input
    ByteStream* getInputStream();

    //##ModelId=3EADC132003F
    //##Documentation
    //## Gets the packet generated with the generateStream() method. The output
    //## packet is generated during this call.
    ByteStream* getOutputStream();

    //##ModelId=3EADC131024A
    //##Documentation
    //## Gets the name of packet.
    virtual char* getName()
    {
        return name;
    }

    //##Documentation
    //## The name of the file .packet that contains the structure of the packet
    virtual char* getFileName()
    {
        return filename;
    }

    //##ModelId=3C187751008D
    //##Documentation
    //## Prints to stdout the identifiers of the packet.
    virtual void printIdentifiers();

    //##ModelId=3EADC1310364
    //##Documentation
    //## Deletes the ByteStream passed as arguments.
    virtual void deleteExternalByteStream();

    //##ModelId=3EADC13200A5
    //##Documentation
    //## Writes property of byte packetID.
    virtual void setPacketID(const byte& value);

    //##ModelId=3EADC1320266
    //##Documentation
    //## Read property of byte packetID.
    virtual const byte& getPacketID();


    //##ModelId=3EADC1320336
    bool thereIsPrefix();

    //##Documentation
    //## This attribute represents the packet header.
    PacketHeader *header;

    //##Documentation
    //## This attribute represent the packet data field.
    PacketDataField *dataField;

    //##ModelId=3EADC12A0365
    //##Documentation
    //## the prefix of the packet.
    ByteStream* prefix;

    //##ModelId=3EADC12A0382
    //##Documentation
    //## The ByteStrem of the packet read
    ByteStream* packet;

    //##ModelId=3EADC12A039E
    //##Documentation
    //## This is the ByteStream generated with generateStream().
    ByteStream* packet_output;


protected:

    //##ModelId=3EADC13203A3
    //##Documentation
    //## Generates the stream for output.
    //## \pre the number of block and the number of element for each block
    //## must be set (if appliable)
    virtual void generateStream();


    //##ModelId=3C1877510044
    //##Documentation
    //## Loads the configuration of identifiers from file .packet.
    virtual bool loadIdentifiers(ConfigurationFile& file);

    //##ModelId=3EADC12A03B8
    //##Documentation
    //## This is the number that identifies the packet in the .stream file
    byte packetID;

    //##ModelId=3EADC12B006D
    //##Documentation
    //## The name of the packet
    char* name;

    //##ModelId=3EADC12B010E
    //##Documentation
    //## List of identifiers. This identifiers permits to identify if the stream contains
    //## a particular type of packet
    PacketIdentifier** identifiers;

    //##ModelId=3EADC12B012E
    //##Documentation
    //## List of bool that indicates which part of packet are presents into one or more
    //## identifiers. 0 is the header, 1 is the data field header, 2 is the source data field
    bool type_of_identifier[3];

    //##ModelId=3EADC12B01D4
    unsigned number_of_identifier;

    //##ModelId=3EADC13301AB
    bool setPacketValuePrefix(ByteStream* prefix);

    //##ModelId=3EADC133035E
    bool setPacketValueVerify(ByteStream* prefix, ByteStream* packetHeader, ByteStream* packetDataField);

    //##ModelId=3EADC13403C2
    bool setPacketValueDataFieldHeader(ByteStream* packetDataField);

    //##ModelId=3EADC13501A2
    bool setPacketValueSourceDataField(ByteStream* packetDataField);

    //##ModelId=3EADC1350364
    bool setPacketValueHeader(ByteStream* header);

    bool setPacketValueTail(ByteStream* packetDataField);

    //##ModelId=3EADC1360145
    void memByteStream(ByteStream* prefix, ByteStream* packetHeader, ByteStream* packetDataField);

    //##ModelId=3EADC1370165
    void memByteStream(ByteStream* prefix, ByteStream* packet);

    //##ModelId=3EADC12B027F
    bool bigendian;

    //##ModelId=3EADC12B032D
    bool thereisprefix;

    //##ModelId=3EADC12B03DC
    word dimPrefix;

    //##Documentation
    //## The name of the file .packet that contains the structure of the packet
    char* filename;

private:

    //##ModelId=3EADC12C001B
    ByteStream* tempHeader;

    //##ModelId=3EADC12C0043
    ByteStream* tempDataField;

    //##ModelId=3EADC12C006A
    ByteStream* tempDataFieldHeader;

    //##ModelId=3EADC12C0090
    ByteStream* tempPacketDataField;

    ByteStream* tempTail;

    //##ModelId=3EADC12C00B6
    bool first_output_stream_setted;

};

}

#endif
