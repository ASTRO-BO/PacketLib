/***************************************************************************
                          OutputPacketStream.h  -  description
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001 by Andrea Bulgarelli
    email                : bulgarelli@bo.iasf.cnr.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *             
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/
#ifndef OutputPacketStream_h_h
#define OutputPacketStream_h_h

#include "PacketLibDefinition.h"
#include "PacketStream.h"
#include "Output.h"

namespace PacketLib {

//##ModelId=3C0F6C190344
//##Documentation
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/OutputPacketStream.h,v 1.3 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: OutputPacketStream.h,v 1.3 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.3 $
//##	\brief This class represents generic output of strean if packet.
class OutputPacketStream : public PacketStream
{
    public:

        //##ModelId=3EADC12A0289
        OutputPacketStream();

        //##ModelId=3EADC12A0290
        OutputPacketStream(const char* fileNameConfig);

        //##ModelId=3EADC12A02A9
        //## Generate the output ByteStream and send it to the output.
        bool writePacket(Packet* p) throw(PacketExceptionIO*);

        //##ModelId=3EADC12A02C8
        void setOutput(Output* out);

    protected:

	//##ModelId=3EADC12A027A
        Output* out;
};

}
#endif
