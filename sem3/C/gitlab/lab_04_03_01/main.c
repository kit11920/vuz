#include <stdio.h>
#include "input_output.h"
#include "change_strings.h"
#include "errors.h"


int main(void)
{
    char str[STR_LEN];
    int rc = OK;

    rc = get_line(str, STR_LEN);
    if (rc != OK)
    {
        print_error(rc);
        return rc;
    }


    size_t count_words;
    char words[COUNT_WORDS][WORD_LEN];
    rc = parse_string(str, words, &count_words);
    printf("%d", rc);
    if (rc == OK)
    {
        if (count_words == 0)
            rc = ERR_ONLY_DELIMS;
        else if (count_words == 1)
            rc = ERR_ONLY_ONE_WORD;
    }
    if (rc != OK)
    {
        print_error(rc);
        return rc;
    }

    size_t count_new_words;
    char new_words[COUNT_WORDS][WORD_LEN];
    rc = make_new_arr_of_words(words, count_words, new_words, &count_new_words);
    if (rc == OK && count_new_words == 0)
        rc = ERR_NO_DIFF_WORDS;
    if (rc != OK)
    {
        print_error(rc);
        return rc;
    }

    char str_out[STR_LEN];
    form_string(new_words, count_new_words, str_out);

    printf("Result: %s\n", str_out);

    return OK;
}













