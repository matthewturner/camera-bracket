#ifndef CommandReader_h
#define CommandReader_h

#include "IStreamReader.h"
#include "stdint.h"
#include "string.h"

const uint8_t NONE = 0;
const uint8_t STOP = 1;
const uint8_t CALIBRATE = 2;
const uint8_t LEFT_45 = 3;
const uint8_t RIGHT_45 = 4;

struct command
{
    uint8_t Value;
    uint8_t Data;
};
typedef struct command Command;

class CommandReader
{
public:
    CommandReader(IStreamReader *streamReader);
    bool tryReadCommand(Command &command);

private:
    uint8_t tryReadInstruction();
    Command convertToCommand(uint8_t instructionLength);
    char _commandBuffer[20];
    char _dataBuffer[20];
    IStreamReader *_streamReader;
};

#endif