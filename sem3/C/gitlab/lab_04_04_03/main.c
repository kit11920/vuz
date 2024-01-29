#include <stdio.h>

#include "input_output.h"
#include "phone_number.h"
#include "errors.h"

int main(void)
{
    char str[STR_LEN];
    int rc;

    rc = get_line(str, STR_LEN);
    if (rc != OK)
        return rc;

    rc = strip(str);
    if (rc != OK)
    {
        printf("NO");
        return OK;
    }

    if (is_phone(str))
        printf("YES");
    else
        printf("NO");

    return OK;
}
