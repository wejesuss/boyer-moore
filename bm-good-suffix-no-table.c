#include <stdio.h>
#include <string.h>
#include <time.h>

int max(int a, int b) { return (a < b) ? b : a; }

void search(char *txt, char *pat, size_t txtlen, size_t patlen)
{
    double time_spent = 0.0;

    clock_t begin = clock();

    for (int i = 0; i <= (txtlen - patlen); i++)
    {
        for (int j = patlen - 1; j >= 0; j--)
        {
            if (pat[j] != txt[i + j])
            {
                size_t matches = patlen - j - 1;
                // printf("pattern matched %s\n", &pat[j+1]);
                // printf("pattern matched %d characters with T\n", matches);

                if (matches > 0)
                {
                    // loop from j through patlen
                    // compare pat[j-(j-i)] == pat[(patlen - 1) - (j - i)]
                    // if all comparisons are true (we found &pat[j+1])
                    //     shift pat by patlen - j
                    // else (t[(patlen - 1) - (j - i)] != pat[j - (j - i)])
                    //     j or i -= 1
                    // valores e cáculos ilustrativos
                    // não considera preffix
                    // são dois nested loops

                    signed long long subs_end = j;
                    while (subs_end >= 0)
                    {
                        size_t starting = max(0, (subs_end + 1) - matches);
                        size_t n_comps = subs_end - starting + 1;

                        int diff = strncmp(&pat[starting], &pat[patlen - n_comps], n_comps);

                        // printf("i position %d ", i);
                        // printf("comparing %d chars in string %s starting from %d until %d ", n_comps, pat, starting, subs_end);
                        // printf("diff result %d\n", diff);

                        if (diff == 0)
                        {
                            i += (patlen - 1) - subs_end - 1;
                            break;
                        }

                        subs_end--;
                    }
                }

                break;
            }

            if (j == 0)
            {
                printf("pattern occurs at shift %d\n", i);
            }
        }
    }

    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\ntotal time: %f seconds\n", time_spent);
}

int main(void)
{
    char txt[] = "ABCFGFGCFG";
    char pat[] = "FGFG";
    size_t txtlen = strlen(txt);
    size_t patlen = strlen(pat);

    search(txt, pat, txtlen, patlen);

    return 0;
}