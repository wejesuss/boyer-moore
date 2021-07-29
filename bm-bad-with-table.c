#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 256

int max(int a, int b)
{
    return (a < b) ? b : a;
}

void make_table(char *pat, size_t len, int *table)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        table[i] = len;
    }

    for (int i = 0; i < len; i++)
    {
        table[(int)pat[i]] = i;
    }
}

void search(char *txt, char *pat, size_t txtlen, size_t patlen, int *table)
{
    for (int i = 0; i <= (txtlen - patlen); i++)
    {
        for (int j = patlen - 1; j >= 0; j--)
        {
            if (pat[j] != txt[i + j])
            {
                i += max(1, j - table[txt[i + j]]);

                i--;
                break;
            }

            if (j == 0)
            {
                printf("pattern occurs at shift %d\n", i);
                i += (i + patlen < txtlen) ? patlen - table[txt[i + patlen]] : 1;
            }
        }
    }
}

int main(void)
{
    char txt[] = "vabdabcca";
    char pat[] = "ab";
    size_t txtlen = strlen(txt);
    size_t patlen = strlen(pat);

    int table[ALPHABET_SIZE];

    make_table(pat, patlen, table);
    search(txt, pat, txtlen, patlen, table);

    return 0;
}