#include <unity.h>
#include "CommandReader.h"
#include "SoftwareStreamReader.h"

SoftwareStreamReader streamReader;
Command command;
CommandReader commandReader(&streamReader);

void test_invalid_command(void)
{
    streamReader.setCommand("blah");
    bool actual = commandReader.tryReadCommand(&command);
    TEST_ASSERT_EQUAL(Commands::NONE, command.Value);
}

void test_invalid_command_returns_false(void)
{
    streamReader.setCommand("blah");
    bool actual = commandReader.tryReadCommand(&command);
    TEST_ASSERT_FALSE(actual);
}

void test_non_terminated_command(void)
{
    streamReader.setCommand(">calibrate");
    bool actual = commandReader.tryReadCommand(&command);
    TEST_ASSERT_EQUAL(Commands::NONE, command.Value);
}

void test_calibrate_command(void)
{
    streamReader.setCommand(">calibrate!");
    bool actual = commandReader.tryReadCommand(&command);
    TEST_ASSERT_EQUAL(Commands::CALIBRATE, command.Value);
}

void test_valid_command_returns_true(void)
{
    streamReader.setCommand(">calibrate!");
    bool actual = commandReader.tryReadCommand(&command);
    TEST_ASSERT_TRUE(actual);
}

void test_left_command(void)
{
    streamReader.setCommand(">left!");
    bool actual = commandReader.tryReadCommand(&command);
    TEST_ASSERT_EQUAL(Commands::LEFT, command.Value);
}

void test_right_command(void)
{
    streamReader.setCommand(">right!");
    bool actual = commandReader.tryReadCommand(&command);
    TEST_ASSERT_EQUAL(Commands::RIGHT, command.Value);
}

void test_stop_command(void)
{
    streamReader.setCommand(">stop!");
    bool actual = commandReader.tryReadCommand(&command);
    TEST_ASSERT_EQUAL(Commands::STOP, command.Value);
}

void test_embedded_command(void)
{
    streamReader.setCommand("random>calibrate!random");
    bool actual = commandReader.tryReadCommand(&command);
    TEST_ASSERT_EQUAL(Commands::CALIBRATE, command.Value);
}

void test_command_with_missing_data(void)
{
    streamReader.setCommand(">move-to:!");
    bool actual = commandReader.tryReadCommand(&command);
    TEST_ASSERT_EQUAL(Commands::MOVE_TO, command.Value);
    TEST_ASSERT_EQUAL(0, command.Data);
}

void test_command_with_invalid_data(void)
{
    streamReader.setCommand(">move-to:xxx!");
    bool actual = commandReader.tryReadCommand(&command);
    TEST_ASSERT_EQUAL(Commands::MOVE_TO, command.Value);
    TEST_ASSERT_EQUAL(0, command.Data);
}

void test_command_with_positive_data(void)
{
    streamReader.setCommand(">move-to:35!");
    bool actual = commandReader.tryReadCommand(&command);
    TEST_ASSERT_EQUAL(Commands::MOVE_TO, command.Value);
    TEST_ASSERT_EQUAL(35, command.Data);
}

void test_command_with_negative_data(void)
{
    streamReader.setCommand(">move-to:-35!");
    bool actual = commandReader.tryReadCommand(&command);
    TEST_ASSERT_EQUAL(Commands::MOVE_TO, command.Value);
    TEST_ASSERT_EQUAL(-35, command.Data);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_invalid_command);
    RUN_TEST(test_invalid_command_returns_false);
    RUN_TEST(test_non_terminated_command);
    RUN_TEST(test_calibrate_command);
    RUN_TEST(test_valid_command_returns_true);
    RUN_TEST(test_left_command);
    RUN_TEST(test_right_command);
    RUN_TEST(test_stop_command);
    RUN_TEST(test_embedded_command);
    RUN_TEST(test_command_with_missing_data);
    RUN_TEST(test_command_with_invalid_data);
    RUN_TEST(test_command_with_positive_data);
    RUN_TEST(test_command_with_negative_data);
    UNITY_END();

    return 0;
}