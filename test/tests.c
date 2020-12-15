#include <stdbool.h>

#include "cutest.h"

#include "../src/filter.h"

void test_dummy(void)
{
    TEST_CHECK(0 != 7);
}


void test_single_exclude(void)
{
    append_rule("/hello/deary*", true);
    TEST_CHECK(exclude_path("/hello/deary") == true);
    TEST_CHECK(exclude_path("/hello/deary/hehehe") == true);
    TEST_CHECK(exclude_path("/hello/deary/hehehe/") == true);
    TEST_CHECK(exclude_path("/hello/dear/hehehe") == false);
    TEST_CHECK(exclude_path("/usr/lib/libc.so") == false);
}

void test_multiple_exclude(void)
{
    append_rule("/hello/deary*", true);
    append_rule("/hi**", true);
    TEST_CHECK(exclude_path("/hello/deary") == true);
    TEST_CHECK(exclude_path("/hi/mike") == true);
    TEST_CHECK(exclude_path("/hello/deary/hehehe") == true);
    TEST_CHECK(exclude_path("/hello/deary/hehehe/") == true);
    TEST_CHECK(exclude_path("/hello/dear/hehehe") == false);
    TEST_CHECK(exclude_path("/usr/lib/libc.so") == false);
}

void test_include(void)
{
    default_exclude = true;
    append_rule("/hello/deary*", false);
    append_rule("/hi**", false);

    TEST_CHECK(exclude_path("/hello/deary") == false);
    TEST_CHECK(exclude_path("/hi/mike") == false);
    TEST_CHECK(exclude_path("/hello/deary/hehehe") == false);
    TEST_CHECK(exclude_path("/hello/deary/hehehe/") == false);
    TEST_CHECK(exclude_path("/hello/dear/hehehe") == true);
    TEST_CHECK(exclude_path("/usr/lib/libc.so") == true);

    default_exclude = false;
}

void test_include_overlap(void)
{
    append_rule("/hello/*", true);
    append_rule("/hello/deary/*", false);
    TEST_CHECK(exclude_path("/hello/deary/hehehe") == false);
    TEST_CHECK(exclude_path("/hello/dear/hehehe") == true);
}

TEST_LIST = {
    {"Test single exclude", test_single_exclude},
    {"Test multiple exclude", test_multiple_exclude},
    {"Test include", test_include},
    {"Test Overlapping include", test_include_overlap},
    {0}
};

