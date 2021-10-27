#include <unity.h>
#include "Dependency.h"

Dependency dependency;

void test_method(void)
{
    bool actual = dependency.method();
    TEST_ASSERT_TRUE(actual);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_method);
    UNITY_END();

    return 0;
}