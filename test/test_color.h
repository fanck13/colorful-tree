#ifndef _TEST_COLOR_H_
#define _TEST_COLOR_H_

#include "CuTest.h"

void test_get_background_color_by_ext(CuTest* tc);

void test_get_foreground_color_by_ext(CuTest* tc);

CuSuite* test_color_suite(void);

#endif