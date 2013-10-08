#include "InputPacketStreamFile.h"

using namespace PacketLib;

const char config[] = "p3901.stream";
const char file[] = "VC-01.P-033300.pkt";

int main(int argc, char** argv) {
	InputPacketStreamFile* ips = new PacketLib::InputPacketStreamFile;
	ips->setFileNameConfig((char*)config);
	ips->createStreamStructure();		
	ips->setInitialPosition(0L);
	ips->setFileNameStream((char*)file);
	ips->openInputStream();
	int count = 0;
    	int countbad = 0;
	bool eof = false; 
	eof = ips->isInputStreamEOF();
	PacketLib::Packet *p;
        p = ips->getPacketFromStream();

        while(!eof) {
                if(p != 0) {
                        count++;
                        p->deleteExternalByteStream();
                }
                else
                        countbad++;

                // testing stream EOF should not raise an exception
                eof = ips->isInputStreamEOF();

                // getting a packet from the stream should not raise an exception
                p = ips->getPacketFromStream();
        }

	return 0;
}
