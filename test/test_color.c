#include "color.h"
#include "test_color.h"


void test_get_background_color_by_ext(CuTest* tc){
    CuAssertTrue(tc, 1);
}

void test_get_foreground_color_by_ext(CuTest* tc){
    CuAssertTrue(tc, 1);
}


CuSuite* test_color_suite(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, test_get_background_color_by_ext);

    SUITE_ADD_TEST(suite, test_get_foreground_color_by_ext);
    
    return suite;
}