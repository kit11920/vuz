#include <stdlib.h>
#include <check.h>

#include "check_uni_farr_insert_el.h"
#include "check_uni_find_film_by_key.h"
#include "check_cmp.h"

int main(void)
{
    int no_failed = 0;

    {
        Suite *s;
        SRunner *runner;

        s = unit_farr_insert_el_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }
    {
        Suite *s;
        SRunner *runner;

        s = uni_find_film_by_key_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }
    {
        Suite *s;
        SRunner *runner;

        s = cmp_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }

    return no_failed;
}

