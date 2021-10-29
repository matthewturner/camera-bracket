#include "CommandReader.h"

CommandReader::CommandReader(IStreamReader *streamReader)
{
    _streamReader = streamReader;
}

unsigned char CommandReader::tryReadCommand()
{
    unsigned char instructionLength = tryReadInstruction();
    unsigned char instruction = convertToCommand(instructionLength);
    return instruction;
}

unsigned char CommandReader::tryReadInstruction()
{
    int index = -1;
    while (_streamReader->available())
    {
        char ch = _streamReader->read();
        switch (ch)
        {
        case '>':
            index = 0;
            break;
        case '!':
            _commandBuffer[index] = '\0';
            return index + 1;
        default:
            _commandBuffer[index] = ch;
            index++;
            break;
        }
    }
    return 0;
}

unsigned char CommandReader::convertToCommand(unsigned char instructionLength)
{
    if (instructionLength == 0)
    {
        return NONE;
    }
    if (strcmp(_commandBuffer, "stop") == 0)
    {
        return STOP;
    }
    if (strcmp(_commandBuffer, "left-45") == 0)
    {
        return LEFT_45;
    }
    if (strcmp(_commandBuffer, "right-45") == 0)
    {
        return RIGHT_45;
    }
    return NONE;
}