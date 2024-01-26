#include <stdlib.h>
// #include <stdio.h>
#include <check.h>

#include "check_assoc_array_find.h"
#include "check_assoc_array_remove.h"
#include "check_assoc_array_each.h"
#include "check_assoc_array_min.h"
#include "check_assoc_array_max.h"


int main(void)
{
    int no_failed = 0;

    {
        Suite *s;
        SRunner *runner;

        s = find_assoc_array_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }
    {
        Suite *s;
        SRunner *runner;

        s = remove_assoc_array_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }
    {
        Suite *s;
        SRunner *runner;

        s = each_assoc_array_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }
    {
        Suite *s;
        SRunner *runner;

        s = min_assoc_array_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }
    {
        Suite *s;
        SRunner *runner;

        s = max_assoc_array_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }

    // printf("FAIL: %d\n", no_failed);
    return no_failed;
}
