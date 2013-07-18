/***************************************************************************
                          InputPacketStream.h  -  description
                             -------------------
    begin                : Sun Oct 27 2002
    copyright            : (C) 2002 by Andrea Bulgarelli
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

#ifndef INPUTPACKETSTREAM_H
#define INPUTPACKETSTREAM_H

#include "PacketStream.h"
#include "Input.h"
#include "PacketExceptionIO.h"

namespace PacketLib {

//##ModelId=3C0F6C190336
//## $Date: 2005/03/09 10:57:50 $
//## $Header: /home/repository/cvs/gtb/PacketLib/include/InputPacketStream.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//## $Id: InputPacketStream.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//## $Revision: 1.2 $
//## \brief This class represents the stream of byte in input that contains the packets. The input object must be deleted by its creator.
class InputPacketStream : public PacketStream
{
    public:

        //##ModelId=3EADC1290013
        InputPacketStream();

        //##ModelId=3EADC1290020
        InputPacketStream(const char* fileNameConfig);

        //##ModelId=3EADC1290051
        ~InputPacketStream();

        //##ModelId=3C3AB71401AE
        //##Documentation
        //## \return The index of packet type if it's recognized. 0 if packet isn't recogniezed.
        //## \param prefix A ByteStream that contains the prefix of packet (if present).
        //## \param packetHeader A ByteStream that contains the packet header.
        //## \param packetDataField A ByteStream that contains the packet data field.
        int detPacketType(ByteStream* prefix, ByteStream* packetHeader, ByteStream* packetDataField);

        //##ModelId=3EADC1290097
        //##Documentation
        //## \return The index of packet type if it's recognized. 0 if packet isn't recogniezed.
        //## \param prefix A ByteStream that contains the prefix of packet (if present).
        //## \param packet A ByteStream that contains the packet.
        int detPacketType(ByteStream* prefix, ByteStream* packet);

        //##ModelId=3EADC12900F5
        //##Documentation
        //## This method sets the generic input of the stream
        //## \param in An input.
        void setInput(Input* in);

        //##ModelId=3EADC1290130
        //##Documentation
        //## This method read a telemetry packet
        //## \pre The setInput method must be invocated
        //## \return A pointer telemetry packet. Make attention: the object returned is one of the TM packet object of the array of this object. Don't delete it!
        Packet* readPacket() throw(PacketExceptionIO*);

    protected:

 //##ModelId=3EADC128038F
        Input* in;

};

}
#endif
