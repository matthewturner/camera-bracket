#ifndef CommandReader_h
#define CommandReader_h

#include "IStreamReader.h"
#include "string.h"

const unsigned char NONE = 0;
const unsigned char STOP = 1;
const unsigned char LEFT_10 = 2;
const unsigned char LEFT_25 = 3;
const unsigned char LEFT_45 = 4;
const unsigned char RIGHT_10 = 5;
const unsigned char RIGHT_25 = 6;
const unsigned char RIGHT_45 = 7;

class CommandReader
{
public:
    CommandReader(IStreamReader *streamReader);
    unsigned char tryReadCommand();

private:
    unsigned char tryReadInstruction();
    unsigned char convertToCommand(unsigned char instructionLength);
    char _commandBuffer[20];
    IStreamReader *_streamReader;
};

#endif