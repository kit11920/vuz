#include "tests.h"

int main(void)
{
    int count_fall = 0;
    count_fall += all_tests_strpbrk();
    count_fall += all_tests_strspn();
    count_fall += all_tests_strcspn();
    count_fall += all_tests_strchr();
    count_fall += all_tests_strrchr();

    printf("%d\n", count_fall);
}
