/***************************************************************************
 *     begin                : Oct 07 2013
 *     copyright            : (C) 2013 Andrea Zoli
 *     email                : zoli@iasfbo.inaf.it
***************************************************************************/

/***************************************************************************
*                                                                         *
*   This program is free software for non commercial purpose              *
*   and for public research institutes; you can redistribute it and/or    *
*   modify it under the terms of the GNU General Public License.          *
*   For commercial purpose see appropriate license terms                  *
*                                                                         *
***************************************************************************/

//#include<sstream>
//#include<fstream>
//#include<iomanip>
#include "InputPacketStreamFile.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>
#include<unistd.h>

const char config[] = "p3901.stream";

const int NFILES = 1;

const char* files[NFILES] = { "VC-01.P-033300.pkt" };

const int good[NFILES] = {100};
const int bad[NFILES] = {5};

BOOST_AUTO_TEST_CASE(input_packet_stream_file)
{
	PacketLib::InputPacketStreamFile ips;

	// loading an invalid file should raise an exception
	ips.setFileNameConfig((char*)"notafile");
	BOOST_CHECK_THROW(ips.createStreamStructure(), PacketLib::PacketExceptionIO*);

	// loading a valid config file should not raise an exception
	ips.setFileNameConfig((char*)config);
	BOOST_CHECK_NO_THROW(ips.createStreamStructure());

	for(int i=0; i<NFILES; i++)
	{
        ips.setInitialPosition(0L);

		// opening a valid input stream should not raise an exception
		ips.setFileNameStream((char*)files[i]);
		BOOST_CHECK_NO_THROW(ips.openInputStream());

		// testing stream EOF should not raise an exception
		bool eof;
		BOOST_CHECK_NO_THROW(eof = ips.isInputStreamEOF());

		// getting a packet from the stream should not raise an exception
		PacketLib::Packet *p;
		BOOST_CHECK_NO_THROW(p = ips.getPacketFromStream());

        long count = 0;
        long countbad = 0;

		while(!eof) {
			if(p != 0) {
				count++;
				p->deleteExternalByteStream();
			}
			else
				countbad++;

			// testing stream EOF should not raise an exception
			BOOST_CHECK_NO_THROW(eof = ips.isInputStreamEOF());

			// getting a packet from the stream should not raise an exception
			BOOST_CHECK_NO_THROW(p = ips.getPacketFromStream());
		}

		// good packets number should be equal to its known value
		BOOST_CHECK_EQUAL(count, good[i]);

		// bad packets number should be equal to its known value
		BOOST_CHECK_EQUAL(countbad, bad[i]);
	}
}

BOOST_AUTO_TEST_CASE(input_packet_stream_file_freerun)
{
	PacketLib::InputPacketStreamFile ips;

	// loading an invalid file should raise an exception
	ips.setFileNameConfig((char*)"notafile");
	BOOST_CHECK_THROW(ips.createStreamStructure(), PacketLib::PacketExceptionIO);

	// loading a valid config file should not raise an exception
	ips.setFileNameConfig((char*)config);
	BOOST_CHECK_NO_THROW(ips.createStreamStructure());

	for(int i=0; i<NFILES; i++)
	{
        ips.setInitialPosition(0L);

		// opening a valid input stream should not raise an exception
		ips.setFileNameStream((char*)files[i]);
		BOOST_CHECK_NO_THROW(ips.openInputStream());

		// getting a packet from the stream should not raise an exception
		PacketLib::Packet *p;
		BOOST_CHECK_NO_THROW(p = ips.getPacketFromStream());

		// executing free run should not raise an exception
		BOOST_CHECK_NO_THROW(ips.freeRun());

        long num = ips.getNumberOfFileStreamPointer();
		for(int i=0; i<num; i++) {
			PacketLib::FileStreamPointer* fsp;
			// getting a FileStreamPointer should not raise an exception
			BOOST_CHECK_NO_THROW(fsp = ips.getFileStreamPointer(i));

			// type of packet should be != 0
			BOOST_CHECK(fsp->typeOfPacket != 0);
		}
	}
}
