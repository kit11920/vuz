#include <stdlib.h>
#include <stdio.h>
#include <check.h>

#include "check_k_shift_arr.h"
#include "check_make_sqrt_arr.h"


int main(void)
{
    int failed = 0;
    {
        Suite *s;
        SRunner *runner;

        s = k_shift_arr_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }
    {
        Suite *s;
        SRunner *runner;

        s = make_sqrt_arr_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }

    printf("FAILED: %d\n", failed);
    return failed;
}









































