#include "CommandReader.h"

CommandReader::CommandReader(IStreamReader *streamReader)
{
    _streamReader = streamReader;
}

bool CommandReader::tryReadCommand(Command *command)
{
    if (tryReadInstruction())
    {
        return convertToCommand(command);
    }
    return false;
}

bool CommandReader::tryReadInstruction()
{
    _commandIndex = -1;
    _dataIndex = -1;
    while (_streamReader->available())
    {
        char ch = _streamReader->read();
        switch (ch)
        {
        case '>':
            _commandIndex = 0;
            break;
        case ':':
            _dataIndex = 0;
            break;
        case '!':
            _commandBuffer[_commandIndex] = '\0';
            _commandIndex++;
            _dataBuffer[_dataIndex] = '\0';
            _dataIndex++;
            return true;
        default:
            if (_dataIndex == -1)
            {
                _commandBuffer[_commandIndex] = ch;
                _commandIndex++;
            }
            else
            {
                _dataBuffer[_dataIndex] = ch;
                _dataIndex++;
            }
            break;
        }
    }
    return false;
}

bool CommandReader::convertToCommand(Command *command)
{
    command->Value = NONE;
    command->Data = 0;

    if (_commandIndex == 0)
    {
        return false;
    }
    if (strcmp(_commandBuffer, "stop") == 0)
    {
        command->Value = STOP;
        return true;
    }
    if (strcmp(_commandBuffer, "calibrate") == 0)
    {
        command->Value = CALIBRATE;
        return true;
    }
    if (strcmp(_commandBuffer, "left-45") == 0)
    {
        command->Value = LEFT_45;
        return true;
    }
    if (strcmp(_commandBuffer, "right-45") == 0)
    {
        command->Value = RIGHT_45;
        return true;
    }
    if (strcmp(_commandBuffer, "move-to") == 0)
    {
        command->Value = MOVE_TO;
        return true;
    }
    return false;
}