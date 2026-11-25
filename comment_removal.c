#include "header.h"

void comment_rem(FILE *fp, FILE *ft)
{
    int ch, next;
    int in_string = 0;
    int in_char = 0;
    int escape = 0;

    while ((ch = fgetc(fp)) != EOF)
    {
        if (in_string || in_char)
        {
            fputc(ch, ft);

            if (escape)
                escape = 0;
            else if (ch == '\\')
                escape = 1;
            else if (in_string && ch == '"')
                in_string = 0;
            else if (in_char && ch == '\'')
                in_char = 0;

            continue;
        }

        if (ch == '"')
        {
            in_string = 1;
            fputc(ch, ft);
        }
        else if (ch == '\'')
        {
            in_char = 1;
            fputc(ch, ft);
        }
        else if (ch == '/')
        {
            next = fgetc(fp);

            if (next == '/')
            {
                while ((ch = fgetc(fp)) != EOF && ch != '\n');

                if (ch == '\n')
                    fputc('\n', ft);
            }
            else if (next == '*')
            {
                int prev = 0;

                while ((ch = fgetc(fp)) != EOF)
                {
                    if (ch == '\n')
                        fputc('\n', ft);

                    if (prev == '*' && ch == '/')
                        break;

                    prev = ch;
                }
            }
            else
            {
                fputc('/', ft);

                if (next != EOF)
                {
                    fputc(next, ft);

                    if (next == '"')
                        in_string = 1;
                    else if (next == '\'')
                        in_char = 1;
                }
            }
        }
        else
        {
            fputc(ch, ft);
        }
    }
}
