#include <stdio.h>

#include "CuTest.h"
#include "test_color.h"
#include "test_tree.h"
#include "test_config.h"
#include "test_arguments.h"
#include "test_map.h"
#include "test_utils.h"


void RunAllTests(void)
{
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();

    CuSuiteAddSuite(suite, test_color_suite());
    CuSuiteAddSuite(suite, test_tree_suite());
    CuSuiteAddSuite(suite, test_config_suite());
    CuSuiteAddSuite(suite, test_arguments_suite());
    CuSuiteAddSuite(suite, test_map_suite());
    CuSuiteAddSuite(suite, test_utils_suite());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
}


int main()
{
    RunAllTests();
    return 0;
}