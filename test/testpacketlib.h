/***************************************************************************
                          testpacketlib.h  -  description
                             -------------------
    begin                : Fri Feb 22 2002
    copyright            : (C) 2013 by Andrea Bulgarelli
    email                : bulgarelli@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef TESTPACKETLIB_H
#define TESTPACKETLIB_H
#include "PacketLibDefinition.h"
#include "Utility.h"
#include "InputPacketStreamFile.h"
#include "FileStreamPointer.h"
#include "PacketExceptionFileFormat.h"
#define OUTPUT 1

using namespace PacketLib;



class TestPacketLib {
public:
    TestPacketLib();
    ~TestPacketLib();


    bool TestSuiteType1(char* nameOfTestSuite, char* fileNameConfig, char** file);

private: // Private attributes

    InputPacketStreamFile* ips;
    char* initStructure(char* fileNameConfig);
    bool test(char* file);
    bool test2(char* file);
};

#endif
