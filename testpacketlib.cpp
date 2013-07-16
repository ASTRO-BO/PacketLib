/***************************************************************************
                          testpacketlib.cpp  -  description
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

#include "testpacketlib.h"



TestPacketLib::TestPacketLib(){
	ips = new InputPacketStreamFile();
}

TestPacketLib::~TestPacketLib(){
	delete ips;
}

char* TestPacketLib::initStructure(char* fileNameConfig){
try {
	
	ips->setFileNameConfig(fileNameConfig);
  ips->createStreamStructure();

	//delete this line
//	Packet* p = ips.getPacketType(1);
//  int dim = p->getDimension();


	return 0;
}
catch(PacketExceptionIO* e) {
	return (char*) e->geterror();
}
catch(PacketExceptionFileFormat* e) {
	return (char*) e->geterror();
}


}


bool TestPacketLib::TestSuiteType1(char* nameOfTestSuite, char* fileNameConfig, char** file){
char* ret;
bool ret2 = true;
//bool retb;
try {
	if(OUTPUT) cout << "--------------------------------------------------" << endl;
	if(OUTPUT) cout << "START OF " << nameOfTestSuite << " with the file " << fileNameConfig << endl;
	ret=initStructure(fileNameConfig);
	if(ret != 0) {
		cout << ret;
		return false;
	}
  if(OUTPUT) cout << "OK: Stream structure created" << endl;
	//for(int j=0; j<3; j++) {
		for(int i=0; file[i] != 0; i++)
		  if(!test2(file[i]))
				ret2 = false;		
	//}
	if(!ret2)
			return false;
		else          	
			return true;
}
catch(PacketExceptionIO* e) {
	if(OUTPUT) cout << "ERROR: " << (char*) e->geterror();
	return false;
}
catch(PacketExceptionFileFormat* e) {
	if(OUTPUT) cout << "ERROR: " << (char*) e->geterror();
	return false;
}
}

bool TestPacketLib::test(char* file) {
try{
long index ;
	cout << "TEST: " << file << endl;
	ips->setFileNameStream(file);
	ips->setInitialPosition(0L);
	ips->openInputStream();
	if(OUTPUT) cout << "OK: Data file opened" << endl;
	if(!ips->freeRun()) {
		if(OUTPUT) cout << "ERROR: freeRun failed";
		return false;
	}
	index = ips->getNumberOfFileStreamPointer();
	if(OUTPUT) cout << "OK: construction of FileStreamPointer. Found " << index << " packet" << endl;
	for(int i=0; i< index; i++)  {
		FileStreamPointer* fsp = ips->getFileStreamPointer(i); 	
		if(!fsp->typeOfPacket) {
			if(OUTPUT) cout << "ERROR: packet not recognized" << endl;
     	return false;
		}				
	}
	if(OUTPUT) cout << "OK: all the packet are recognized" << endl;
	return true;
}
catch(PacketExceptionIO* e) {
	if(OUTPUT) cout << "ERROR: " << (char*) e->geterror();
	return false;
}
catch(PacketExceptionFileFormat* e) {
	if(OUTPUT) cout << "ERROR: " << (char*) e->geterror();
	return false;
}
}


bool TestPacketLib::test2(char* file) {
try{
	cout << "TEST: " << file << endl;
	ips->setFileNameStream(file);
	ips->setInitialPosition(0L);
	ips->openInputStream();
	if(OUTPUT) cout << "OK: Data file opened" << endl;
	long count = 0;
	long countbad = 0;
	Packet* p;
	while(!ips->isInputStreamEOF()) {
		p = ips->getPacketFromStream();
   	if(p != 0) {
			count++;
			p->deleteExternalByteStream();	
		}
		else
			if(!ips->isInputStreamEOF()) {
				countbad++;
			}		
	}
	if(p != 0)
			p->deleteExternalByteStream();
	cout << "Bad: " << countbad << endl;
	cout << "OK: " << count << endl;	
	return true;
}
catch(PacketExceptionIO* e) {
	if(OUTPUT) cout << "ERROR: " << (char*) e->geterror();
	return false;
}
catch(PacketExceptionFileFormat* e) {
	if(OUTPUT) cout << "ERROR: " << (char*) e->geterror();
	return false;
}
}
