#include <stdio.h>
#include "data_figure.h"



int main(void)
{
    figure_t *fig = create_figure();
    const char *filename = "./rect_3d.txt";
    err_t rc = load_figure(filename, *fig);
    if (rc != OK)
        printf("error - %d\n", rc);
    else
        free_data_figure(*fig);
    free(fig);
    return rc;
}