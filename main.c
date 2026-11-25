#include "header.h"

int main()
{
    FILE *fp, *ft;

    /* Step 1: Comment removal */

    fp = fopen("input.c", "r");
    ft = fopen("temp1.c", "w");

    if (fp == NULL || ft == NULL)
    {
        printf("File opening failed\n");
        return 1;
    }

    comment_rem(fp, ft);

    fclose(fp);
    fclose(ft);

    /* Step 2: File inclusion */

    fp = fopen("temp1.c", "r");
    ft = fopen("temp2.c", "w");

    if (fp == NULL || ft == NULL)
    {
        printf("File opening failed\n");
        return 1;
    }

    header_inc(fp, ft);

    fclose(fp);
    fclose(ft);

    /* Step 3: Macro replacement */

    fp = fopen("temp2.c", "r");
    ft = fopen("output.i", "w");

    if (fp == NULL || ft == NULL)
    {
        printf("File opening failed\n");
        return 1;
    }

    macro_rep(fp, ft);

    fclose(fp);
    fclose(ft);

    printf("Preprocessing completed successfully\n");

    return 0;
}
