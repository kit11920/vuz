#include <stdlib.h>
#include <check.h>
#include <stdio.h>

#include "check_search_string.h"
#include "check_del_2spaces.h"
#include "check_cat_str_list.h"

int main(void)
{
    int no_failed = 0;

    {
        Suite *s;
        SRunner *runner;

        s = search_string_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }
    {
        Suite *s;
        SRunner *runner;

        s = del_2spaces_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }
    {
        Suite *s;
        SRunner *runner;

        s = cat_str_list_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }

    printf("FAILED: %d\n", no_failed);
    return no_failed;
}
