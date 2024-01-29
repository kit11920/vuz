#include <stdlib.h>
#include <check.h>

#include "check_insert.h"
#include "check_find.h"
#include "check_sort.h"
#include "check_front_back_split.h"
#include "check_sorted_merge.h"
#include "check_remove_duplicates.h"


int main(void)
{
    int no_failed = 0;

    {
        Suite *s;
        SRunner *runner;

        s = insert_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }
    {
        Suite *s;
        SRunner *runner;

        s = find_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }
    {
        Suite *s;
        SRunner *runner;

        s = front_back_split_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }
    {
        Suite *s;
        SRunner *runner;

        s = sorted_merge_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }
    {
        Suite *s;
        SRunner *runner;

        s = sort_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }
    {
        Suite *s;
        SRunner *runner;

        s = remove_duplicates_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }


    return no_failed;
}
