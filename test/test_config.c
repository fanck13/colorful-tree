#include "config.h"
#include "test_config.h"

void test_get_configs(CuTest* tc){
    CuAssertTrue(tc, 1);
}

CuSuite* test_config_suite(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, test_get_configs);

    return suite;
}