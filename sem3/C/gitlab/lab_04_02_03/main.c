 #include <stdio.h>
#include "input_output.h"
#include "change_strings.h"
#include "errors.h"


int main(void)
{
    char str1[STR_LEN], str2[STR_LEN];
    int rc;

    rc = get_line(str1, STR_LEN);
    if (rc != OK)
    {
        print_error(rc);
        return rc;
    }
    rc = get_line(str2, STR_LEN);
    if (rc != OK)
    {
        print_error(rc);
        return rc;
    }


    size_t count_words1, count_words2;
    char words1[COUNT_WORDS][WORD_LEN], words2[COUNT_WORDS][WORD_LEN];
    rc = parse_string(str1, words1, &count_words1);
    if (rc == OK && count_words1 == 0)
        rc = ERR_ONLY_SPACES;
    if (rc != OK)
    {
        print_error(rc);
        return rc;
    }

    rc = parse_string(str2, words2, &count_words2);
    if (rc == OK && count_words2 == 0)
        rc = ERR_ONLY_SPACES;
    if (rc != OK)
    {
        print_error(rc);
        return rc;
    }


    size_t count_diff_words;
    char diff_words[COUNT_WORDS][WORD_LEN];
    diff_words_in_strs(words1, count_words1, words2, count_words2, diff_words, &count_diff_words);


    char str_out[STR_LEN];
    rc = form_string(diff_words, count_diff_words, str_out, STR_LEN);
    if (rc != OK)
    {
        print_error(rc);
        return rc;
    }

    printf("Result: ");
    puts(str_out);

    return OK;
}













