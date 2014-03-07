/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Sat Oct 26 15:31:22 CEST 2004
    copyright            : (C) 2002 by Andrea Bulgarelli
    email                : bulgarelli@bo.iasf.cnr.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream.h>
#include <stdlib.h>
#include "OutputSocketClient.h"
#include "OutputPacketStream.h"
#include "ByteStream.h"
#include "Output.h"
#include "OutputFile.h"

using namespace PacketLib;

int main(int argc, char *argv[])
{
  try {
	Output* out;
	OutputPacketStream ops;

	//create the structure
	ops.setFileNameConfig("config_files/BURST.stream");
	ops.createStreamStructure();

	//parameter for output: socket client
	out = (Output*) new OutputSocketClient(ops.isBigEndian());
	cout << "OUTPUT: SOCKET CLIENT 20000" << endl;
	char** param = (char**) new (char*)[3];
	param[0] = "localhost"; //host
	param[1] = "20000";	//porta
	param[2] = 0;

	//parameter for output: file			
	/*out = (Output*) new OutputFile(ops.isBigEndian());
	char** param = (char**) new (char*)[2];
	param[0] = "../../test.raw"; //nome file
	param[1] = 0;*/

	//open the output
	out->open(param);

	ops.setOutput(out);

	//send a byte stream
	/*ByteStream* bl = new ByteStream(10, ops.isBigEndian());
	for(int i=0; i< 10; i++)
		bl->setByte(i, i);

	out->writeByteStream(bl);
	out->writeByteStream(bl);
    */


	//send a TC packet
	Packet* p = ops.getPacketType(2);	
	p->header->setFieldValue(3, 257);
	p->header->setFieldValue(5, 1);
	cout << "OUTPUT: ";

	ops.writePacket(p);
	cout << p->packet_output->printStreamInHexadecimal()    << endl;
	
	//close output
	out->close();
  }
  catch(PacketException* e) {
    cout << e->geterror() << endl;
  }	
}
