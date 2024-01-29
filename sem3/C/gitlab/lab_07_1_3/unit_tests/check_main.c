#include <stdlib.h>
#include <check.h>

#include "array.h"

#include "check_mysort.h"
#include "check_key.h"
#include "check_cmp.h"
#include "check_swap.h"


int main(void)
{
    int no_failed = 0;

    {
        Suite *s;
        SRunner *runner;

        s = mysort_suite();
        // Для запуска тестов, всходящих в тестовый набор, нужно создать так называемый
        // "runner".
        runner = srunner_create(s);

        // Вот таким образом запускаются все тесты. С помощью второго параметра (в данном случаев
        // CK_VERBOSE) можно детализировать вывод.
        srunner_run_all(runner, CK_VERBOSE);
        // После того, как все тесты будут выполнены, можно получить по ним дополнительную информацию,
        // например, вот так.
        no_failed += srunner_ntests_failed(runner);
        // Перед завершением main "runner" нужно обязательно освободить.
        srunner_free(runner);
    }
    {
        Suite *s;
        SRunner *runner;

        s = key_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }
    {
        Suite *s;
        SRunner *runner;

        s = cmp_int_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }
    {
        Suite *s;
        SRunner *runner;

        s = cmp_str_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }
    {
        Suite *s;
        SRunner *runner;

        s = swap_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);

        no_failed += srunner_ntests_failed(runner);

        srunner_free(runner);
    }



    return no_failed;
}

