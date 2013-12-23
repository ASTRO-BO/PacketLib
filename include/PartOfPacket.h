/***************************************************************************
                          PartOfPacket.h  -  description
                             -------------------
    begin                : Thu Dec 6 2001
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

#ifndef _PARTOFPACKET_H
#define _PARTOFPACKET_H

#include "InputText.h"
#include "Field.h"
#include "PacketLibDefinition.h"
#include "Utility.h"
#include "ByteStream.h"
#include "PacketException.h"
#include "MemoryBuffer.h"

namespace PacketLib
{

extern word pattern[17];

/// This class represent a subset of the packet. This class has been created for grouping
/// the common behaviours of PacketHeader, DataFieldHeader and SourceDataField
/// \brief Single part of packet.
class PartOfPacket
{
public:

    /// Constructor
    PartOfPacket(const char* popName = 0);

    /// Virtual destructor
    virtual ~PartOfPacket();

    /// Prints the structure of this part of packet.
    virtual string* printStructure();

    /// Prints the value of each field of this part of packet.
    virtual char** printValue(const char* addString = "");

    virtual void printValueStdout();

    /// This method loads the field present into the InputText (passed with the
    /// parameter).
    /// The InputText must be open and the internal pointer of the file must
    /// be in the first line that describes the fields.
    virtual bool loadFields(InputText& fp) throw(PacketException*);

    /// This method loads the field present into the MemoryBuffer (passed with the
    /// parameter).
    virtual bool loadFields(MemoryBuffer* mb) throw(PacketException*);

    virtual MemoryBuffer* loadFieldsInBuffer(InputText & fp);

    /// Returns the dimension (in byte) of this part of packet.
    virtual  inline dword getDimension()
    {
        return fieldsDimension / 8;
    };

    /// Returns a pointer of a field in the list of fields of this part of packet.
    /// \param index Represent the index in the list.
    virtual  inline  Field* getFields(word index)
    {
        if(index < numberOfFields)
            return fields[index];
        else
            return 0;
    };

    /// Returns the value of a field in the list of fields of this part of packet.
    /// \param index Represent the index in the list.
    virtual  inline word getFieldValue(word index)
    {
        if(index < numberOfFields)
            return fields[index]->value;
        else
            return 0;
    };

    /// Returns the value of a field in the list of fields of this part of packet.
    /// The value returned is interpreted as a real single precision (IEEE 754).
    /// The index of the argument is the first 16 bit field of the 2 fields that compound
    /// the 32 bit real single precision. The layout foreseen is the following:
    /// ---------------------------------
    /// -	float last 16 bits	-	the index passed as argument
    /// ---------------------------------
    /// -	float first 16 bits	-	the index + 1
    /// ---------------------------------
    /// This corresponds with the PTC=5, PFC = 1.
    /// \param index Represent the index of the field.
    virtual float getFieldValue_5_1(word index);
    
    /// Returns the value of a field in the list of fields of this part of packet.
    /// The value returned is interpreted as a real double precision (IEEE 754).
    /// The index of the argument is the first 16 bit field of the 4 fields that compound
    /// the 64 bit real double precision. The layout foreseen is the following:
    /// ---------------------------------
    /// -	float last 16 bits	-	the index passed as argument
    /// ---------------------------------
    /// -	float third 16 bits	-	the index + 1
    /// ---------------------------------
    /// -	float second 16 bits	-	the index + 1
    /// ---------------------------------
    /// -	float first 16 bits	-	the index + 1
    /// ---------------------------------
    /// This corresponds with the PTC=5, PFC = 2.
    /// \param index Represent the index of the field.
    virtual double getFieldValue_5_2(word index);

    /// Set the value of a field. The value is interpreted as a real single
    /// precision (IEEE 754).
    /// The index of the argument is the first 16 bit field of the 2 fields that compound
    /// the 32 bit real single precision. The layout foreseen is the following:
    ///	---------------------------------
    ///	-	float last 16 bits	-	the index passed as argument
    ///	---------------------------------
    ///	-	float first 16 bits	-	the index + 1
    ///	---------------------------------
    /// This corresponds with the PTC=5, PFC = 1.
    /// See setFieldValue(word index, word value) for general considerations.
    /// \param index Represent the index of the field.
    /// \param value The real single precision value
    virtual void setFieldValue_5_1(word index, float value);
    
    /// Set the value of a field. The value is interpreted as a real double
    /// precision (IEEE 754).
    /// The index of the argument is the first 16 bit field of the 4 fields that compound
    /// the 64 bit real double precision. The layout foreseen is the following:
 	/// ---------------------------------
    /// -	float last 16 bits	-	the index passed as argument
    /// ---------------------------------
    /// -	float third 16 bits	-	the index + 1
    /// ---------------------------------
    /// -	float second 16 bits	-	the index + 1
    /// ---------------------------------
    /// -	float first 16 bits	-	the index + 1
    /// ---------------------------------
    /// This corresponds with the PTC=5, PFC = 2.
    /// See setFieldValue(word index, word value) for general considerations.
    /// \param index Represent the index of the field.
    /// \param value The real double precision value
    virtual void setFieldValue_5_2(word index, double value);

    /// Returns the value of a field in the list of fields of this part of packet.
    /// The value returned is interpreted as a 32 bit signed integer.
    /// The index of the argument is the first 16 bit field of the 2 fields that compound
    /// the 32 bit signed integer. The layout foreseen is the following:
    ///	---------------------------------
    ///	-	32 bit int MSB 16 bits	- the index passed as argument
    ///	---------------------------------
    ///	-	32 bit int LSB 16 bits	- the index + 1
    ///	---------------------------------
    /// This corresponds with the PTC=4, PFC = 14.
    /// \param index Represent the index of the field.
    virtual signed long getFieldValue_4_14(word index);

    /// Sets the value of a field. The value is interpreted as a 32 bit signed integer.
    /// The index of the argument is the first 16 bit field of the 2 fields that compound
    /// the 32 bit signed integer. The layout foreseen is the following:
    ///	---------------------------------
    ///	-	32 bit int MSB 16 bits	- 	the index passed as argument
    ///	---------------------------------
    ///	-	32 bit int LSB 16 bits	- 	the index + 1
    ///	---------------------------------
    /// This corresponds with the PTC=4, PFC = 14.
    /// See setFieldValue(word index, word value) for general considerations.
    /// \param index Represent the index of the field.
    /// \param value The 32 bit signed integer value.
    virtual void setFieldValue_4_14(word index, signed long value);

    /// Returns the value of a field in the list of fields of this part of packet.
    /// The value returned is interpreted as a 24 bit signed integer.
    /// The index of the argument is the first 16 bit field of the 2 fields that compound
    /// the 24 bit signed integer. The layout foreseen is the following:
    ///	---------------------------------
    ///	-	24 bit int MSB 16 bits	-	the index passed as argument
    ///	---------------------------------
    ///	-	24 bit int LSB 8 bits	-	the index + 1
    ///	---------------------------------
    /// This corresponds with the PTC=4, PFC = 13.
    /// \param index Represent the index of the field.
    /// \return the 24 bit signed data converted in a long 32 bit
    virtual signed long getFieldValue_4_13(word index);

    /// Sets the value of a field. The value is interpreted as a 24 bit signed integer.
    /// The index of the argument is the first 16 bit field of the 2 fields that compound
    /// the 24 bit signed integer. The layout foreseen is the following:
    ///	---------------------------------
    ///	-	24 bit int MSB 16 bits	-	the index passed as argument
    ///	---------------------------------
    ///	-	24 bit int LSB 8 bits	-	the index + 1
    ///	---------------------------------
    /// This corresponds with the PTC=4, PFC = 13.
    /// See setFieldValue(word index, word value) for general considerations.
    /// \param index Represent the index of the field.
    /// \param value The 24 bit signed integer value. The long value is converted in a
    /// 24 bit data format (bit0 with the sign became 24 bit)
    virtual void setFieldValue_4_13(word index, signed long value) throw(PacketException*);

    /// Returns the value of a field in the list of fields of this part of packet.
    /// The value returned is interpreted as a 32 bit unsigned integer.
    /// The index of the argument is the first 16 bit field of the 2 fields that compound
    /// the 32 bit unsigned long. The layout foreseen is the following:
    ///	---------------------------------
    ///	-	32 bit int MSB 16 bits	- the index passed as argument
    ///	---------------------------------
    ///	-	32 bit int LSB 16 bits	- the index + 1
    ///	---------------------------------
    /// This corresponds with the PTC=3, PFC = 14.
    /// \param index Represent the index of the field.
    virtual unsigned long getFieldValue_3_14(word index);

    /// Sets the value of a field. The value is interpreted as a 32 bit unsigned integer.
    /// The index of the argument is the first 16 bit field of the 2 fields that compound
    /// the 32 bit unsigned long. The layout foreseen is the following:
    ///	---------------------------------
    ///	-	32 bit int MSB 16 bits	- 	the index passed as argument
    ///	---------------------------------
    ///	-	32 bit int LSB 16 bits	- 	the index + 1
    ///	---------------------------------
    /// This corresponds with the PTC=3, PFC = 14.
    /// See setFieldValue(word index, word value) for general considerations.
    /// \param index Represent the index of the field.
    /// \param value The 32 bit unsigned integer value.
    virtual void setFieldValue_3_14(word index, unsigned long value);

    /// Returns the value of a field in the list of fields of this part of packet.
    /// The value returned is interpreted as a 24 bit unsigned integer.
    /// The index of the argument is the first 16 bit field of the 2 fields that compound
    /// the 24 bit unsigned long. The layout foreseen is the following:
    ///	---------------------------------
    ///	-	24 bit int MSB 16 bits	- the index passed as argument
    ///	---------------------------------
    ///	-	24 bit int LSB 8 bits	- the index + 1
    ///	---------------------------------
    /// This corresponds with the PTC=3, PFC = 13.
    /// \param index Represent the index of the field.
    virtual unsigned long getFieldValue_3_13(word index);

    /// Sets the value of a field. The value is interpreted as a 24 bit unsigned integer.
    /// The index of the argument is the first 16 bit field of the 2 fields that compound
    /// the 24 bit unsigned long. The layout foreseen is the following:
    ///	---------------------------------
    ///	-	24 bit int MSB 16 bits	- 	the index passed as argument
    ///	---------------------------------
    ///	-	24 bit int LSB 8 bits	- 	the index + 1
    ///	---------------------------------
    /// This corresponds with the PTC=3, PFC = 13.
    /// See setFieldValue(word index, word value) for general considerations.
    /// \param index Represent the index of the field.
    /// \param value The 24 bit unsigned integer value.
    virtual void setFieldValue_3_13(word index, unsigned long value) throw(PacketException*);

    ///Documentation
    /// Sets the value of a field in the list of fields of this part of packet. Remember that
    /// if a predefined value is specified in the .stream, this method has not effect and the
    /// value contained in the .stream is used.
    /// \param index Represent the index in the list.
    /// \param value The value must be set.
    virtual void setFieldValue(word index, word value);

    /// Returns the number of fields.
    virtual  inline word getNumberOfFields()
    {
        return numberOfFields;
    };

    /// Sets the stream of byte. This method assigns the value of stream for each field of part of packet
    virtual bool setByteStream(ByteStreamPtr s);

    /// Get the current ByteStream
    virtual ByteStreamPtr getByteStream()
    {
    	return stream;
    }

    virtual void memByteStream(ByteStreamPtr stream);

    /// Represent current stream writes to output.
    ByteStreamPtr outputstream;

    /// Generates the stream.
    virtual ByteStreamPtr generateStream(bool bigendian);

    /// Creates the outputstream ByteStream for the generation of the output stream
    virtual bool setOutputStream(ByteStreamPtr os, dword first);

    /// In a recoursive structure, the PartOfPacket that contains this PartOfPacket
    PartOfPacket* previous;

    char* popName;

protected:

    /// Represent current stream reads from input.
    ByteStreamPtr stream;

    /// List of field of part of packet.
    Field** fields;

    /// Dimension in bit of fields.
    word fieldsDimension;

    /// Number of fields.
    word numberOfFields;

private:

    void deleteFields();
};


}
#endif
