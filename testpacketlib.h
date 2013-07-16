/***************************************************************************
                          testpacketlib.h  -  description
                             -------------------
    begin                : Fri Feb 22 2002
    copyright            : (C) 2002 by Andrea Bulgarelli
    email                : bulgarelli@tesre.bo.cnr.it
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
#include "./packet/PacketLibDefinition.h"
#include "./packet/Utility.h"
#include "./packet/InputPacketStreamFile.h"
#include "./packet/FileStreamPointer.h"
#include "./packet/PacketExceptionFileFormat.h"
#define OUTPUT 1

using namespace PacketLib;

/**
  *@author Andrea Bulgarelli
	\date $Date: 2003/09/03 11:53:30 $
	$Header: /home/repository/cvs/gtb/PacketLib/testpacketlib.h,v 1.1.1.1 2003/09/03 11:53:30 andrea Exp $
	$Id: testpacketlib.h,v 1.1.1.1 2003/09/03 11:53:30 andrea Exp $
	$Name:  $
	$Log: testpacketlib.h,v $
	Revision 1.1.1.1  2003/09/03 11:53:30  andrea
	The PacketLib
	
	Revision 1.4  2002/11/13 15:16:35  andrea
	PacketLib 1.2.1 (beta). See ChangeLog 4 November 2002
	
	Revision 1.3  2002/05/13 09:14:19  agile
	*** empty log message ***
	
	Revision 1.2  2002/05/13 09:13:22  agile
	*** empty log message ***
	
	\version $Revision: 1.1.1.1 $
	$Source: /home/repository/cvs/gtb/PacketLib/testpacketlib.h,v $
  */

class TestPacketLib {
public: 
	TestPacketLib();
	~TestPacketLib();

  /** Questa test suite consente di verificare file di test CAL-DFE-TE */
  bool TestSuiteType1(char* nameOfTestSuite, char* fileNameConfig, char** file);
	
private: // Private attributes
  /**  */
  InputPacketStreamFile* ips;
  /** Crea la struttura dello stream sulla quale effettare il test */
  char* initStructure(char* fileNameConfig);
	bool test(char* file);
	bool test2(char* file);
};

#endif
