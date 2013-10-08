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

#ifndef INPUTPACKETSTREAMFILE_H
#define INPUTPACKETSTREAMFILE_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "InputPacketStreamFile.h"

class InputPacketStreamFileTest : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(InputPacketStreamFileTest);
	CPPUNIT_TEST(test);
	CPPUNIT_TEST_SUITE_END(); 

public: 
    void setUp();
    void tearDown();

protected:
	void test();

private:
	PacketLib::InputPacketStreamFile ips;
};

#endif
