#include "header.h"

void header_inc(FILE *fp, FILE *ft)
{
    char line[300];
    char filename[100];

    int i, j;
    int ch;
    FILE *fh;

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (strncmp(line, "#include", 8) == 0)
        {
            i = 8;

            while (line[i] == ' ' || line[i] == '\t')
                i++;

            if (line[i] == '<')
            {
                /* Preserve system header */
                fputs(line, ft);
            }
            else if (line[i] == '"')
            {
                i++;
                j = 0;

                while (line[i] != '"' && line[i] != '\0')
                {
                    if (j < 99)
                        filename[j++] = line[i];

                    i++;
                }

                filename[j] = '\0';

                fh = fopen(filename, "r");

                if (fh == NULL)
                {
                    printf("Header file opening failed: %s\n", filename);
                    continue;
                }

                while ((ch = fgetc(fh)) != EOF)
                {
                    fputc(ch, ft);
                }

                fclose(fh);
            }
            else
            {
                fputs(line, ft);
            }
        }
        else
        {
            fputs(line, ft);
        }
    }
}
