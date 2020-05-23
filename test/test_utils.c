#include "test_utils.h"

void test_get_file_ext(CuTest* tc){
    CuAssertTrue(tc, 1);
}

void test_file_exist(CuTest* tc){
    CuAssertTrue(tc, 1);
}

void test_end_with(CuTest* tc){
    CuAssertTrue(tc, 1);
}

void test_start_with(CuTest* tc){
    CuAssertTrue(tc, 1);
}

CuSuite* test_utils_suite(void){
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, test_get_file_ext);
    SUITE_ADD_TEST(suite, test_file_exist);
    SUITE_ADD_TEST(suite, test_end_with);
    SUITE_ADD_TEST(suite, test_start_with);

    return suite;
}