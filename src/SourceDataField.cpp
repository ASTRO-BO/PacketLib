#include "SourceDataField.h"

using namespace PacketLib;

//##ModelId=3DA3E603001E
SourceDataField::SourceDataField(const char* sdfName) : PartOfPacket(sdfName)
{
    fixed = false;
    isblock = false;
    rblock = false;

    indexOfNBlock = new word(1);
    subFromNBlock = new word(1);
    maxNumberOfBlock = new word(1);
    numberOfRealDataBlock = new word(1);
    numberOfBlockFixed = new bool(1);
    indexOfNBlock[0] = 0;
    subFromNBlock[0] = 0;
    maxNumberOfBlock[0] = 0;
    numberOfRealDataBlock[0] = 0;
    numberOfBlockFixed[0] = false;

    reset_output_stream = true;
}

SourceDataField::~SourceDataField()
{
    delete indexOfNBlock;
    delete subFromNBlock;
    delete maxNumberOfBlock;
    delete numberOfRealDataBlock;
    delete numberOfBlockFixed;
}

char* SourceDataField::printInHexadecimal()
{
    dword dim = getDimension();
    ByteStream b(stream->stream, dim, true);
    char* c = b.printStreamInHexadecimal();
    return c;
}

//##ModelId=3C301E8A0081
bool SourceDataField::isBlock()
{
    return isblock;
}


//##ModelId=3C347EA003C8
bool SourceDataField::isFixed()
{
    return fixed;
}


//##ModelId=3C35EF40001F
bool SourceDataField::isNumberOfBlockFixed(word rblockIndex)
{
    return numberOfBlockFixed[rblockIndex];
}


//##ModelId=3C35EF4303B7
word SourceDataField::getMaxNumberOfBlock(word rblockIndex)
{
    return maxNumberOfBlock[rblockIndex];
}


//##ModelId=3C9AEC0B006F
word SourceDataField::getSubFromNBlock(word rblockIndex)
{
    return subFromNBlock[rblockIndex];
}


word SourceDataField::getIndexOfNBlock(word rblockIndex)
{
    return indexOfNBlock[rblockIndex];
}


//##ModelId=3C9AEC0A01AD
void SourceDataField::setNumberOfRealDataBlock(word number, word rblockIndex) throw (PacketException*)
{
    numberOfRealDataBlock[rblockIndex] = number;
    reset_output_stream = true;
}


//##ModelId=3C9AEC0B011F
word SourceDataField::getNumberOfRealDataBlock(word rblockIndex)
{
    return  numberOfRealDataBlock[rblockIndex];
}


//##ModelId=3DA3E63E0384
word SourceDataField::getNumberOfFields()
{
    return PartOfPacket::getNumberOfFields();
};

//##ModelId=3DA3E6380320
word SourceDataField::getNumberOfFields(word block)
{
    return 0;
};

//##ModelId=3DA3E60F0226
dword SourceDataField::getDimension()
{
    return PartOfPacket::getDimension();
}


//##ModelId=3C9AFF7A0170
word SourceDataField::getNumberOfRealElement(word block)
{
    return 0;
}

//##ModelId=3DA3E6430082
void SourceDataField::setNumberOfRealElement(word block, word value)
{

}

void SourceDataField::setFieldValue(word block, word index, word value)
{

}

Field* SourceDataField::getFields(word block, word index)
{
    return 0;
}

word SourceDataField::getFieldValue(word block, word index)
{
    return 0;
}

float SourceDataField::getFieldValue_5_1(word block, word index)
{
    union u_tag
    {
        unsigned long i;		//32 bit
        float f;	//32 bit single precision
    } u;
    u.i = (getFieldValue(block, index) << 16) | getFieldValue(block, index + 1);
    return u.f;
}

void SourceDataField::setFieldValue_5_1(word block, word index, float value)
{
    union u_tag
    {
        unsigned long i;		//32 bit
        float f;	//32 bit single precision
    } u;
    word w;
    u.f = value;
    w = (word)(u.i >> 16);
    setFieldValue(block, index, w);
    w = (word)(0xFFFF & u.i);
    setFieldValue(block, index + 1, w);
}

long SourceDataField::getFieldValue_4_14(word block, word index)
{
    long l;
    l = (long)(getFieldValue(block, index) << 16) | (long)getFieldValue(block, index + 1);
    return l;
}

void SourceDataField::setFieldValue_4_14(word block, word index, signed long value)
{
    word w;
    w = (word)(value >> 16);
    setFieldValue(block, index, w);
    w = (word) (0xFFFF & value);
    setFieldValue(block, index + 1, w);
}

signed long SourceDataField::getFieldValue_4_13(word block, word index)
{
    union u_tag
    {
        unsigned long u;		//32 bit
        signed long s;
    } us;
    us.u = getFieldValue_3_14(block, index);
    unsigned long sign = (us.u  >> 23); //get the sign
    unsigned long wh = us.u & 0x007FFFFF;
    //get a long 32 bit
    if(sign == 1)
        us.u = 0x7F800000 + wh + (sign << 31);
    else
        us.u = wh + (sign << 31);
    return us.s;
}

void  SourceDataField::setFieldValue_4_13(word block, word index, signed long value) throw(PacketException*)
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
    setFieldValue_3_14(block, index, value2);
}

unsigned long SourceDataField::getFieldValue_3_14(word block, word index)
{
    dword l;
    l = (dword)(getFieldValue(block, index) << 16) | (dword)getFieldValue(block, index + 1);
    return l;
}

void SourceDataField::setFieldValue_3_14(word block, word index, unsigned long value)
{
    word w;
    w = (word)(value >> 16);
    setFieldValue(block, index, w);
    w = (word) (0xFFFF & value);
    setFieldValue(block, index + 1, w);
}

unsigned long SourceDataField::getFieldValue_3_13(word block, word index)
{
    word wh, wl;
    wh = getFieldValue(block, index);
    wl = getFieldValue(block, index + 1);
    return (dword)(wh << 8) | (dword)(wl & 0xFF);
}

void SourceDataField::setFieldValue_3_13(word block, word index, unsigned long value) throw(PacketException*)
{
    word w;
    if(value > U24BITINTGEGERUNSIGNED_MAX)
        throw new PacketException("setFieldValue_3_13(): the max value of 24 bit unsigned integer should be 16777215");
    w = (word)(value >> 8);
    setFieldValue(block, index, w);
    w = (word) (0xFF & value);
    setFieldValue(block, index + 1, w);
}

//##ModelId=3DA3E6120276
dword SourceDataField::getDimension(word block)
{
    return 0;
}

dword SourceDataField::getMaxDimension(word nblock)
{
    return 0;
}

//##ModelId=3DA3E60B0064
word SourceDataField::getMaxNumberOfElements(word nblock)
{
    return 0;
}

//##ModelId=3DA3E64B0320
bool SourceDataField::get_reset_output_stream() const
{
    return reset_output_stream;
}


//##ModelId=3DA3E6500168
void SourceDataField::set_reset_output_stream(bool value)
{
    reset_output_stream = value;
}
