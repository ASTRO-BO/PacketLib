/***************************************************************************
                          InputPacketStream.h  -  description
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
#ifndef InputPacketStreamFile_h_h
#define InputPacketStreamFile_h_h

#include "PacketLibDefinition.h"
#include "PacketHeader.h"
#include "InputPacketStream.h"
#include "ByteStream.h"
#include "ConfigurationFile.h"
#include "FileStreamPointer.h"
#include "PacketException.h"
#include "PacketNotRecognized.h"
#include "FileStream.h"

namespace PacketLib
{

//##ModelId=3EADC1220335
//##	$Date: 2005/07/12 09:10:35 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/InputPacketStreamFile.h,v 1.5 2005/07/12 09:10:35 bulgarelli Exp $
//##	$Id: InputPacketStreamFile.h,v 1.5 2005/07/12 09:10:35 bulgarelli Exp $
//##	$Revision: 1.5 $
//##	\brief This class represents the stream of byte into a file that contains the packets.
class InputPacketStreamFile : public InputPacketStream
{

public:

    //##ModelId=3EADC12901CB
    InputPacketStreamFile(const char* fileNameConfig, const char* fileNameStream, long initialPosition) ;

    //##ModelId=3EADC12901D7
    InputPacketStreamFile();

    //##ModelId=3EADC12901D8
    ~InputPacketStreamFile();

    //##ModelId=3EADC12901D9
    void setFileNameStream(char *);

    //Documentation
    //##ModelId=3EADC12901DE
    //## Opens the input stream.
    bool openInputStream() throw(PacketExceptionIO*);

    //Documentation
    //##ModelId=3EADC12901E0
    //## Closes the input stream
    void closeInputStream() throw(PacketExceptionIO*);

    //Documentation
    //##ModelId=3EADC12901E2
    //## \return true if stream is at the end of file (input)
    bool isInputStreamEOF() throw(PacketExceptionIO*);

    //##ModelId=3EADC12901E4
    Packet* getPacketFromStream() throw (PacketExceptionIO * );

    //##ModelId=3EADC12901E6
    long getNumberOfFileStreamPointer();

    //##ModelId=3EADC12901E8
    //##Documentation
    //## This method builds a list of FileStreamPointer
    bool freeRun() throw(PacketExceptionIO*);

    //##ModelId=3EADC12901EA
    //##Documentation
    //## Get a packet form the file stream pointer
    //## \pre freeRun() must be invocated.
    Packet* getPacketFromFileStreamPointer(int index, bool newpointer = false) throw(PacketExceptionIO*);

    //##ModelId=3EADC12901F0
    //##Documentation
    //## Get a file stream pointer
    //## \pre freeRun() must be invocated.
    FileStreamPointer* getFileStreamPointer(int index);

    //##ModelId=3EADC12901F8
    void setInitialPosition(long p);

    //##ModelId=3EADC1290189
    //##Documentation
    //## List of FileStreamPointer in the inputStream
    FileStreamPointer** listOfFileStreamPointer;

    //##ModelId=3EADC12901AC
    //##Documentation
    //## File that contains byte stream
    FileStream* inputStream;

private:

    //##ModelId=3EADC12901B7
    //##Documentation
    //## File name of file that contains the packet
    char* fileNameStream;

    //##ModelId=3EADC12901BD
    //##Documentation
    //## Initial position into file
    long initialPosition;

    //##ModelId=3EADC12901C4
    //##Documentation
    //## Number of packet in the listOfFileStreamPointer
    long numberOfFileStreamPointer;

};

}
#endif
