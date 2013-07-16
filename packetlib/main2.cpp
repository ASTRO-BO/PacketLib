/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Fri Jan 18 11:12:04 CET 2002
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


#include "./packet/PacketLibDefinition.h"
#include "./packet/Utility.h"
#include "./packet/InputPacketStreamFile.h"
#include "./packet/FileStreamPointer.h"
#include "./packet/PacketExceptionFileFormat.h"
#include "./packet/Output.h"
#include "./packet/OutputFile.h"
#include "./packet/MemoryBuffer.h"
#include "testpacketlib.h"
#include <unistd.h>
#include <time.h>

clock_t start;
clock_t end;
time_t timevar1;
time_t  timevar2;	
word ssc = 0;



Output* output;





void report() {
	cout << "-------------------------------------------" << endl;
  printf("Time0: %6.4f\n", (double)(clock() - (double)start) / CLOCKS_PER_SEC);
	//cout << "Time1: " << (double)(clock() - (double)start) / CLOCKS_PER_SEC << endl;
 	time(&timevar2);
	cout << "Time: " << timevar2-timevar1 << endl;
	cout << "Number of ByteStream without memory allocation (responsibility): " << ByteStream::count_object2 << " mem allocated: " << ByteStream::count_object2 * sizeof(ByteStream) << endl;
	cout << "Number of ByteStream deleted: " << ByteStream::count_object_deleted2 << " mem free: " << ByteStream::count_object_deleted2 * (long)sizeof(ByteStream) << endl;

	cout << "Number of ByteStream with memory allocation (responsibility): " << ByteStream::count_object << " mem allocated: " << ByteStream::count_object * sizeof(ByteStream) << endl;
	cout << "Number of ByteStream external deleted: " << ByteStream::count_object_deleted << " mem free: " << (long)(ByteStream::count_object_deleted * (long)sizeof(ByteStream)) << endl;


	cout << "Number of byte read by File class: " << File::byte_read <<  endl;
	cout << "Number of char read by File class: " << File::char_read <<  endl;
}




int main(int argc, char *argv[])
{
long count = 0;
long countbad = 0;


  /*
MemoryBuffer* mm = new MemoryBuffer();
	mm->loadBuffer("./CAL-DFE-TE/stream.stream");
	int dim = mm->getBufferDimension();
	for(int i=0; i<dim; i++)
		cout << mm->getbuffer() << endl;
  cout << "--" << endl;

	mm->saveBuffer("./CAL-DFE-TE/pippo.txt");

return 0;  	
*/
time_t  timevar2;	
try {

InputPacketStreamFile* ips = new InputPacketStreamFile();
/*InputPacketStream* ips2 = new InputPacketStream();
InputPacketStream* ips3 = new InputPacketStream();
InputPacketStream* ips4 = new InputPacketStream();*/
//cout << Utility::extractFileName("/data1/archive/raw/science/0506/cer05060_011018.hrt");
//char* c = new char[1048576];
//sleep(1);
TestPacketLib* tpl = new TestPacketLib;
TestPacketLib* tp2 = new TestPacketLib;
TestPacketLib* tp3 = new TestPacketLib;
//TEST SUITE 1



char** t1 = new (char*)[6];
	t1[0]="./CAL-DFE-TE/data/10BURT.RAW";
  t1[1]="./CAL-DFE-TE/data/03bursts.raw";
	t1[2]="./CAL-DFE-TE/data/03grids.raw";
  t1[3]="./CAL-DFE-TE/data/06grids.raw";
	t1[4]="./CAL-DFE-TE/data/15grids.raw";
	t1[5]=0;

char** t2 = new (char*)[20];
  t2[0]="./CAL-CSIBarsTE/data/0508/cer05080_011018.hrt";
	t2[1]="./CAL-CSIBarsTE/data/0508/cer05089_011019.hrt";
  t2[2]="./CAL-CSIBarsTE/data/0508/cer05084_011018_.hrt";
	t2[3]="./CAL-CSIBarsTE/data/0508/cer05087_011019__.hrt";
	t2[4]="./CAL-CSIBarsTE/data/0500/cer05008_011018.hrt";
  t2[5]="./CAL-CSIBarsTE/data/0508/cer05085_011018_.hrt";
	t2[6]="./CAL-CSIBarsTE/data/0508/cer05081_011018.hrt";
	t2[7]="./CAL-CSIBarsTE/data/0508/cer05082_011018.hrt";
	t2[8]="./CAL-CSIBarsTE/data/0508/cer05083_011018.hrt";
	t2[9]="./CAL-CSIBarsTE/data/0508/cer05088_011019.hrt";

  t2[10]="./CAL-CSIBarsTE/data/0508/cer05080_011018.hrt";
	t2[11]="./CAL-CSIBarsTE/data/0508/cer05089_011019.hrt";
  t2[12]="./CAL-CSIBarsTE/data/0508/cer05084_011018_.hrt";
	t2[13]="./CAL-CSIBarsTE/data/0508/cer05087_011019__.hrt";
	t2[14]="./CAL-CSIBarsTE/data/0500/cer05008_011018.hrt";
	t2[15]="./CAL-CSIBarsTE/data/0508/cer05081_011018.hrt";
	t2[16]="./CAL-CSIBarsTE/data/0508/cer05082_011018.hrt";
	t2[17]="./CAL-CSIBarsTE/data/0508/cer05083_011018.hrt";
	t2[18]="./CAL-CSIBarsTE/data/0508/cer05088_011019.hrt";

	t2[10]=0;


  //t2[0]="./CAL-CSIBarsTE/data/0508/cer05084_011018_.hrt";
	//t2[1]=0;

char** t3 = new (char*)[6];
  t3[0]="./Proto-MCAL-TE/data/vme_burst_telemetry_file.raw";
	t3[1]="./Proto-MCAL-TE/data/ite00024_020326.prt";
  /*t3[2]="./data/0508/cer05084_011018_.hrt";
	t3[3]="./data/0508/cer05087_011019__.hrt";
	t2[4]="15grids.raw";*/
	t3[2]=0;


//goto notest;
  //sleep(1);

//delete[] c;
//goto notest;
  bool ret1, ret2, ret3;	
	if(!(ret1=tpl->TestSuiteType1("TEST SUITE 1","./CAL-DFE-TE/stream.stream", t1)))
		cout << "TEST SUITE 1 FAILED" << endl;
  else
		cout << "TEST SUITE 1 OK" << endl;

	if(!(ret2=tp2->TestSuiteType1("TEST SUITE 2","./CAL-CSIBarsTE/CAL-CSIBarsTE.stream", t2)))
		cout << "TEST SUITE 2 FAILED" << endl;
  else
		cout << "TEST SUITE 2 OK" << endl;		

	if(!(ret3=tp3->TestSuiteType1("TEST SUITE 3","./Proto-MCAL-TE/stream.stream", t3)))
		cout << "TEST SUITE 3 FAILED" << endl;
  else
		cout << "TEST SUITE 3 OK" << endl;		

//	delete tpl;
	//delete tp2;
	//delete tp3;
 	if(!ret1)
		cout << "TEST SUITE 1 FAILED" << endl;
  else
		cout << "TEST SUITE 1 OK" << endl;
 	if(!ret2)
		cout << "TEST SUITE 2 FAILED" << endl;
  else
		cout << "TEST SUITE 2 OK" << endl;
 	if(!ret3)
		cout << "TEST SUITE 3 FAILED" << endl;
  else
		cout << "TEST SUITE 3 OK" << endl;


  report();
// 	tm_int=localtime(&timevar1);


delete[] t1;
delete[] t2;
delete[] t3;

return 0;

//notest:

	ips->setFileNameConfig("./CAL-DFE-TE/stream.stream");
  ips->createStreamStructure();
	ips->setFileNameStream("./CAL-DFE-TE/data/03bursts.raw");
	ips->openInputStream();

	while(!ips->isInputStreamEOF()) {
		Packet* p = ips->getPacketFromStream();
   	if(p != 0)
			count++;
		else
			if(!ips->isInputStreamEOF())
				countbad++;
	}
	cout << "Bad: " << countbad << endl;
	cout << "OK: " << count << endl;	
	delete ips;

delete tpl;
delete[] t1;
delete[] t2;
delete[] t3;

  cout << "end of program" << endl;

return 0;
notest:

{
	char in;
	int index = 0;
	char* c;
  char** cc;
	InputPacketStreamFile ips("./CAL-DFE-TE/stream.stream", "/home/agile/data-testsuite/CAL-DFE-TE/10BURT.RAW", 0L) ;
  //string* fileNameConfig = new string();
  ips.createStreamStructure();
	ips.openInputStream();
  //FileStream* f = ips.inputStream;
	//cout << "EOF: " << f->isEOF() << endl;
	ips.freeRun();
	while(in != EOF) {		
		Packet* p = ips.getPacketFromFileStreamPointer(index);
		FileStreamPointer* fsp = ips.getFileStreamPointer(index);
		cout << "-------------------------------------------" << endl;
		cout << "Position in file byte: " << fsp->pointerStart << endl;
    cout << "Dimension of packet: " << p->getDimension() << endl;
			cout << (p->getName()) << endl;
			cout << "Prefix hex:" << endl;
			c = p->prefix->printStreamInHexadecimal();		
			cout << c << endl;			
			cout << "Header hex:" << endl;			
			c = p->header->stream->printStreamInHexadecimal();		
			cout << c << endl;
			cout << p->header->stream->getValue(1,2) << endl;
			cout << "Header fields:" << endl;
			cc = p->header->printValue();
			for(int i=0; cc[i] != 0; i++)
				cout << cc[i] << endl;

			cout << "Data field header hex:" << endl;
			c =  p->dataField->dataFieldHeader->stream->printStreamInHexadecimal();
			cout << c << endl;
			cout << "Data field header fields:" << endl;
			cc =  p->dataField->dataFieldHeader->printValue();
			for(int i=0; cc[i] != 0; i++)
				cout << cc[i] << endl;	

			//cout << "Source Data field hex:" << endl;
			//c =  p->dataField->sourceDataField->stream->printStreamInHexadecimal();
			//cout << c << endl;
			/*cout << "Source Data field fields:" << endl;
			cc =  p->dataField->sourceDataField->printValue();
			for(int i=0; cc[i] != 0; i++)
				cout << cc[i] << endl;	
        */

		cin >> &in;
		switch(in) {
    case 'n': index++; break;
		case 'p': index--; break;
		case 'q': return 0; break;
		}

			//	index++;
		cout << "INDEX: " << index << endl;
	}
  PRINTDEBUG("stream closed");
	return 0;
}
}
catch(PacketExceptionIO* e) {
	cout << e->geterror();
}
catch(PacketExceptionFileFormat* e) {
	cout << e->geterror();
}

cout << "End";
exit(0);
}
