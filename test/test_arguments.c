#include "test_arguments.h"

void test_process_arguments(CuTest* tc){
    CuAssertTrue(tc, 1);
}

CuSuite* test_arguments_suite(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, test_process_arguments);
    
    return suite;
}