#include "header.h"

int is_char(char ch)
{
    if ((ch >= 'A' && ch <= 'Z') ||
        (ch >= 'a' && ch <= 'z') ||
        (ch >= '0' && ch <= '9') ||
        ch == '_')
        return 1;

    return 0;
}

int is_start(char ch)
{
    if ((ch >= 'A' && ch <= 'Z') ||
        (ch >= 'a' && ch <= 'z') ||
        ch == '_')
        return 1;

    return 0;
}

void macro_rep(FILE *fp, FILE *ft)
{
    char line[300];
    char name[50][50];
    char value[50][150];
    char param[50][50];
    char word[50];
    char arg[100];
    char temp[50];

    int count = 0;
    int i, j, k, n;
    int found;
    int function[50];

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (strncmp(line, "#define", 7) == 0)
        {
            if (count >= 50)
                continue;

            i = 7;

            while (line[i] == ' ' || line[i] == '\t')
                i++;

            j = 0;

            while (is_char(line[i]) && j < 49)
            {
                name[count][j++] = line[i];
                i++;
            }

            name[count][j] = '\0';

            function[count] = 0;
            param[count][0] = '\0';

            if (line[i] == '(')
            {
                function[count] = 1;
                i++;

                while (line[i] == ' ' || line[i] == '\t')
                    i++;

                j = 0;

                while (is_char(line[i]) && j < 49)
                {
                    param[count][j++] = line[i];
                    i++;
                }

                param[count][j] = '\0';

                while (line[i] != ')' && line[i] != '\0')
                    i++;

                if (line[i] == ')')
                    i++;
            }

            while (line[i] == ' ' || line[i] == '\t')
                i++;

            j = 0;

            while (line[i] != '\0' && line[i] != '\n' && j < 149)
            {
                value[count][j++] = line[i];
                i++;
            }

            value[count][j] = '\0';

            count++;
        }
        else
        {
            i = 0;

            while (line[i] != '\0')
            {
                if (is_start(line[i]))
                {
                    j = 0;

                    while (is_char(line[i]) && j < 49)
                    {
                        word[j++] = line[i];
                        i++;
                    }

                    word[j] = '\0';
                    found = 0;

                    for (k = 0; k < count; k++)
                    {
                        if (strcmp(word, name[k]) == 0)
                        {
                            found = 1;

                            if (function[k] == 0)
                            {
                                fputs(value[k], ft);
                            }
                            else if (line[i] == '(')
                            {
                                i++;
                                j = 0;

                                while (line[i] != ')' &&
                                       line[i] != '\0' &&
                                       j < 99)
                                {
                                    arg[j++] = line[i];
                                    i++;
                                }

                                arg[j] = '\0';

                                if (line[i] == ')')
                                    i++;

                                j = 0;

                                while (value[k][j] != '\0')
                                {
                                    if (is_start(value[k][j]))
                                    {
                                        n = 0;

                                        while (is_char(value[k][j]) &&
                                               n < 49)
                                        {
                                            temp[n++] = value[k][j];
                                            j++;
                                        }

                                        temp[n] = '\0';

                                        if (strcmp(temp, param[k]) == 0)
                                            fputs(arg, ft);
                                        else
                                            fputs(temp, ft);
                                    }
                                    else
                                    {
                                        fputc(value[k][j], ft);
                                        j++;
                                    }
                                }
                            }
                            else
                            {
                                fputs(word, ft);
                            }

                            break;
                        }
                    }

                    if (found == 0)
                        fputs(word, ft);
                }
                else
                {
                    fputc(line[i], ft);
                    i++;
                }
            }
        }
    }
}
