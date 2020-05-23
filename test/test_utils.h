#ifndef __TEST_UTILS_H__
#define __TEST_UTILS_H__

#include "CuTest.h"
#include "utils.h"

void test_get_file_ext(CuTest* tc);
void test_file_exist(CuTest* tc);
void test_end_with(CuTest* tc);
void test_start_with(CuTest* tc);

CuSuite* test_utils_suite(void);

#endif