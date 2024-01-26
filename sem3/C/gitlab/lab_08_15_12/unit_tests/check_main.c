#include <stdlib.h>
#include <check.h>

#include "check_addition.h"
#include "check_multiplication.h"
#include "check_invert.h"



int main(void)
{
    int no_failed = 0;

    {
        Suite *s;
        SRunner *runner;

        s = addition_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }
    {
        Suite *s;
        SRunner *runner;

        s = multiplication_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }
    {
        Suite *s;
        SRunner *runner;

        s = invert_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }

    return no_failed;
}



