#ifndef CommandReader_h
#define CommandReader_h

#include "IStreamReader.h"
#include "Arduino.h"
#include "string.h"

const uint8_t NONE = 0;
const uint8_t STOP = 1;
const uint8_t CALIBRATE = 2;
const uint8_t LEFT_45 = 3;
const uint8_t RIGHT_45 = 4;

class CommandReader
{
public:
    CommandReader(IStreamReader *streamReader);
    uint8_t tryReadCommand();

private:
    uint8_t tryReadInstruction();
    uint8_t convertToCommand(uint8_t instructionLength);
    char _commandBuffer[20];
    IStreamReader *_streamReader;
};

#endif