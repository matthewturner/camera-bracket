#include <unity.h>
#include "CommandReader.h"
#include "SoftwareStreamReader.h"

SoftwareStreamReader streamReader;
CommandReader commandReader(&streamReader);

void test_invalid_command(void)
{
    streamReader.setCommand("blah");
    unsigned char command = commandReader.tryReadCommand();
    TEST_ASSERT_EQUAL(NONE, command);
}

void test_non_terminated_command(void)
{
    streamReader.setCommand(">inflate");
    unsigned char command = commandReader.tryReadCommand();
    TEST_ASSERT_EQUAL(NONE, command);
}

void test_calibrate_command(void)
{
    streamReader.setCommand(">calibrate!");
    unsigned char command = commandReader.tryReadCommand();
    TEST_ASSERT_EQUAL(CALIBRATE, command);
}

void test_left_45_command(void)
{
    streamReader.setCommand(">left-45!");
    unsigned char command = commandReader.tryReadCommand();
    TEST_ASSERT_EQUAL(LEFT_45, command);
}

void test_right_45_command(void)
{
    streamReader.setCommand(">right-45!");
    unsigned char command = commandReader.tryReadCommand();
    TEST_ASSERT_EQUAL(RIGHT_45, command);
}

void test_stop_command(void)
{
    streamReader.setCommand(">stop!");
    unsigned char command = commandReader.tryReadCommand();
    TEST_ASSERT_EQUAL(STOP, command);
}

void test_embedded_command(void)
{
    streamReader.setCommand("random>calibrate!random");
    unsigned char command = commandReader.tryReadCommand();
    TEST_ASSERT_EQUAL(CALIBRATE, command);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_invalid_command);
    RUN_TEST(test_non_terminated_command);
    RUN_TEST(test_calibrate_command);
    RUN_TEST(test_left_45_command);
    RUN_TEST(test_right_45_command);
    RUN_TEST(test_stop_command);
    RUN_TEST(test_embedded_command);
    UNITY_END();

    return 0;
}