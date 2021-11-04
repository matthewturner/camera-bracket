#ifndef CommandReader_h
#define CommandReader_h

#include "IStreamReader.h"
#include "stdint.h"
#include "string.h"

enum commands
{
    NONE = 0,
    STOP = 1,
    CALIBRATE = 2,
    LEFT = 3,
    RIGHT = 4,
    MOVE_TO = 5,
    STATUS = 6
};
typedef enum commands Commands;

struct command
{
    Commands Value;
    short Data;
};
typedef struct command Command;

class CommandReader
{
public:
    CommandReader(IStreamReader *streamReader);
    bool tryReadCommand(Command *command);

private:
    bool tryReadInstruction();
    bool convertToCommand(Command *command);
    char _commandBuffer[20];
    char _dataBuffer[20];
    short _commandIndex = -1;
    short _dataIndex = -1;
    IStreamReader *_streamReader;
};

#endif