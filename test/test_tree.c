#include "test_tree.h"
#include "tree.h"

void test_combine_path(CuTest* tc){
    CuAssertTrue(tc, 1);
}


CuSuite* test_tree_suite(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, test_combine_path);
    
    return suite;
}