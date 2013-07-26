/***************************************************************************
                          PartOfPacket.cpp  -  description
                             -------------------
    begin                : Thu Dec 6 2001
    copyright            : (C) 2001 by Andrea Bulgarelli
    email                : bulgarelli@tesre.bo.cnr.it
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

//##ModelId=3C0F6C1A0223
PartOfPacket::PartOfPacket(const char* popName)
{
    fieldsDimension = 0;
    stream = new ByteStream();
    numberOfFields = 0;
    fields = 0;
    outputstream = 0;
    this->popName = (char*) popName;
}


//##ModelId=3C35860301F9
PartOfPacket::~PartOfPacket()
{
    deleteFields();
    //delete stream;
    //Don't deletes the extern ByteStream. The responsibility of this isn't of Packet class;
    //But deletes the internal ByteStream
//     if(stream !=0) AB27Aug2005
//         if(!stream->getMemAllocation()) {
//             delete stream; stream = 0;
// 	}
}


//##ModelId=3CAEAC8B0280
string* PartOfPacket::printStructure()
{
    bool first = true;
    char *s;

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

/*
// OLD VERSION
bool PartOfPacket::loadFields(InputText& fp) throw(PacketException*)
{
    bool ret;
    MemoryBuffer* buffer = loadFieldsInBuffer(fp);
    if(buffer==0)
        return false;
    ret = loadFields(buffer);
    //buffer->freebuffer(); TODO
    //delete buffer; TODO
    return ret;
}
*/

bool PartOfPacket::loadFields(InputText& fp) throw(PacketException*)
{
    char* name, *dimension, *value;
    //chiama la funzione che libera la memoria
    deleteFields();
    int count = 0;
    //count the number of fields
    long pos = fp.getpos();
    count++;
    while(strlen(name) !=  0)
    {
        name = fp.getLine();
        count++;
        if(name[0] == '[')
        {
            count--;
            break;
        }
    }
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
        Field* f = new Field(name, dimension, value, numberOfFields);
        fieldsDimension += f->getDimension();
        fields[numberOfFields] = f;
        numberOfFields++;
        name = fp.getLine();
        //legge fino a quando non finisce il buffer
        if(name[0] == '[')
        {
            break;
        }
    }
    return true;
}


//##ModelId=3DA3E5AD0046
bool PartOfPacket::loadFields(MemoryBuffer* buffer) throw(PacketException*)
{
    char* name;
    char* dimension;
    char* value;
    int count = 0;

    //chiama la funzione che libera la memoria
    deleteFields();
    count = buffer->getBufferDimension();
    //si alloca la memoria per i fields
    fields = new Field* [count/3];

    //inizio creazione packet
    name = buffer->getbuffer();
    if(name == 0)
    {
        return false;
    }
    while(name != 0)
    {
        dimension = buffer->getbuffer();
        value = buffer->getbuffer();
        Field* f = new Field(name, dimension, value, numberOfFields);
        fieldsDimension += f->getDimension();
        fields[numberOfFields] = f;
        numberOfFields++;
        name = buffer->getbuffer();
        //legge fino a quando non finisce il buffer
        if(name == 0)
        {
            return true;
        }
    }
    return true;
}



//##ModelId=3DA3E5AF0064
MemoryBuffer* PartOfPacket::loadFieldsInBuffer(InputText & fp)
{
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
        //legge fino a quando non incontra [
        if(name[0] == '[')
        {
            //delete[] name;
            break;
        }
    }
    return buffer;
}

//##ModelId=3C18AB2E037F
bool PartOfPacket::setByteStream(ByteStream* s)
{
    Field* ftemp;

    //se e' stato passato un NULL si esce
    if(s == NULL) return true;

    if(getDimension() > s->getDimension())
        return false;


    if(!s->getMemAllocation())
        stream->setStream(s->stream, s->getDimension(), s->isBigendian());

    //si assegna lo stream all'header
    this->stream = s;
    //converto il puntatore a byte in un puntatore a void. La lettura da file ha gia'
    //garantito la corretta interpretazione dei dati per macchine big o little endian
    byte* stream = (byte*) s->stream;
    //indica la posizione all'interno della word:
    byte posbit = 0;
    //indica la word da analizzare nello stream:
    word posword = 0;
    //dimensione del field corrente
    byte dimbit = 0;

    //number of shift for elaboration
    short numberOfShift = 0;
    //number of fields
    //unsigned nof = getNumberOfFields();
    word nof = numberOfFields;
    for(word i=0; i<nof; i++)
    {
        ftemp =  fields[i];
        dimbit = ftemp->getDimension();
        //word temporanea da modificare per le elaborazioni
        byte bh = *(stream + posword);
        byte bl = *(stream + posword + 1);
        //word wordtemp = *(stream + posword);
        word wordtemp;
        if (s->isBigendian())
            wordtemp = bh * 256 + bl;
        else
            wordtemp = bl * 256 + bh;
        numberOfShift = 16 - (posbit + dimbit);
        //parte nuova
        if(numberOfShift < 0)   //NB: se non si verifica mai questa condizione, il codice è assolutamente uguale al pre PacketLib 1.3.3
        {
            short currentDimBit = dimbit + numberOfShift;
            dimbit = abs(numberOfShift);
            ftemp->value = (wordtemp & pattern[currentDimBit] ) << dimbit;
            posbit = 0;
            posword += 2;
            bh = *(stream + posword);
            bl = *(stream + posword + 1);
            if (s->isBigendian())
                wordtemp = bh * 256 + bl;
            else
                wordtemp = bl * 256 + bh;

            numberOfShift = 16 - (posbit + dimbit);
            wordtemp = wordtemp >> numberOfShift;
            /*		cout << i << ": " << ftemp->value << endl;
            		cout << i << ": " << (ftemp->value << currentDimBit) << endl;
            		cout << i << ": " << wordtemp << endl;*/
            ftemp->value = (ftemp->value) | wordtemp & pattern[dimbit];
            /*		cout << i << ": " << ftemp->value << endl;
            		cout << i << ": " << (wordtemp & pattern[dimbit]) << endl;*/
        }
        else
        {
            //questa fa parte della parte vecchia
            wordtemp = wordtemp >> numberOfShift;
            ftemp->value = wordtemp & pattern[dimbit];
        }
        //aggiornamento pobit e posword
        posbit += dimbit;
        if(posbit >=16)
        {
            posword+=2;
            posbit =0;
        }
    }
    return true;
}


//##ModelId=3CAEAC8B02FD
char** PartOfPacket::printValue(const char* addString)
{
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
    // Iterate through list and output each element.
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
        s2 += Utility::integerToString(f->getDimension());
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
        s2 += Utility::integerToString(f->getDimension());
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


//##ModelId=3DA3E5BE0172
void PartOfPacket::deleteFields()
{
    for(unsigned i = 0; i < numberOfFields; i++)
        delete fields[i];
    delete[] fields;
}


//##ModelId=3DA3E5B701FE
ByteStream* PartOfPacket::generateStream(bool bigendian)
{
    word w = 0, wtemp = 0;
    int posbit = 0;
    word posword = 0;
    short shift;
    //dimensione del field corrente
    byte dimbit = 0;
    if(outputstream == 0)
        outputstream = new ByteStream(getDimension(), bigendian);
    for(unsigned i = 0; i<numberOfFields; i++)
    {
        if(!fields[i]->thereIsPredefinedValue())
            wtemp = fields[i]->value;
        else
            wtemp = fields[i]->value =  fields[i]->getPredefinedValue();
        dimbit = fields[i]->getDimension();
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
            posbit += fields[i]->getDimension();
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

//##ModelId=3DA3E5BA00FA
bool PartOfPacket::setOutputStream(ByteStream* os, dword first)
{
    delete outputstream;
    outputstream = new ByteStream((os->stream + first), getDimension(), os->isBigendian());
    return true;
}

void PartOfPacket::setFieldValue(word index, word value)
{
    if(index < numberOfFields)
        fields[index]->value = (value & pattern[fields[index]->getDimension()]);
}

float PartOfPacket::getFieldValue_5_1(word index)
{
    union u_tag
    {
        unsigned long i;		//32 bit
        float f;	//32 bit single precision
    } u;
    u.i = (getFieldValue(index) << 16) | getFieldValue(index + 1);
    return u.f;
}

void PartOfPacket::setFieldValue_5_1(word index, float value)
{
    union u_tag
    {
        unsigned long i;		//32 bit
        float f;	//32 bit single precision
    } u;
    word w;
    u.f = value;
    w = (word)(u.i >> 16);
    setFieldValue(index, w);
    w = (word)(0xFFFF & u.i);
    setFieldValue(index + 1, w);
}

signed long PartOfPacket::getFieldValue_4_14(word index)
{
    long l;
    l = (long)(getFieldValue(index) << 16) | (long)getFieldValue(index + 1);
    return l;
}

void PartOfPacket::setFieldValue_4_14(word index, signed long value)
{
    word w;
    w = (word)(value >> 16);
    setFieldValue(index, w);
    w = (word) (0xFFFF & value);
    setFieldValue(index + 1, w);
}

unsigned long PartOfPacket::getFieldValue_3_14(word index)
{
    dword l;
    l = (dword)(getFieldValue(index) << 16) | (dword)getFieldValue(index + 1);
    return l;
}

void PartOfPacket::setFieldValue_3_14(word index, unsigned long value)
{
    word w;
    w = (word)(value >> 16);
    setFieldValue(index, w);
    w = (word) (0xFFFF & value);
    setFieldValue(index + 1, w);
}

unsigned long PartOfPacket::getFieldValue_3_13(word index)
{
    word wh, wl;
    wh = getFieldValue(index);
    wl = getFieldValue(index + 1);
    return (dword)(wh << 8) | (dword)(wl & 0xFF);
}

void PartOfPacket::setFieldValue_3_13(word index, unsigned long value) throw(PacketException*)
{
    word w;
    if(value > U24BITINTGEGERUNSIGNED_MAX)
        throw new PacketException("setFieldValue_3_13(): the max value of 24 bit unsigned integer should be 16777215");
    w = (word)(value >> 8);
    setFieldValue(index, w);
    w = (word) (0xFF & value);
    setFieldValue(index + 1, w);
}

signed long PartOfPacket::getFieldValue_4_13(word index)
{
    union u_tag
    {
        unsigned long u;		//32 bit
        signed long s;
    } us;
    us.u = getFieldValue_3_14(index);
    unsigned long sign = (us.u  >> 23); //get the sign
    unsigned long wh = us.u & 0x007FFFFF;
    //get a long 32 bit
    if(sign == 1)
        us.u = 0x7F800000 + wh + (sign << 31);
    else
        us.u = wh + (sign << 31);
    return us.s;
}


void PartOfPacket::setFieldValue_4_13(word index, signed long value) throw(PacketException*)
{
    union u_tag
    {
        unsigned long u;		//32 bit
        signed long s;
    } us;
    if(value > U24BITINTGEGERSIGNED_MAX)
        throw new PacketException("setFieldValue_4_13(): the max value of 24 bit signed integer should be 8388607");
    if(value < U24BITINTGEGERSIGNED_MIN)
        throw new PacketException("setFieldValue_4_13(): the min value of 24 bit signed integer should be -8388607");
    us.s = value;
    unsigned long sign = (us.u >> 31);
    unsigned long wh = us.u & 0x007FFFFF; //23 bit
    unsigned long value2 = 0;
    value2 = wh + (sign << 23);
    setFieldValue_3_14(index, value2);
}

