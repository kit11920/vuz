#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <sys/time.h>
#include <time.h>

#include "country_struct.h"
#include "errs.h"
#include "sorts.h"
#include "in_output.h"


void rewrite_rand_country_time(struct country_t table[], const size_t len_table)
{
    srand(time(NULL));
    for (size_t i = 0; i < len_table; i++)
        table[i].time = rand() % 1000;
}

unsigned long long ms_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return -1ULL;

    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}

unsigned long long gettime_bubble_sort_orig_table(struct country_t table[], const size_t len_table)
{
    rewrite_rand_country_time(table, len_table);

    unsigned long long beg, end;

    beg = ms_now();
    bubble_sort_orig_table(table, len_table);
    end = ms_now();

    table[0].time = 10;
    table[1].time = table[0].time;

    return end - beg;
}

unsigned long long gettime_merge_sort_orig_table(struct country_t table[], const size_t len_table)
{
    rewrite_rand_country_time(table, len_table);

    unsigned long long beg, end;

    beg = ms_now();
    merge_sort_orig_table(table, 0, len_table - 1);
    end = ms_now();

    table[0].time = 10;
    table[1].time = table[0].time;

    return end - beg;
}

unsigned long long gettime_bubble_sort_key_table(struct country_t table[], const size_t len_table)
{
    rewrite_rand_country_time(table, len_table);

    unsigned long long beg, end;
    struct key_table_t key_table[BIG_TABLE_LEN];

    beg = ms_now();
    make_key_table(table, len_table, key_table);
    bubble_sort_key_table(key_table, len_table);
    end = ms_now();

    table[0].time = 10;
    table[1].time = table[0].time;

    return end - beg;
}

unsigned long long gettime_merge_sort_key_table(struct country_t table[], const size_t len_table)
{
    rewrite_rand_country_time(table, len_table);

    unsigned long long beg, end;
    struct key_table_t key_table[BIG_TABLE_LEN];

    beg = ms_now();
    make_key_table(table, len_table, key_table);
    merge_sort_key_table(key_table, 0, len_table - 1);
    end = ms_now();

    table[0].time = 10;
    table[1].time = table[0].time;

    return end - beg;
}

int make_compare_table(char *data_filename)
{
    struct country_t table[BIG_TABLE_LEN];
    size_t len_table_max;
    size_t step_len = 4000;
    int count_steps = 3;
    int rc;
    int count_repeat = 5;

    rc = read_table(data_filename, table, &len_table_max, BIG_TABLE_LEN);
    if (rc != OK)
        return rc;

    for (size_t len_table = len_table_max; len_table > len_table_max - count_steps * step_len; len_table -= step_len)
    {
        printf("Длина таблицы:     %zu\n", len_table);
        printf("Идет обработка, подождите...\n");

        unsigned long long time_bubble_sort_orig = 0, time_merge_sort_orig = 0;
        unsigned long long time_bubble_sort_key = 0, time_merge_sort_key = 0;
        int percent_orig_table, percent_key_table, percent_bytes, percent_buble_sort, percent_merge_sort;
        size_t bytes_orig_table, bytes_key_table;

        for (int i = 0; i < count_repeat; i++)
        {
            time_bubble_sort_orig += gettime_bubble_sort_orig_table(table, len_table);
            time_merge_sort_orig += gettime_merge_sort_orig_table(table, len_table);
            time_bubble_sort_key += gettime_bubble_sort_key_table(table, len_table);
            time_merge_sort_key += gettime_merge_sort_key_table(table, len_table);
        }
        time_bubble_sort_orig /= count_repeat;
        time_merge_sort_orig /= count_repeat;
        time_bubble_sort_key /= count_repeat;
        time_merge_sort_key /= count_repeat;

        percent_orig_table = (int) round((time_bubble_sort_orig - time_merge_sort_orig) / (double) time_bubble_sort_orig * 100);
        percent_key_table = (int) round((time_bubble_sort_key - time_merge_sort_key) / (double) time_bubble_sort_key * 100);
        percent_buble_sort = (int) round((time_bubble_sort_orig - time_bubble_sort_key) / (double) time_bubble_sort_orig * 100);
        percent_merge_sort = (int) round((time_merge_sort_orig - time_merge_sort_key) / (double) time_merge_sort_orig * 100);

        printf("Сортировки\t\t\tПузырьком\t\tСлиянием\tЭффективность сортировки\n");
        printf("Исходная таблица\t\t%lld ms\t\t\t%lld ms\t\t%d%%\n", time_bubble_sort_orig, time_merge_sort_orig, percent_orig_table);
        printf("Таблица ключей\t\t\t%lld ms\t\t\t%lld ms\t\t%d%%\n", time_bubble_sort_key, time_merge_sort_key, percent_key_table);
        printf("Эффективность хранения\t\t%d%%\t\t\t%d%%\n", percent_buble_sort, percent_merge_sort);

        bytes_orig_table = sizeof(struct country_t) * len_table;
        bytes_key_table = (sizeof(struct country_t) + sizeof(struct key_table_t)) * len_table;
        percent_bytes = (int) round((bytes_key_table - bytes_orig_table) / (double) bytes_key_table * 100);

        printf("\nРазмера (в байтах):\n");
        printf("Исходная таблица\t\tТаблица ключей\t\tНа сколько процентов больше\n");
        printf("%zu\t\t\t\t%zu\t\t\t%d%%\n", bytes_orig_table, bytes_key_table, percent_bytes);
        printf("\n\n");
    }
    return OK;
}

















