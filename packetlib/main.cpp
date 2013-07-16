#include "Device.h"
#include "Utility.h"
//#include "PacketLibDefinition.h"
#include <iostream>
#include "InputPacketStream.h"
#include "SDFRBBlock.h"
#include "OutputSocketClient.h"
#include "OutputPacketStream.h"
#include "ByteStream.h"
#include "Output.h"
#include "OutputFile.h"
#include "InputSocketServer.h"
#include "InputPacketStream.h"
#include "InputPacketStreamFile.h"
#include "Input.h"
#include "InputFile.h"
#include "PacketLibDemo.h"
#include "SDFBlockVariable.h"
#include "SDFBlockFixed.h"
#include <list>
#define APIDTM 767
using namespace PacketLib;
using namespace std;

int mainA() {
 	InputPacketStreamFile* ips = new InputPacketStreamFile();
    	ips->setFileNameConfig("bugs/4/CAL-DFE-TE.stream");
    	ips->createStreamStructure();

    	ips->setFileNameStream("bugs/4/mcal.raw");
    	ips->setInitialPosition(0);
   	ips->openInputStream();
		
   	ips->freeRun();

	list<ByteStream*> byteStreamPacketList;

    	for(int index=0; index< ips->getNumberOfFileStreamPointer(); index++)
    	{
      		Packet *p = ips->getPacketFromFileStreamPointer(index);
      		int apid = p->header->getFieldValue(3);
      		if (apid == 1294) {
			//make a copy of the byte stream
			ByteStream *b = new ByteStream(p->packet, 0, 0);
			byteStreamPacketList.push_back(b);
		}
		
	}
	list<ByteStream*>::const_iterator iter;
  	// Iterate through list and output each element.
	int i = 0;
  	for (iter=byteStreamPacketList.begin(); iter != byteStreamPacketList.end(); iter++)
  	{
		ByteStream* b = (ByteStream*)(*iter); 

		Packet* p = ips->getPacketType(3);
		cout << p->getName() << " " << b->getDimension() <<  endl;
		bool ok = p->setAndVerifyPacketValue(0, b);
		if(ok) {
			cout << p->header->getFieldValue(5) << endl; //get the source sequence counter
		}
		
 	}

}

int main() {
 	InputPacketStreamFile* ips = new InputPacketStreamFile();
    	ips->setFileNameConfig("bugs/4/CAL-DFE-TE.stream");
    	ips->createStreamStructure();

    	ips->setFileNameStream("bugs/4/mcal.raw");
    	ips->setInitialPosition(0);
   	ips->openInputStream();
		
   	ips->freeRun();

	list<FileStreamPointer*> fileStreamList;

    	for(int index=0; index< ips->getNumberOfFileStreamPointer(); index++)
    	{
      		Packet *p = ips->getPacketFromFileStreamPointer(index);
      		int apid = p->header->getFieldValue(3);
      		if (apid == 1294) {
			//make a copy of the byte stream
			FileStreamPointer* fsp = ips->getFileStreamPointer(index);
			fileStreamList.push_back(fsp);
		}
		
	}
	list<FileStreamPointer*>::const_iterator iter;
  	// Iterate through list and output each element.
	int i = 0;
  	for (iter=fileStreamList.begin(); iter != fileStreamList.end(); iter++)
  	{
		FileStreamPointer* fsp = (FileStreamPointer*)(*iter); 

		Packet *p = ips->getPacketFromFileStreamPointer(fsp->index);
		cout << p->getName() <<  endl;		
 	}

}

int mainrrr() {
 	InputPacketStreamFile* ips = new InputPacketStreamFile();
    	ips->setFileNameConfig("bugs/4/CAL-DFE-TE.stream");
    	ips->createStreamStructure();


    	ips->setFileNameStream("bugs/4/mcal.raw");
    	ips->setInitialPosition(0);
   	ips->openInputStream();
		
   	ips->freeRun();

    	list<Packet*> packetList;
	
    	for(int index=0; index< ips->getNumberOfFileStreamPointer(); index++)
    	{
      		Packet *p = ips->getPacketFromFileStreamPointer(index, true);
      		int apid = p->header->getFieldValue(3);
      		if (apid == 1294) {
			packetList.push_back( p );
			if(index == 300)
				break;
		}
		
	}
	list<Packet*>::const_iterator iter;
  	// Iterate through list and output each element.
  	for (iter=packetList.begin(); iter != packetList.end(); iter++)
  	{
		Packet* p = (Packet*)(*iter); 
		cout << p->getName()  <<  endl;
		
 	}
	sleep(30);

}


int maingrid() {

	

Output* out;	
	OutputPacketStream ops;
SDFRBBlock* bi, *bcX, *bcZ, *TAA1, *mcal;

	//create the structure
	ops.setFileNameConfig("bugs/tail/p3901.stream");
	ops.createStreamStructure();

	//parameter for output: file			
	out = (Output*) new OutputFile(ops.isBigEndian());
	char** param = (char**) new char* [2];
	param[0] = "./test.raw"; //nome file
	param[1] = 0;

	//open the output
	out->open(param);

	ops.setOutput(out);

	//send a TM packet
	Packet* p = ops.getPacketType(1);	
	
	cout << p->dataField->sourceDataField->getNumberOfFields() << endl;

	
	p->header->setFieldValue(3, APIDTM);
	//Get a pointer to the source data field
	SDFRBlock* sdf = (SDFRBlock*) p->dataField->sourceDataField;
	
	int block_3901_events = 1;
	int block_3901_1 = 1;
	int block_3901_2 = 1;
	int block_3901_3 = 1;
	int block_3901_4 = 1;
	//set the number of blocks of the sdf
	sdf->setNumberOfRealDataBlock(block_3901_events, 0); //N blocks for rtype 0
	//for each block of the sdf, set the number of sub-blocks
	for(int i=0; i < block_3901_events; i++) {
		//get the block i of type 0 of the source data field
		bi = sdf->getBlock(i, 0);   
		//set the number of blocks of sub-block of type 0 of block i of the sdf
		bi->setNumberOfRealDataBlock(block_3901_1, 0);	
		//set the number of blocks of sub-block of type 1 of block i of the sdf
		bi->setNumberOfRealDataBlock(block_3901_2, 1);
		//set the number of blocks of sub-block of type 2 of block i of the sdf
		bi->setNumberOfRealDataBlock(block_3901_3, 2);
		//set the number of blocks of sub-block of type 3 of block i of the sdf
		bi->setNumberOfRealDataBlock(block_3901_4, 3);
	}
	
	//--------------------------------------------------------
	//set the data field header values -----------------------
	//--------------------------------------------------------	
	p->dataField->dataFieldHeader->setFieldValue(3, 39);  //type: the value 39 in the field 3
	p->dataField->dataFieldHeader->setFieldValue(4, 1);   //subtype
	p->dataField->tail->setFieldValue(0, 13);
	cout << "sdf num of fields " << p->dataField->sourceDataField->getNumberOfFields() << endl;
	cout << "sdf dimension " << p->dataField->sourceDataField->getDimension() << endl; 
/*	char** cc =  p->dataField->sourceDataField->printValue();
	int num=0;
	while(cc[num] != 0) {
		cout << cc[num] << endl;
		num++;
	}*/	
	ByteStream* b = p->getOutputStream();
	ops.writePacket(p);
	out->close();
}

int main5() {
Input* in;
  	try {
	InputPacketStreamFile* ips = new InputPacketStreamFile();
	ByteStream* bs;
	bool endcycle = false;

	//create the structure
	ips->setFileNameConfig("bugs/tail/p3901.stream");
	ips->createStreamStructure();
	   	ips->setFileNameStream("bugs/tail/TM3901.raw");
	ips->setInitialPosition(0);
	ips->openInputStream();
	ips->freeRun();
   	Packet *p = ips->getPacketFromFileStreamPointer(0);
	cout << p->printSourceDataFieldStream() << endl;
	cout << p->dataField->sourceDataField->stream->printStreamInHexadecimal() << endl;
	cout << p->dataField->tail->getFieldValue(0) << endl;
	return 0;
	

	File* filepacket = new File(true);
	
	filepacket->open("bugs/tail/TM3901.raw", "r");
	
	cout << ips->packetLibVersion() << endl;
	
	cout << "INPUT: FILE" << endl;
	
	ByteStream* b0, *b1, *b2;
    	//BufferByteStream *br = new BufferByteStream;

        //filepacket->memBookmarkPos();
	int i=0;
	while(!filepacket->isEOF()) {
        	if(ips->thereIsPrefix()) //si scarta il prefix
           	 b0 = filepacket->getNByte(ips->getPrefixDimension());
        	else
            	b0 = 0;
        	int dimheader = ips->headerReference->getDimension();
        	b1 = filepacket->getNByte(dimheader);
        	ips->headerReference->setByteStream(b1);
       		 word pl = ips->headerReference->getPacketLength();

        	//filepacket->setLastBookmarkPos();

        	//b2 = filepacket->getNByte(ips->getDimPrefix() + dimheader + pl);
		b2 = filepacket->getNByte(pl);
		cout << b2->printStreamInHexadecimal() << endl;
		i++;
		if(i==10) return 1;
	}

} catch (PacketException* e) {
	cout << e->geterror() << endl;  
}
}



int readpacket(char* filename);

int main3 () {
try {
	cout << time(0) << endl;
    Output* out;
    OutputPacketStream ops;
	char* filename = "bugs/3/config_files/conf.stream";
    //create the structure
    ops.setFileNameConfig(filename);
    ops.createStreamStructure();

    //parameter for output: file			
    out = (Output*) new OutputFile(ops.isBigEndian());
    char** param = (char**) new char* [2];
    param[0] = "./test.raw"; //nome file
    param[1] = 0;

    //open the output
    out->open(param);

    ops.setOutput(out);

    // TM packet
    Packet* p = ops.getPacketType(1);	

    // Set header section
    p->header->setFieldValue(3, 1113);  

    // Set datation section
    p->dataField->dataFieldHeader->setFieldValue(3, 516);  // Number Of Week
    p->dataField->dataFieldHeader->setFieldValue_3_14(4, 66578);   // Seconds of Week
    p->dataField->dataFieldHeader->setFieldValue(6, 125);  // Internal Timer Value
    p->dataField->dataFieldHeader->setFieldValue(7, 23);   // Counter 1/32 Hz
    p->dataField->dataFieldHeader->setFieldValue(8, 56);   // Counter 1 Hz

    // Number of blocks is fixed
    p->dataField->setNumberOfRealDataBlock(268);

    // set data fields
    p->dataField->dataFieldHeader->setFieldValue(9, 45631); // WINDOWID
    p->dataField->dataFieldHeader->setFieldValue(10, 250);  // ADDNUMBER
    p->dataField->dataFieldHeader->setFieldValue(11, 10);   // PACKETNUM
    p->dataField->dataFieldHeader->setFieldValue(12, 8);    // PACKETCOUN
    p->dataField->dataFieldHeader->setFieldValue(14, 8);    // PIXELNUMBER

    SDFBlockFixed* sdf = (SDFBlockFixed*) p->dataField->sourceDataField;
    for (int i=0; i<268; i++) {
      // get a block of the source data field
      SDFBFBlock* block = sdf->getBlock(i);
      block->setFieldValue_3_13(0, 1456121); // PIXELVALUE
      block->setFieldValue(4, 16);
    }

    ops.writePacket(p);

    cout << "PACKET:      " << p->getName() << endl;
    cout << "Size:        " << p->getDimension() << endl;
    cout << "APID:        " << p->header->getFieldValue(3) << endl;
    cout << "Data Length: " << p->header->getFieldValue(6) << endl;
    cout << "HexStream:   " << p->packet_output->printStreamInHexadecimal() << endl;

    // Deallocate memory used by the packet
    p->deleteExternalByteStream();

    //close output
    out->close();
    
    readpacket(filename);
  }
  catch(PacketException* e) {
    cout << "ERROR-" << e->geterrorcode() << ": " << e->geterror() << endl;
  }
}

int main2() {
try {
	Output* out;	
	OutputPacketStream ops;
	char* filename = "bugs/tail/p3914.stream";
	//create the structure
	ops.setFileNameConfig(filename);
	ops.createStreamStructure();

	//parameter for output: file			
	out = (Output*) new OutputFile(ops.isBigEndian());
	char** param = (char**) new char* [2];
	param[0] = "./test.raw"; //nome file
	param[1] = 0;

	//open the output
	out->open(param);

	ops.setOutput(out);

	//send a TM packet
	Packet* p = ops.getPacketType(1);	

	// Number of blocks is fixed
	//p->dataField->sourceDataField->setNumberOfRealDataBlock(268);
	p->header->setFieldValue(3, 767); 
	
	// set data fields
	p->dataField->dataFieldHeader->setFieldValue(3, 39); 
	p->dataField->dataFieldHeader->setFieldValue(4, 14);  
	int nb = 1;
	p->dataField->setNumberOfRealDataBlock(nb);
	
	SDFBlockFixed* sdf = (SDFBlockFixed*) p->dataField->sourceDataField;
	for (int i=0; i<nb; i++) {
		// get a block of the source data field
		SDFBFBlock* block = sdf->getBlock(i);
		int nf = sdf->getNumberOfFields();
		for(int j=0; j<nf; j++)
			block->setFieldValue(j, j); // PIXELVALUE
	}

	
	p->dataField->tail->setFieldValue(0, 876);	
	ops.writePacket(p);
	cout << "PACKET:      " << p->getName() << endl;
	cout << "Size:        " << p->getDimension() << endl;
	cout << "Packet length:        " << p->header->getFieldValue(6) << endl;
	//cout << "Data Length: " << p->header->getFieldValue(6) << endl;
	//cout << "HexStream:   " << p->packet_output->printStreamInHexadecimal() << endl;
	cout << "Tail: " << p->dataField->tail->getFieldValue(0) << endl;
	cout << p->printPacketOutputStream() << endl;
	char** cc =  (char**)p->dataField->sourceDataField->printValue();
	int num=0;
	while(cc[num] != 0) {
		cout << cc[num] << endl;
		num++;
	}
	// Deallocate memory used by the packet
	p->deleteExternalByteStream();
	
	//close output
	out->close();
	
	readpacket(filename);
	

} catch (PacketException* e) {
	cout << e->geterror() << endl;  
}
}

void extractFields(Packet* p)
{
SourceDataField* sdf = p->dataField->sourceDataField;
int apid;	
	cout << "APID: " << (apid = p->header->getFieldValue(3)) << endl;
	cout << "Total dimension: " << p->getDimension() << endl;
	cout << "Packet Length: " << p->header->getFieldValue(6) << endl;
			Field* field = p->header->getFields(3);
		cout << "field name " << field->name << endl;
		cout << "field dimension " << field->dimension << endl;
		cout << "field value " << field->value << endl;
	cout << "number of blocks. " << p->dataField->getNumberOfRealDataBlock() << endl;
	//   cout << "Number Of Week: " << p->dataField->dataFieldHeader->getFieldValue(3) << endl;
	//   cout << "Seconds In Week: " << p->dataField->dataFieldHeader->getFieldValue_4_14(4) << endl;
	//   cout << "Internal Timer Value: " << p->dataField->dataFieldHeader->getFieldValue(6) << endl;
	//   cout << "Counter 1/32 Hz: " << p->dataField->dataFieldHeader->getFieldValue(7) << endl;
	//   cout << "Counter 1 Hz: " << p->dataField->dataFieldHeader->getFieldValue(8) << endl;
// 	char** cc =  p->dataField->sourceDataField->printValue();
// 	int num=0;
// 	while(cc[num] != 0) {
// 		cout << cc[num] << endl;
// 		num++;
// 	}
	
	switch (apid) {
	case 1103:
		cout << "ASTBKGROUNDID: " << p->dataField->dataFieldHeader->getFieldValue(9) << endl;
		for (int i=0; i<32; i++) {
		cout << "SUPIXELERR[" << i << "]: " << sdf->getFieldValue( i, 0)      << endl;
		cout << "MEANSKYSP["  << i << "]: " << sdf->getFieldValue_3_13( i, 1) << endl;
		cout << "VARSKYSP["   << i << "]: " << sdf->getFieldValue( i, 3)      << endl;
		cout << "MEANSKYBP["  << i << "]: " << sdf->getFieldValue_3_13( i, 4) << endl;
		// Work around to fix the problem
		//cout << "MEANSKYSP[" << i << "]: "  << ((long(sdf->getFieldValue( i, 1)) * 256) + long(sdf->getFieldValue( i, 2)) ) << endl;
		//cout << "MEANSKYBP[" << i << "]: "  << ((long(sdf->getFieldValue( i, 4)) * 256) + long(sdf->getFieldValue( i, 5)) ) << endl;
	}    
	break;
	case 1113:
		cout << "DIM " << sdf->getFields(0, 3)->dimension << endl;
		cout << "PROVA2 " << sdf->getFieldValue(0, 4) << endl;
		cout << "PIXELVALUE " << sdf->getFieldValue_3_13( 0, 0) << endl;;
		break;
	case 767:
		cout << "TAIL " << p->dataField->tail->getFieldValue(0) << endl;
		cout << p->printSourceDataFieldStream() << endl;
		cout << p->dataField->sourceDataField->getDimension() << endl;
	default: break;
	}
}


int readpacket(char* filename)   {
Input* in;
  	try {
	InputPacketStreamFile* ips = new InputPacketStreamFile();
	ByteStream* bs;
	bool endcycle = false;

	//create the structure
	ips->setFileNameConfig(filename);
	ips->createStreamStructure();
   
   	ips->setFileNameStream("./test.raw");
	ips->setInitialPosition(0);
	ips->openInputStream();
	ips->freeRun();
	
	cout << ips->packetLibVersion() << endl;
	
	cout << "INPUT: FILE" << endl;
	
	int numberPackets = ips->getNumberOfFileStreamPointer();
	cout << "  Number packets = " << numberPackets << endl;
	
	for(int index=0; index<numberPackets; index++)
	{
		cout << index << endl;
		Packet *p = ips->getPacketFromFileStreamPointer(index);
		if (p == NULL) {
			cout << "Packet not recognized." << endl;
		}
		else {
			cout << "PACKET: " << p->getName() << endl;
			cout << "Size: "   << p->getDimension() << endl;
			int apid = p->header->getFieldValue(3);  
			extractFields(p);
		}
		// Deallocate memory used by the packet
		if(p) p->deleteExternalByteStream();
	}	
		
	/*
	in = (Input*) new InputFile(ips.isBigEndian());
	cout << "INPUT: FILE" << endl;
	char** param = (char**) new (char*)[2];
	param[0] = "test.raw";
	param[1] = 0;

	//open input
	in->open(param);

	ips.setInput(in);	

	//crea l'input
	int i = 0;
	while (! in->isEOF()) {		
  		Packet* p = ips.readPacket();
		if( in->isEOF())
			break; 
		if(p->getPacketID() == 2) {			
  			cout << i++ << " INPUT: " << p->getName() << " - number of blocks: " << p->dataField->sourceDataField->getNumberOfRealDataBlock() << endl;
			cout << p->dataField->dataFieldHeader->getFieldValue_3_13(4) << endl;
			cout << p->dataField->sourceDataField->getFieldValue_4_14(1, 0) << endl;
			
			SDFBlockFixed* sdf = (SDFBlockFixed*) p->dataField->sourceDataField;
			SDFBFBlock* block = sdf->getBlock(0);
			cout << block->getFieldValue_5_1(0) << endl;
	
			//print the list of values
			char **c = p->dataField->sourceDataField->printValue();
			int i = 0;
			while(c[i])
				cout << c[i++] << endl;
		}
		//when you have finished to use the packet, it is important to
		//deallocate the memory allocated during the reading operation from input
		p->deleteExternalByteStream();
	}
	
	in->close();
	return 0;
*/
	//ByteStream *b = new ByteStream(10, false);
	/*Utility u;
  char* filenameConfig = "/home/bulgarelli/Projects/AGILE_TM_Generator/conf/AGILE_TM_GENERATOR.stream";
  char* filenameOutput = "/home/bulgarelli/3901.raw";
	Device d(true);
  Output* out;
    OutputPacketStream ops;
    SDFRBlock* sdf;
    SDFRBBlock* b0;
    SDFRBBlock* bcX, *TAA1, *mcal;
    char** param;
	cout << *Utility::wordToBinary((word)150, 6) << endl;
  cout << Utility::integerToString3("str%d", 3) << endl;


  InputPacketStream ips(filenameConfig);
  ips.createStreamStructure();
  Packet* p = ips.getPacketType(1);
  cout << "MAX DIMENSION " << p->getMaxDimension() << endl;

  sdf = (SDFRBlock*) p->dataField->sourceDataField;
  //the number of grid blocks
  sdf->setNumberOfRealDataBlock(1, 0);

  cout << "SDF nfields " << sdf->getNumberOfFields() << endl;

  b0 = sdf->getBlock(0, 0);
  
  b0->setNumberOfRealDataBlock(1, 0);
  b0->setNumberOfRealDataBlock(1, 1);
  b0->setNumberOfRealDataBlock(1, 2);
  b0->setNumberOfRealDataBlock(3, 3);
  
  cout << "Number of read data block of SDF: " << p->dataField->sourceDataField->getNumberOfRealDataBlock(0) << endl;

  cout << "Real Dimension of Packet: " << p->getDimension() << endl;

  //goto READP;
  //**************************************************************
  // Generate a tm grid packet
  //**************************************************************
	//crea la struttura dei telemetry packet in memoria
	ops.setFileNameConfig(filenameConfig);
	ops.createStreamStructure();

	//parametri per output: file
	out = (Output*) new OutputFile(ops.isBigEndian());
	param = (char**) new (char*)[2];
	param[0] = filenameOutput; //nome file
	param[1] = 0;

	//apri l'output
	out->open(param);

	//setta l'output specifico
	ops.setOutput(out);

    //invia un packet
	p = ops.getPacketType(1);
	p->header->setFieldValue(3, 1294);
	p->dataField->dataFieldHeader->setFieldValue(3, 39);
    p->dataField->dataFieldHeader->setFieldValue(4, 1);
    p->dataField->tail->setFieldValue(0, 11);

    //SI SETTANO ALCUNI VALORI
    sdf = (SDFRBlock*) p->dataField->sourceDataField;
    sdf->setNumberOfRealDataBlock(1, 0); //1 block for rtype 0
    b0 = sdf->getBlock(0, 0);   //get the block 0 of rblock 0
    b0->setNumberOfRealDataBlock(1, 0);
    b0->setNumberOfRealDataBlock(1, 1);
    b0->setNumberOfRealDataBlock(1, 2);
    b0->setNumberOfRealDataBlock(3, 3);
    sdf->setFieldValue(0, 1);   //set into the fixed part of SDF
    sdf->setFieldValue(1, 2);

    //get the cluster X block 0
    bcX = b0->getBlock(0, 0);
    bcX->setFieldValue(0, 2);
    TAA1 = b0->getBlock(2, 3);
    TAA1->setFieldValue(2, 1);
    mcal = b0->getBlock(0, 2);
    mcal->setFieldValue(1, 7);

    cout << "VERIFY: " << sdf->getFieldValue(0) << endl;  
    cout << "Real Dimension of Packet to be written " << p->getDimension() << endl;
    cout << "Total number of fields " << sdf->getNumberOfFields() << endl;
    ops.writePacket(p);
	//cout << p->packet_output->printStreamInHexadecimal() << endl;
    cout << p->packet_output->getDimension()<< endl;
	//chiudi l'output
	out->close();

    READP:
  //**************************************************************
  // Reopen and recognize the tm packet
  //**************************************************************
    Input* in;
  //parametri per input: file
	in = (Input*) new InputFile(ips.isBigEndian());	
	param = (char**) new (char*)[2];
	param[0] = filenameOutput;
	param[1] = 0;

	//apri l'input
	in->open(param);

	//setta il particolare tipo di input
	ips.setInput(in);

    p = ips.readPacket();
	cout << "Packet name: " << p->getName() << endl;
	cout << p->dataField->sourceDataField->stream->printStreamInHexadecimal()    << endl;
    cout << "READED: " <<  p->dataField->sourceDataField->getFieldValue(0) << endl;
    sdf = (SDFRBlock*) p->dataField->sourceDataField;
    cout << "Readed: number of block of SDF " << sdf->getNumberOfRealDataBlock() << endl;
    cout << "Readed: number of block of SDF " << sdf->getFieldValue(14) << endl;
    b0 = sdf->getBlock(0, 0);
    bcX = b0->getBlock(0, 0);
    mcal = b0->getBlock(0, 2);
    TAA1 = b0->getBlock(2, 3);
    cout << "Readed cluster X block 0 block 0 field 0: " << bcX->getFieldValue(0) << endl;
    cout << mcal->getFieldValue(1) << endl;
    cout << TAA1->getFieldValue(2) << endl;
    cout << TAA1->fixed.stream->printStreamInHexadecimal() << endl;

    cout << "CHECKSUM: " << p->dataField->tail->getFieldValue(0) << endl;

    p->printPacketValue();
	//chiudi l'input
	in->close();


    //*********************************************

  cout << " ----------------------- input packet stream file -------------" << endl;
  InputPacketStreamFile* ipsf = new InputPacketStreamFile() ;
	ipsf->setFileNameConfig(filenameConfig);
  ipsf->createStreamStructure();
	ipsf->setFileNameStream(filenameOutput);
	ipsf->setInitialPosition(0);
	ipsf->openInputStream();
	ipsf->freeRun();

 // p->printPacketValue();

 	word num = ipsf->getNumberOfPacketType();
	int stat[num];
	for(int i=0; i<num; i++)
		stat[i]=0;
	list<FileStreamPointer>::iterator it;
	for(it=ipsf->listOfFileStreamPointer.begin();it!=ipsf->listOfFileStreamPointer.end(); it++) {
		cout << it->nameOfPacket << " - " << it->index << endl;
		stat[it->typeOfPacket]++;
	}

	for(int i=0; i<num;i++) {
  	Packet* p = ipsf->getPacketType(i);
		cout << p->getName() << ":" << stat[i] << endl;
	}

  p = ipsf->getPacketFromFileStreamPointer(0);
  if(p == NULL)
    cout << "NULL NULL !!!!!!!!!!!!!!!" << endl;

  cout << "Packet name: " << p->getName() << endl;
  cout << "CHECKSUM: " << p->dataField->tail->getFieldValue(0) << endl;
    cout << "END" << endl;  
	return 1;*/
} catch (PacketException* e) {
    cout << e->geterror() << endl;
  
}
}
