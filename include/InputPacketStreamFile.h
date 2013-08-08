/***************************************************************************
                          InputPacketStreamFile.h  -  description
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001, 2013 by Andrea Bulgarelli
    email                : bulgarelli@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/
 
#ifndef _INPUTPACKETSTREAMFILE_H_H
#define _INPUTPACKETSTREAMFILE_H_H

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

///	\brief This class represents the stream of byte into a file that contains the packets.
class InputPacketStreamFile : public InputPacketStream
{

public:

    InputPacketStreamFile(const char* fileNameConfig, const char* fileNameStream, long initialPosition) ;

    InputPacketStreamFile();

    ~InputPacketStreamFile();

    void setFileNameStream(char *);

    /// Opens the input stream.
    bool openInputStream() throw(PacketExceptionIO*);

    /// Closes the input stream
    void closeInputStream() throw(PacketExceptionIO*);

    /// \return true if stream is at the end of file (input)
    bool isInputStreamEOF() throw(PacketExceptionIO*);

    Packet* getPacketFromStream() throw (PacketExceptionIO * );

    long getNumberOfFileStreamPointer();

    /// This method builds a list of FileStreamPointer
    bool freeRun() throw(PacketExceptionIO*);

    /// Get a packet form the file stream pointer
    /// \pre freeRun() must be invocated.
    Packet* getPacketFromFileStreamPointer(int index, bool newpointer = false) throw(PacketExceptionIO*);

    /// Get a file stream pointer
    /// \pre freeRun() must be invocated.
    FileStreamPointer* getFileStreamPointer(int index);

    void setInitialPosition(long p);

    /// List of FileStreamPointer in the inputStream
    FileStreamPointer** listOfFileStreamPointer;

    /// File that contains byte stream
    FileStream* inputStream;

private:

    /// File name of file that contains the packet
    char* fileNameStream;

    /// Initial position into file
    long initialPosition;

    /// Number of packet in the listOfFileStreamPointer
    long numberOfFileStreamPointer;

};

}
#endif
