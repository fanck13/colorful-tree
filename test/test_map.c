#include "test_map.h"

void test_create_rbtree(CuTest* tc){
    CuAssertTrue(tc, 1);
}

void test_destroy_rbtree(CuTest* tc){
    CuAssertTrue(tc, 1);
}

void test_set(CuTest* tc){
    CuAssertTrue(tc, 1);
}

void test_get(CuTest* tc){
    CuAssertTrue(tc, 1);
}

CuSuite* test_map_suite(void){
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_create_rbtree);
    SUITE_ADD_TEST(suite, test_destroy_rbtree);
    SUITE_ADD_TEST(suite, test_set);
    SUITE_ADD_TEST(suite, test_get);
    return suite;
}