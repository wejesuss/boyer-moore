#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 256

int max(int a, int b) { return (a < b) ? b : a; }

void set_memory(int *shift, int *bpos, int *occurrence, int patlen)
{
    memset(shift, 0, (patlen + 1) * sizeof(int));
    memset(bpos, 0, (patlen + 1) * sizeof(int));
    memset(occurrence, -1, ALPHABET_SIZE * sizeof(int));
}

void good_first_case(int *shift, int *bpos, char *pat, int patlen)
{
    int i = patlen, j = patlen + 1;
    bpos[i] = j;

    while (i > 0)
    {
        while (j <= patlen && pat[i - 1] != pat[j - 1])
        {
            if (shift[j] == 0)
            {
                shift[j] = j - i;
            }

            j = bpos[j];
        }

        i--;
        j--;
        bpos[i] = j;
    }
}

void good_second_case(int *shift, int *bpos, char *pat, int patlen)
{
    int i, j = bpos[0];
    for (i = 0; i <= patlen; i++)
    {
        if (shift[i] == 0)
        {
            shift[i] = j;
        }

        if (i == j)
        {
            j = bpos[j];
        }
    }
}

void bad_character(int *table, char *pat, int patlen)
{
    char a;
    for (size_t i = 0; i < patlen; i++)
    {
        a = pat[i];
        table[(int)a] = i;
    }
}

void good_suffix(int *shift, int *bpos, char *pat, int patlen)
{
    good_first_case(shift, bpos, pat, patlen);
    good_second_case(shift, bpos, pat, patlen);

    // for (int t = 0; t <= patlen; t++)
    // {
    //     printf("%i ", shift[t]);
    // }

    // printf("\n");
    // for (int t = 0; t <= patlen; t++)
    // {
    //     printf("%i ", bpos[t]);
    // }
}

void search(int *shift, int *occurrence, char *text, int textlen, char *pat, int patlen)
{
    int s = 0;

    while (s <= (textlen - patlen))
    {
        int j = patlen - 1;
        while (j >= 0 && text[s + j] == pat[j])
        {
            j--;
        }

        if (j < 0)
        {
            printf("pattern found at shift: %d\n", s);
            s++;
        }
        else
        {
            s += max(shift[j + 1], j - occurrence[(int)text[s + j]]);
        }
    }
}

int main(void)
{
    char *text = "Just trying to figure it out if it actually works";
    char *pat = "it actually works";
    int textlen = strlen(text);
    int patlen = strlen(pat);

    int shift[patlen + 1];
    int bpos[patlen + 1];
    int occurrence[ALPHABET_SIZE];
    set_memory(shift, bpos, occurrence, patlen);

    bad_character(occurrence, pat, patlen);
    good_suffix(shift, bpos, pat, patlen);

    search(shift, occurrence, text, textlen, pat, patlen);

    return 0;
}
