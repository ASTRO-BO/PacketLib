/***************************************************************************
                          PartOfPacket.cpp  -  description
                             -------------------
    begin                : Thu Dec 6 2001
    copyright            : (C) 2001, 2013 by Andrea Bulgarelli
    email                : bulgarelli@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "PartOfPacket.h"

using namespace PacketLib;

word PacketLib::pattern[] = {0,1,3,7,15,31,63,127,255,511,1023,2047,4095,8191,16383,32767,65535};


PartOfPacket::PartOfPacket(const char* popName)
{
    fieldsDimension = 0;
    stream = ByteStreamPtr(new ByteStream());
    numberOfFields = 0;
	numberOfLogicalFields = 0;
    fields = 0;
    outputstream = 0;
	decoded = false;
    this->popName = (char*) popName;
}


PartOfPacket::~PartOfPacket()
{
    deleteFields();
}



string* PartOfPacket::printStructure()
{
    bool first = true;
    char *s = NULL;

    for(unsigned i=0; i< numberOfFields; i++)
    {
        Field* f = fields[i];
        if(first)
        {
            sprintf(s, "Prog: %d - Name - %s\n", f->getProgressiv(), f->getName() );
            first = false;
        }
        else
            sprintf(s, "%sProg: %d - Name - %s\n", s, f->getProgressiv(), f->getName() );
    }
    string* sr = new string(s);
    return sr;
}

#ifdef USEPHYSICALFIELDS

bool PartOfPacket::loadFields(InputText& fp) throw(PacketException*)
{
    char* name, *dimension, *value;
    /// It calls the function that releases the memory
    deleteFields();
    int count = 0;
    /// count the number of fields
    long pos = fp.getpos();
    do {
        name = fp.getLine();
        count++;
        if(name[0] == '[')
        {
            count--;
            break;
        }
    } while(strlen(name) !=  0);
    fp.setpos(pos);
    fields = new Field* [count/3];
	
    name = fp.getLine();
    if(strlen(name) == 0)
    {
        return false;
    }
	
    while(strlen(name) != 0)
    {
		
        dimension = fp.getLine();
        value = fp.getLine();
        Field* f = new Field(name, atoi(dimension), value, numberOfFields);
		//cout << name << " " << dimension << " " << value << endl;
        fieldsDimension += f->size();
        fields[numberOfFields] = f;
        numberOfFields++;
        name = fp.getLine();
        /// It reads until the buffer ends
        if(name[0] == '[')
        {
            break;
        }
    }
    return true;
}

#endif

#ifdef USELOGICALFIELDS

bool PartOfPacket::loadFields(InputText& fp) throw(PacketException*)
{

    char* name, *type, *value;
    /// It calls the function that releases the memory
    deleteFields();
    int count = 0;
	int countlogicalfields = 0;
    /// count the number of fields
    long pos = fp.getpos();
	
    do {
        name = fp.getLine();
		if(strlen(name) == 0 || name[0] == '[')
        {
            count--;
			countlogicalfields--;
            break;
        }
		countlogicalfields++;
		type = fp.getLine();
		if(strlen(name) == 0 || type[0] == '[')
        {
            break;
        }
		/// Logical type
		enum LogicalFieldDataType outtype;
		///the number of physical fields equivalent to this logical field
		int outtypenfields;
		///the number of bits of each single field
		int outputfieldsbitsize;
		LogicalField::getType(type, outtype, outtypenfields, outputfieldsbitsize);
		count += outtypenfields;
		//TODO HERE
		if(outtype == UNKNOWN)
			throw new PacketException("PartOfPacket::loadFields(): wrong type for a field specified in the configuration file");
		
		value = fp.getLine();
		if(strlen(name) == 0 || value[0] == '[')
        {
            break;
        }
		
        
    } while(strlen(name) !=  0);

    fields = new Field* [count+1];
	logicalFields = new LogicalField* [countlogicalfields+1];

	fp.setpos(pos);
    name = fp.getLine();
    if(strlen(name) == 0)
    {
        return false;
    }

	numberOfFields = 0;
	numberOfLogicalFields = 0;
    while(strlen(name) != 0)
    {

        type = fp.getLine();
        value = fp.getLine();
		
		cout << "numberOfLogicalFields " << numberOfLogicalFields << endl;
		LogicalField* lf = new LogicalField(name, type, value, numberOfLogicalFields );
		
		//cout << name << " " << type << " " << value << " " << lf->getType() << " " << lf->getOutTypeNfields() << " " << numberOfLogicalFields << endl;
		logicalFields[numberOfLogicalFields] = lf;
		numberOfLogicalFields++;
		
		if(lf->getOutTypeNfields() > 1) {
			if(lf->getOutTypeNfields() > 4)
				throw new PacketException("It is not possible to have more than 4 physical fields for a logical field");
			for(int i=0; i<lf->getOutTypeNfields(); i++) {
				cout << "A!!!!!!!!! " << i << endl;
				//it should be useful to change the name of the field TODO
				//the predefined value is only valid for types <= 16 bit - it should be possible to call the appropriate set methods here TODO
				cout << "numberOfFields " << numberOfFields << endl;
				
				Field* f = new Field(name, lf->getOutputFieldsBitSize(), "none", numberOfFields);
				fieldsDimension += f->size();
				fields[numberOfFields] = f;
				cout << lf->getIndexOfPhysicalField() << endl;
				if(i==0) lf->setIndexOfPhysicalField(numberOfFields);
				cout << lf->getIndexOfPhysicalField() << endl;
				
				numberOfFields++;
			}
		} else {
			Field* f = new Field(name, lf->getOutputFieldsBitSize(), value, numberOfFields);
			fieldsDimension += f->size();
			fields[numberOfFields] = f;
			lf->setIndexOfPhysicalField(numberOfFields);
			numberOfFields++;
		}
		
        name = fp.getLine();
        /// It reads until the buffer ends
        if(name[0] == '[')
        {
            break;
        }
    }
	cout << "numberOfLogicalFields-numberOfLogicalFields" <<  numberOfLogicalFields << endl;
	printLogicalFields();
    return true;
}

#endif

#ifdef USEPHYSICALFIELDS

bool PartOfPacket::loadFields(MemoryBuffer* buffer) throw(PacketException*)
{
	return false;
    char* name;
    char* dimension;
    char* value;
    int count = 0;

    /// It calls the function to release the memory
    deleteFields();
    count = buffer->getBufferDimension();
    /// It allocates the field memory
    fields = new Field* [count/3];

    /// Begin of the packet creation
    name = buffer->getbuffer();
    if(name == 0)
    {
        return false;
    }
    while(name != 0)
    {
        dimension = buffer->getbuffer();
        value = buffer->getbuffer();
        Field* f = new Field(name, atoi(dimension), value, numberOfFields);
        fieldsDimension += f->size();
        fields[numberOfFields] = f;
        numberOfFields++;
        name = buffer->getbuffer();
        /// It reads until the buffer ends
        if(name == 0)
        {
            return true;
        }
    }
    return true;
}

#endif


MemoryBuffer* PartOfPacket::loadFieldsInBuffer(InputText & fp)
{
	return 0;
    char* name, *dimension, *value;
    MemoryBuffer* buffer = 0;
    int count = 0;
    name = fp.getLine();
    if(strlen(name) == 0)
    {
        return buffer;
    }

    buffer = new MemoryBuffer();

    while(strlen(name) != 0)
    {
        buffer->setbuffer(name);
        dimension = fp.getLine();
        buffer->setbuffer(dimension);
        value = fp.getLine();
        buffer->setbuffer(value);
        count++;
        name = fp.getLine();
        /// It reads until it reaches [
        if(name[0] == '[')
        {
            //delete[] name;
            break;
        }
    }
    return buffer;
}


bool PartOfPacket::setByteStream(ByteStreamPtr s)
{
    
	decoded = false;
    /// If NULL is passed it exits
    if(s == NULL) return true;

    if(size() > s->size())
        return false;


    if(!s->getMemAllocation())
        stream->setStream(s->stream, s->size(), s->isBigendian());

    /// The stream is assigned
    this->stream = s;
	
	//decode();
	return true;
}

bool PartOfPacket::decode() {
	if(decoded)
		return true;
	Field* ftemp;
    //this->stream->setStream(s, 0, s->size() - 1);
    /// The pointer is converted from byte to void. The reading from file allows the correct data interpretation
    /// for big or little endian machines
    byte* stream = (byte*) this->stream->stream;
	if(stream == NULL)
		return false;
    /// It indicates the position inside the word:
    byte posbit = 0;
    /// It indicates the word to be analyzed inside the stream
    word posword = 0;
    /// Dimension nof the current field
    byte dimbit = 0;

    /// number of shift for elaboration
    short numberOfShift = 0;
    /// number of fields
    //unsigned nof = getNumberOfFields();
    word nof = numberOfFields;
    for(word i=0; i<nof; i++)
    {
        ftemp =  fields[i];
        dimbit = ftemp->size();
        /// Temporary word to be modified for the elaboration
        byte bh = *(stream + posword);
        byte bl = *(stream + posword + 1);
        //word wordtemp = *(stream + posword);
        word wordtemp;
        if (this->stream->isBigendian())
            wordtemp = bh * 256 + bl;
        else
            wordtemp = bl * 256 + bh;
        numberOfShift = 16 - (posbit + dimbit);
        //parte nuova
        /// \remarks if the condition is not fulfilled, the code is equal to the versions older than PacketLib 1.3.3
        if(numberOfShift < 0)   
        {
            short currentDimBit = dimbit + numberOfShift;
            dimbit = abs(numberOfShift);
            ftemp->value = (wordtemp & pattern[currentDimBit] ) << dimbit;
            posbit = 0;
            posword += 2;
            bh = *(stream + posword);
            bl = *(stream + posword + 1);
            if (this->stream->isBigendian())
                wordtemp = bh * 256 + bl;
            else
                wordtemp = bl * 256 + bh;

            numberOfShift = 16 - (posbit + dimbit);
            wordtemp = wordtemp >> numberOfShift;
            /*		cout << i << ": " << ftemp->value << endl;
            		cout << i << ": " << (ftemp->value << currentDimBit) << endl;
            		cout << i << ": " << wordtemp << endl;*/
            ftemp->value = ftemp->value | (wordtemp & pattern[dimbit]);
            /*		cout << i << ": " << ftemp->value << endl;
            		cout << i << ": " << (wordtemp & pattern[dimbit]) << endl;*/
        }
        else
        {
            //questa fa parte della parte vecchia
            wordtemp = wordtemp >> numberOfShift;
            ftemp->value = wordtemp & pattern[dimbit];
        }
        /// Upgrade of pobit and posword
        posbit += dimbit;
        if(posbit >=16)
        {
            posword+=2;
            posbit =0;
        }
    }
	decoded = true;
    return true;
}



char** PartOfPacket::printValue(const char* addString)
{
	decode();
    //bool first = true;
    string s1, s2, s3;
    char *s = new char[1];       //importante, altrimenti non funziona
    char *t;
    char **c;
    long index;
    //c = (char**) malloc(sizeof(char*) * (numberOfFields + 1));
    c = new char* [numberOfFields + 1];
    s3 = "";
    if(!stream) return NULL;
    // Create constant iterator for list.

    //list<Field>::iterator iter;
    /// Iterate through list and output each element.
    index = 0;
    //for (iter=fields.begin(); iter != fields.end(); iter++)
    for(unsigned i=0; i<numberOfFields; i++)
    {
        //Field* f = (Field*) &(*iter);
        Field* f = fields[i];
        //sprintf(s, "Name: %s Value: %d\n", f->name.c_str(), f->value);
        //cout << "@ " << f->value << endl;
        sprintf(s, "%d", f->value);
        //s1 = "Name: ";
        s1 = "";
        s2 = f->getName();
        s2 += " (";
        s2 += Utility::integerToString(f->size());
        s2 +=  ") - ";
        s2 += "Value: ";
        s2 += s;
        s2 += " (0x";
        s2 += Utility::stringToHexadecimal((byte*) &f->value, 2, false, false);
        s2 += ")";
        //		s2 += //+ "@";
        s3 = s1 + s2 + addString;
        //		s3 += '\n';
        c[index] = new char[s3.size() + 1];
        t = (char*) s3.c_str();
        for(unsigned j=0; j<= s3.size(); j++)
            c[index][j] = t[j];
        //c[index][i] = '\0';
        //printf("%p\n", c[index]);
        //cout << c[index] << endl;
        index ++;
    }
    c[index] = 0;
    return c;
}

void PartOfPacket::printValueStdout()
{
	decode();
    //bool first = true;
    string s1, s2, s3;
    char *s = new char[1];       //importante, altrimenti non funziona
    if(!stream) return;
    for(unsigned i=0; i<numberOfFields; i++)
    {
        //Field* f = (Field*) &(*iter);
        Field* f = fields[i];
        //sprintf(s, "Name: %s Value: %d\n", f->name.c_str(), f->value);
        sprintf(s, "%d", f->value);
        //s1 = "Name: ";
        s1 = "";
        s2 = f->getName();
        s2 += " (";
        s2 += Utility::integerToString(f->size());
        s2 +=  ") - ";
        s2 += "Value: ";
        s2 += s;
        s2 += " (0x";
        s2 += Utility::stringToHexadecimal((byte*) &f->value, 2, false, false);
        s2 += ")";
        s3 = s1 + s2;
        cout << s3 << endl;
    }
    /* if(stream)
         	cout << stream->printStreamInHexadecimal() << endl;
     if(outputstream)
         	cout << stream->printStreamInHexadecimal() << endl;*/
}

void PartOfPacket::printLogicalFields()
{
	cout << "numberOfLogicalFields: " << numberOfLogicalFields << endl;
	for(int i=0; i<numberOfLogicalFields; i++) {
		LogicalField* lf = logicalFields[i];
		cout << lf->getProgressiv() << " " << lf->getIndexOfPhysicalField() << " " << lf->getName() << endl;
	}
}


void PartOfPacket::deleteFields()
{
    for(unsigned i = 0; i < numberOfFields; i++)
        delete fields[i];
    delete[] fields;
}


ByteStreamPtr PartOfPacket::generateStream(bool bigendian)
{
    word w = 0, wtemp = 0;
    int posbit = 0;
    word posword = 0;
    short shift;
    /// Dimension of the current field
    byte dimbit = 0;
    if(outputstream == 0)
        outputstream = ByteStreamPtr(new ByteStream(size(), bigendian));
    for(unsigned i = 0; i<numberOfFields; i++)
    {
        if(!fields[i]->thereIsPredefinedValue())
            wtemp = fields[i]->value;
        else
            wtemp = fields[i]->value =  fields[i]->getPredefinedValue();
        dimbit = fields[i]->size();
        shift = 16 - dimbit - posbit;
        if(shift < 0)
        {
            byte nbitshigh = abs(shift);
            //word wh = wtemp >> (16 - nbitshigh);
            word wh = wtemp >> (nbitshigh);
            w = w | wh;
            if(outputstream->setWord(posword, w))
                posword+=2;
            else
                return 0;
            w = 0;
            posbit = nbitshigh;
            w = (wtemp & pattern[nbitshigh]) << (16-posbit);

        }
        else
        {
            wtemp = (wtemp << shift);
            w = w | wtemp;
            //cout << (Utility::wordToBinary(w, 16))->c_str() << endl;
            posbit += fields[i]->size();
        }
        if(posbit == 16)
        {
            posbit = 0;
            if(outputstream->setWord(posword, w))
                posword+=2;
            else
                return 0;
            w = 0;

        }
        else
        {
            if(posbit > 16)
                return 0;
        }
    }
    if(posbit < 16)
        outputstream->setWord(posword, w);
    return outputstream;
};


bool PartOfPacket::setOutputStream(ByteStreamPtr os, dword first)
{
    outputstream = ByteStreamPtr(new ByteStream((os->stream + first), size(), os->isBigendian()));
    return true;
}

word PartOfPacket::getFieldValuePhysical(word index)
{
	cout << "PartOfPacket::getFieldValuePhysical " << endl;
	decode();
	cout << "getFieldValuePhysical index: " << index << " numberOfFields: " << numberOfFields << " " << endl;
	if(index < numberOfFields) {
		cout << "value: " << fields[index]->value << endl;
		return fields[index]->value;
	}
	else
		return 0;
};

word PartOfPacket::getFieldValue(word index)
{
#ifdef USELOGICALFIELDS
	if(index < numberOfLogicalFields)
		index = logicalFields[index]->getIndexOfPhysicalField();
#endif
	  
	return getFieldValuePhysical(index);

}

void PartOfPacket::setFieldValue(word index, word value)
{
	
#ifdef USELOGICALFIELDS
	if(index < numberOfLogicalFields)
		index = logicalFields[index]->getIndexOfPhysicalField();
#endif
	
	setFieldValuePhysical(index, value);
	
    /*
	if(index < numberOfFields)
		fields[index]->value = (value & pattern[fields[index]->size()]);
	*/
}

void PartOfPacket::setFieldValuePhysical(word index, word value)
{
    if(index < numberOfFields)
		fields[index]->value = (value & pattern[fields[index]->size()]);
}

float PartOfPacket::getFieldValue_32f(word index)
{
	
#ifdef USELOGICALFIELDS
	if(index < numberOfLogicalFields)
		index = logicalFields[index]->getIndexOfPhysicalField();
#endif
	
    union u_tag
    {
    	/// 32 bit
        dword i;
        /// 32 bit single precision
        float f;	
    } u;
    u.i =  ( (dword) getFieldValuePhysical(index) << 16) | ( (dword) getFieldValuePhysical(index + 1) );
    return u.f;
}

double PartOfPacket::getFieldValue_64f(word index)
{

#ifdef USELOGICALFIELDS
	if(index < numberOfLogicalFields)
	index = logicalFields[index]->getIndexOfPhysicalField();
#endif
	
	if(sizeof(unsigned long) == 4) {
		//TODO
		throw new PacketException("PartOfPacket::getFieldValue_64f() does not work in a 32 bit system");
	}
		
    union u_tag
    {
    	/// 64 bit for 64 bit os)
        unsigned long i;
        /// 64 bit double precision
        double d;	
    } u;
    u.i = (unsigned long) ( (unsigned long)  getFieldValuePhysical(index) << (48)) | ( (unsigned long) getFieldValuePhysical(index + 1) << (32)) | ( (unsigned long) getFieldValuePhysical(index + 2) << (16)) | ( (unsigned long) getFieldValuePhysical(index + 3) );
    return u.d;
}

void PartOfPacket::setFieldValue_32f(word index, float value)
{

#ifdef USELOGICALFIELDS
	if(index < numberOfLogicalFields)
		index = logicalFields[index]->getIndexOfPhysicalField();
#endif

    union u_tag
    {
    	/// 32 bit
        unsigned long i;
        /// 32 bit single precision
        float f;	
    } u;
    word w;
    u.f = value;
    w = (word)(u.i >> 16);
    setFieldValue(index, w);
    w = (word)(0xFFFF & u.i);
    setFieldValuePhysical(index + 1, w);
}

void PartOfPacket::setFieldValue_64f(word index, double value)
{
	
#ifdef USELOGICALFIELDS
	if(index < numberOfLogicalFields)
		index = logicalFields[index]->getIndexOfPhysicalField();
#endif

    if(sizeof(unsigned long) == 4) {
		//TODO
		throw new PacketException("PartOfPacket::setFieldValue_64f() does not work in a 32 bit system");
	}
		
    union u_tag
    {
    	/// 64 bit for 64 bit os)
        unsigned long i;
        /// 64 bit double precision
        double d;	
    } u;
    
    word w;
    u.d = value;
    w = (word)( (u.i >> 48) );
    setFieldValuePhysical(index, w);
    w = (word)( 0xFFFF &  (u.i >> 32) );
    setFieldValuePhysical(index + 1, w);
    w = (word)( 0xFFFF &  (u.i >> 16) );
    setFieldValuePhysical(index + 2, w);
    w = (word)(0xFFFF & u.i);
    setFieldValuePhysical(index + 3, w);
}

signed long PartOfPacket::getFieldValue_32i(word index)
{
#ifdef USELOGICALFIELDS
	if(index < numberOfLogicalFields)
		index = logicalFields[index]->getIndexOfPhysicalField();
#endif
	
    long l;
    l = (long)(getFieldValuePhysical(index) << 16) | (long)getFieldValuePhysical(index + 1);
    return l;
}

signed short PartOfPacket::getFieldValue_16i(word index)
{
#ifdef USELOGICALFIELDS
	if(index < numberOfLogicalFields)
	index = logicalFields[index]->getIndexOfPhysicalField();
#endif
	
    signed short l;
    l = (signed short)getFieldValuePhysical(index);
    return l;
}

word PartOfPacket::getFieldValue_16ui(word index)
{
	return getFieldValue(index);
}


void PartOfPacket::setFieldValue_32i(word index, signed long value)
{
#ifdef USELOGICALFIELDS
	if(index < numberOfLogicalFields)
		index = logicalFields[index]->getIndexOfPhysicalField();
#endif
	
    word w;
    w = (word)(value >> 16);
    setFieldValuePhysical(index, w);
    w = (word) (0xFFFF & value);
    setFieldValuePhysical(index + 1, w);
}

void PartOfPacket::setFieldValue_16i(word index, signed short value)
{
#ifdef USELOGICALFIELDS
	if(index < numberOfLogicalFields)
	index = logicalFields[index]->getIndexOfPhysicalField();
#endif
	
    word w;
    w = (word)value;
    setFieldValuePhysical(index, w);
}

void PartOfPacket::setFieldValue_16ui(word index, word value)
{
    setFieldValue(index, value);
}

unsigned long PartOfPacket::getFieldValue_32ui(word index)
{
	printLogicalFields();
	exit(0);
	cout << "PartOfPacket::getFieldValue_32ui logical " << index << endl;
#ifdef USELOGICALFIELDS
	if(index < numberOfLogicalFields)
		index = logicalFields[index]->getIndexOfPhysicalField();
	cout << "PartOfPacket::getFieldValue_32ui physica " << index << endl;
#endif
	//TODO con getFieldValue funziona, con getFieldValuePhysical() non funziona
	
	cout << "---" << endl;
	cout << "A getFieldValue" << endl;
	//cout << "getFieldValue_32ui res: " << (unsigned long ) getFieldValue(index)  << endl;
	//cout << (unsigned long ) getFieldValue(index + 1) << endl;
	
	cout << "B getFieldValuePhysical " << endl;
	
	unsigned long tmp = getFieldValuePhysical(index);
	cout << "---" << tmp << endl;
	
	
	
	cout << "----" << endl;
    dword l;
	cout << getFieldValuePhysical(index) << endl;
	l = getFieldValuePhysical(index);
	cout << l << endl;
	l = l << 16;
	cout << l << endl;
	cout << getFieldValuePhysical(index + 1) << endl;
	l = l | getFieldValuePhysical(index + 1);
	cout << l << endl;
	cout << "----" << endl;
    l = (dword) (getFieldValuePhysical(index) << 16) | (dword) getFieldValuePhysical(index + 1);
    return l;
}

void PartOfPacket::setFieldValue_32ui(word index, unsigned long value)
{
#ifdef USELOGICALFIELDS
	if(index < numberOfLogicalFields)
	index = logicalFields[index]->getIndexOfPhysicalField();
#endif
	
    word w;
    w = (word)(value >> 16);
    setFieldValuePhysical(index, w);
    w = (word) (0xFFFF & value);
    setFieldValuePhysical(index + 1, w);
}

#ifdef USEPHYSICALFIELDS

unsigned long PartOfPacket::getFieldValue_24ui(word index)
{
#ifdef USELOGICALFIELDS
	if(index < numberOfLogicalFields)
		index = logicalFields[index]->getIndexOfPhysicalField();
#endif
	
    word wh, wl;
    wh = getFieldValuePhysical(index);
    wl = getFieldValuePhysical(index + 1);
    return (dword)(wh << 8) | (dword)(wl & 0xFF);
}

void PartOfPacket::setFieldValue_24ui(word index, unsigned long value) throw(PacketException*)
{
#ifdef USELOGICALFIELDS
	if(index < numberOfLogicalFields)
		index = logicalFields[index]->getIndexOfPhysicalField();
#endif
	
    word w;
    if(value > U24BITINTGEGERUNSIGNED_MAX)
        throw new PacketException("setFieldValue_24ui(): the max value of 24 bit unsigned integer should be 16777215");
    w = (word)(value >> 8);
    setFieldValuePhysical(index, w);
    w = (word) (0xFF & value);
    setFieldValuePhysical(index + 1, w);
}


signed long PartOfPacket::getFieldValue_24i(word index)
{
	
    union u_tag
    {
    	/// 32 bit
        unsigned long u;		
        signed long s;
    } us;
    us.u = getFieldValue_32ui(index);
    /// get the sign
    unsigned long sign = (us.u  >> 23); 
    unsigned long wh = us.u & 0x007FFFFF;
    /// get a long 32 bit
    if(sign == 1)
        us.u = 0x7F800000 + wh + (sign << 31);
    else
        us.u = wh + (sign << 31);
    return us.s;
}

void PartOfPacket::setFieldValue_24i(word index, signed long value) throw(PacketException*)
{
    union u_tag
    {
    	/// 32 bit
        unsigned long u;		
        signed long s;
    } us;
    if(value > U24BITINTGEGERSIGNED_MAX)
        throw new PacketException("setFieldValue_24i(): the max value of 24 bit signed integer should be 8388607");
    if(value < U24BITINTGEGERSIGNED_MIN)
        throw new PacketException("setFieldValue_24i(): the min value of 24 bit signed integer should be -8388607");
    us.s = value;
    unsigned long sign = (us.u >> 31);
    /// 23 bit
    unsigned long wh = us.u & 0x007FFFFF;
    unsigned long value2 = 0;
    value2 = wh + (sign << 23);
    setFieldValue_32ui(index, value2);
}

#endif

void PacketLib::PartOfPacket::memByteStream(ByteStreamPtr stream) {
	this->stream = stream;
}
