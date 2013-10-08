/***************************************************************************
 *     begin                : Oct 08 2013
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

#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include "InputPacketStreamFileTest.h"

const char config[] = "p3901.stream";
const char file[] = "VC-01.P-033300.pkt";
const int good = 828;
const int bad = 5;

using namespace CppUnit;

void InputPacketStreamFileTest::setUp()
{
}
void InputPacketStreamFileTest::tearDown()
{
}

void InputPacketStreamFileTest::test()
{
	// loading an invalid file should raise an exception
	ips.setFileNameConfig((char*)"notafile");
	CPPUNIT_ASSERT_THROW(ips.createStreamStructure(), PacketLib::PacketExceptionIO*);

	// loading a valid config file should not raise an exception
	ips.setFileNameConfig((char*)config);
	CPPUNIT_ASSERT_NO_THROW(ips.createStreamStructure());

    ips.setInitialPosition(0L);

	// opening a valid input stream should not raise an exception
	ips.setFileNameStream((char*)file);
	CPPUNIT_ASSERT_NO_THROW(ips.openInputStream());

	// testing stream EOF should not raise an exception
	bool eof;
	CPPUNIT_ASSERT_NO_THROW(eof = ips.isInputStreamEOF());

	// getting a packet from the stream should not raise an exception
	PacketLib::Packet *p;
	CPPUNIT_ASSERT_NO_THROW(p = ips.getPacketFromStream());

    int count = 0;
    int countbad = 0;

	while(!eof) {
		if(p != 0) {
			count++;
			p->deleteExternalByteStream();
		}
		else
			countbad++;

		// testing stream EOF should not raise an exception
		CPPUNIT_ASSERT_NO_THROW(eof = ips.isInputStreamEOF());

		// getting a packet from the stream should not raise an exception
		CPPUNIT_ASSERT_NO_THROW(p = ips.getPacketFromStream());
	}

	// good packets number should be equal to its known value
	CPPUNIT_ASSERT_EQUAL(count, good);

	// bad packets number should be equal to its known value
	CPPUNIT_ASSERT_EQUAL(countbad, bad);
}
