#include <stdio.h>
#include <string.h>

void preprocess_strong_suffix(int *shift, int *bpos, char *pat, int m)
{
    // m is the length of pattern
    int i = m, j = m + 1;
    bpos[i] = j;

    while (i > 0)
    {
        /*if character at position i-1 is not equivalent to
          character at j-1, then continue searching to right
          of the pattern for border */
        while (j <= m && pat[i - 1] != pat[j - 1])
        {
            /* the character preceding the occurrence of t in 
               pattern P is different than the mismatching character in P, 
               we stop skipping the occurrences and shift the pattern
               from i to j */
            if (shift[j] == 0)
                shift[j] = j - i;

            //Update the position of next border
            j = bpos[j];
        }
        /* p[i-1] matched with p[j-1], border is found.
           store the  beginning position of border */
        i--;
        j--;
        bpos[i] = j;
    }
}

//Preprocessing for case 2
void preprocess_case2(int *shift, int *bpos, char *pat, int m)
{
    int i, j;
    j = bpos[0];
    for (i = 0; i <= m; i++)
    {
        /* set the border position of the first character of the pattern
           to all indices in array shift having shift[i] = 0 */
        if (shift[i] == 0)
            shift[i] = j;

        /* suffix becomes shorter than bpos[0], use the position of 
           next widest border as value of j */
        if (i == j)
            j = bpos[j];
    }
}

int main(int argc, char const *argv[])
{
    char pat[] = "abbabab";
    int m = strlen(pat);
    int bpos[m + 1], shift[m + 1];
    memset(bpos, 0, sizeof(int) * (m + 1));
    memset(shift, 0, sizeof(int) * (m + 1));

    preprocess_strong_suffix(shift, bpos, pat, m);
    preprocess_case2(shift, bpos, pat, m);

    for (size_t i = 0; i < m + 1; i++)
    {
        printf("%i ", shift[i]);
    }

    printf("\n");
    for (size_t i = 0; i < m + 1; i++)
    {
        printf("%i ", bpos[i]);
    }

    return 0;
}
