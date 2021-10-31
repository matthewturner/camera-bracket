#include "CommandReader.h"

CommandReader::CommandReader(IStreamReader *streamReader)
{
    _streamReader = streamReader;
}

uint8_t CommandReader::tryReadCommand()
{
    uint8_t instructionLength = tryReadInstruction();
    uint8_t command = convertToCommand(instructionLength);
    return command;
}

uint8_t CommandReader::tryReadInstruction()
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

uint8_t CommandReader::convertToCommand(uint8_t instructionLength)
{
    if (instructionLength == 0)
    {
        return NONE;
    }
    if (strcmp(_commandBuffer, "stop") == 0)
    {
        return STOP;
    }
    if (strcmp(_commandBuffer, "calibrate") == 0)
    {
        return CALIBRATE;
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