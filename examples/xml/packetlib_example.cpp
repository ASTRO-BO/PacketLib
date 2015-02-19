/**************************************************************************e
 PacketLib example using RTA Prototype2 raw format
 ---------------------------------------------------------------------------
 copyright            : (C) 2015 Andrea Zoli
 email                : zoli@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/
#include <iostream>
#include <packet/PacketStream.h>
#include <packet/PacketBufferV.h>
#include <packet/Field.h>
#include <cstdlib>
#include <cassert>



int main(int argc, char* argv[])
{
	if(argc <= 2) {
		std::cout << "Wrong arguments, please provide config file and raw input file." << std::endl;
		std::cout << argv[0] << " config.xml input.raw" << std::endl;
		return 1;
	}

	// getting the xml description information through the Packet.
	PacketLib::PacketStream ps(argv[1]);
	PacketLib::Packet* packetType;
	try {
		packetType = ps.getPacketType("triggered_telescope1_30GEN");

		PacketLib::Field* apid = packetType->getPacketHeader()->getField("APID");
		std::cout << apid->getType() << std::endl;
		//assert(apid->getType() == PacketLib::LogicalFieldDataType::UINT11);
		//assert(apid->getName().compare("APID") == 0);
	
		PacketLib::Field* arrayID = packetType->getPacketDataFieldHeader()->getField("ArrayID");
		//assert(arrayID->getType() == PacketLib::LogicalFieldDataType::UINT16);
		//assert(arrayID->getName().compare("ArrayID") == 0);
		
	}
	catch(PacketLib::PacketException* e) {
		std::cerr << "Bad config file: " << e->geterror() << std::endl;
		exit(EXIT_FAILURE);
	}

	// load the event list from .raw file
	PacketLib::PacketBufferV rawPackets(argv[1], argv[2]);
	rawPackets.load();

	for(unsigned int i=0; i<10; i++) {
		PacketLib::ByteStreamPtr rawPacket = rawPackets.getNext();
		PacketLib::Packet* packet = ps.getPacket(rawPacket);
		
		//PacketLib::Field* blockfield = packet->getPacketSourceDataField()->getBlock(0)->getField("FADC00");
		//assert(blockfield->getType() == PacketLib::LogicalFieldDataType::UINT16);


		// use reflection interface to read content
		uint16_t apid = packet->getPacketHeader()->getFieldValue("APID");
		uint16_t arrayID = packet->getPacketDataFieldHeader()->getFieldValue("ArrayID");
		uint16_t npixels = packet->getPacketSourceDataField()->getFieldValue("Number of pixels");
		uint16_t nsamples = packet->getPacketSourceDataField()->getFieldValue("Number of samples");

		std::cout << apid << " " << arrayID << " " << npixels << " " << nsamples << std::endl;
		

		//get each single pixel as a 1-dimensional array
		for(unsigned int j=0; j<npixels; j++) {
			
			uint16_t* pix = (uint16_t*) packet->getPacketSourceDataField()->getBlock(j)->getByteStream()->getStream();
			for(uint16_t sample=0; sample<nsamples; sample++)
				cout << pix[sample] << " ";
			cout << endl;
			
		}
		
		//access to each single sample
		for(uint16_t pixel=0; pixel<npixels; pixel++) {
			for(uint16_t sample=0; sample<nsamples; sample++) {
				cout << packet->getPacketSourceDataField()->getBlock(pixel)->getFieldValue(sample) << " ";
			}
			cout << endl;
		}
		
		// use reflection interface to write content
		// similar the above using setFieldValue_16ui();

		/// get all the waveforms of a camera as 2-dimensional array
		PacketLib::byte* buff = packet->getData()->getStream();
		PacketLib::dword buffSize = packet->getData()->size();
		
		
	}

	return EXIT_SUCCESS;
}
