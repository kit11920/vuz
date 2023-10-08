#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "tests.h"
#include "number.h"
#include "arithmetic.h"
#include "errs.h"


void print_num_to_str(const struct number_t *num, char *buf)
{
    //del_insignificant_zeros(num->mantissa, &num->len_arr, &num->k);

    char part_buf[MAX_LEN_BUF];

    int k = num->k + num->len_arr; // порядок в нормализованном виде
    assert(-99999 <= k && k <= 99999);

    if (num->sign < 0)
        sprintf(part_buf, "-");
    else
        sprintf(part_buf, "+");
    strcat(buf, part_buf);

    sprintf(part_buf, "0.");
    strcat(buf, part_buf);
    for (int i = num->len_arr - 1; i >= 0; i--)
    {
        sprintf(part_buf, "%d", num->mantissa[i]);
        strcat(buf, part_buf);
    }
    
    sprintf(part_buf, " E %+d", k);
    strcat(buf, part_buf);
}


void test_get_number_from_str(const char *input_str, const char *expected_output, int expected_rc)
{
    struct number_t num;
    char str[MAX_LEN_BUF];
    int rc = OK;

    rc = get_number_from_str(input_str, &num);
    if (rc == OK)
    {
        print_num_to_str(&num, str);
        if (strcmp(str, expected_output) != 0)
        {
            printf("ERROR -    \"%s\"\n", input_str);
            printf("expected - \"%s\"\n", expected_output);
            printf("have -     \"%s\"\n\n", str);
        }
        str[0] = 0;
    }
    else if (rc != expected_rc)
    {
        printf("ERROR -    \"%s\"\n", input_str);
        printf("expected rc - \"%d\"\n", expected_rc);
        printf("have rc -     \"%d\"\n\n", rc);
    }

}

void all_tests_get_number_from_str()
{
    test_get_number_from_str("123", "+0.123 E +3", OK);
    test_get_number_from_str("  -123.34  ", "-0.12334 E +3", OK);
    test_get_number_from_str("0.123", "+0.123 E +0", OK);
    test_get_number_from_str(".123", "+0.123 E +0", OK);
    test_get_number_from_str("123.", "+0.123 E +3", OK);
    test_get_number_from_str("0.", "+0.0 E +1", OK);
    test_get_number_from_str(".0", "+0.0 E +1", OK);
    test_get_number_from_str("000.000", "+0.0 E +1", OK);
    test_get_number_from_str("0.00400", "+0.4 E -2", OK);
    test_get_number_from_str("023", "+0.23 E +2", OK);
    test_get_number_from_str("2340", "+0.234 E +4", OK);
    test_get_number_from_str("2340.00", "+0.234 E +4", OK);
    test_get_number_from_str("01234567890123456789.01234567890123456789", "+0.123456789012345678901234567890123456789 E +19", OK);
    
    test_get_number_from_str("12 e 1", "+0.12 E +3", OK);
    test_get_number_from_str("12.1 E 3", "+0.121 E +5", OK);
    test_get_number_from_str("12e 1", "+0.12 E +3", OK);
    test_get_number_from_str("12 e1", "+0.12 E +3", OK);
    test_get_number_from_str("12e1", "+0.12 E +3", OK);
    test_get_number_from_str("12 e -1", "+0.12 E +1", OK);
    test_get_number_from_str("12e+1", "+0.12 E +3", OK);
    test_get_number_from_str("12 e 0", "+0.12 E +2", OK);
    test_get_number_from_str(".0    e11", "+0.0 E +1", OK);
    test_get_number_from_str("12e-10", "+0.12 E -8", OK);
    test_get_number_from_str("  12 e 1  ", "+0.12 E +3", OK);
    test_get_number_from_str("1.23e-99999", "+0.123 E -99998", OK);


    // errors
    test_get_number_from_str(".", "", ERR_NO_MANTISSA);
    test_get_number_from_str("qwe", "", ERR_NO_MANTISSA);
    test_get_number_from_str(".qwe", "", ERR_NO_MANTISSA);
    test_get_number_from_str("012345678901234567890123456789012345678901234567890", "", ERR_RANGE_MANTISSA);
    test_get_number_from_str("01234567890123456789012345678901234567890.123456789", "", ERR_RANGE_MANTISSA);
    test_get_number_from_str("-1234567890123456789012345678901234567890.123456789", "", ERR_RANGE_MANTISSA);
    test_get_number_from_str("12e qwe", "", ERR_IO);
    test_get_number_from_str("12 q 12", "", ERR_IO);
    test_get_number_from_str("12 ee 3", "", ERR_IO);
    test_get_number_from_str("12 e", "", ERR_IO);
    test_get_number_from_str("12 e 12e", "", ERR_IO);
    test_get_number_from_str("12e123456", "", ERR_ORDER_OVERFLOW);

    printf("\nend testing\n");
}


