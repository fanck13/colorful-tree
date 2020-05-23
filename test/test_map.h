#ifndef __TEST_MAP_H__
#define __TEST_MAP_H__

#include "CuTest.h"
#include "test_map.h"

void test_create_rbtree(CuTest* tc);
void test_destroy_rbtree(CuTest* tc);

void test_set(CuTest* tc);
void test_get(CuTest* tc);

CuSuite* test_map_suite(void);
#endif