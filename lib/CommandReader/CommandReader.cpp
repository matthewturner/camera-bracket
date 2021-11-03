#include "CommandReader.h"

CommandReader::CommandReader(IStreamReader *streamReader)
{
    _streamReader = streamReader;
}

bool CommandReader::tryReadCommand(Command &command)
{
    uint8_t instructionLength = tryReadInstruction();
    Command command = convertToCommand(instructionLength);
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

Command CommandReader::convertToCommand(uint8_t instructionLength)
{
    Command command;
    command.Value = NONE;
    command.Data = 0;

    if (instructionLength == 0)
    {
        return command;
    }
    if (strcmp(_commandBuffer, "stop") == 0)
    {
        command.Value = STOP;
        return command;
    }
    if (strcmp(_commandBuffer, "calibrate") == 0)
    {
        command.Value = CALIBRATE;
        return command;
    }
    if (strcmp(_commandBuffer, "left-45") == 0)
    {
        command.Value = LEFT_45;
        return command;
    }
    if (strcmp(_commandBuffer, "right-45") == 0)
    {
        command.Value = RIGHT_45;
        return command;
    }
    return command;
}