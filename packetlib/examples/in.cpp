/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Sat Oct 26 15:30:53 CEST 2004
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
#include "InputSocketServer.h"
#include "InputPacketStream.h"
#include "Input.h"
#include "InputFile.h"
#include "Packet.h"

using namespace PacketLib;

int main(int argc, char *argv[])
{
 try {
	Input* in;
  	
	InputPacketStream ips;
	ByteStream* bs;
	bool endcycle = false;

	//create the structure
	ips.setFileNameConfig("config_files/BURST.stream");
	ips.createStreamStructure();

	//crea l'input

	//parameter for input: socket server
	in = (Input*) new InputSocketServer(ips.isBigEndian());
	cout << "INPUT: SOCKET SERVER 20000" << endl;
	char** param = (char**) new (char*)[2];
	param[0] = "20000";	//porta
	param[1] = 0;

	//parameter for input: file
	/*in = (Input*) new InputFile(ips.isBigEndian());
	cout << "INPUT: FILE" << endl;
	char** param = (char**) new (char*)[2];
	param[0] = "../../test.raw";
	param[1] = 0;
    */

	//open input
	in->open(param);

	ips.setInput(in);

	//read a byte stream from input
	/*while(!endcycle) {
		cout << "Attendo dati..." << endl;
	  bs = in->readByteStream(10);
		if (bs != 0) {
			cout << bs->printStreamInHexadecimal() << endl;
			cout << "------------------------" << endl;
		}
		else {
			if(in->isEOF())
				endcycle = true;
		}
	} */

	Packet* p = ips.readPacket();
	cout << "INPUT: " << p->getName() << endl;
	cout << "INPUT: " << p->header->stream->printStreamInHexadecimal()    << endl;

	//close input
	in->close();
  
  }
  catch(PacketException* e) {
    cout << e->geterror() << endl;
  }	
	
}
