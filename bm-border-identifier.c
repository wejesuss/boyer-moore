#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void free_memory(int error_code, char **substring, int num_of_strings)
{
    if (error_code > 0)
    {
        for (size_t i = 0; i < error_code - 1; i++)
        {
            free(substring[i]);
        }

        free(substring);
    }
    else
    {
        for (size_t i = 0; i < num_of_strings; i++)
        {
            free(substring[i]);
        }

        free(substring);
    }
}

int good_proper_prefix(char **prefixes, char *pat, int patlen)
{
    for (size_t i = 0; i < patlen; i++)
    {
        prefixes[i] = (char *)malloc(sizeof(char) * (patlen + 1));
        if (prefixes[i] == NULL)
        {
            printf("prefixes[i] not allocated\n");
            return i + 1;
        }

        strncpy(prefixes[i], &pat[0], i);
        prefixes[i][i] = '\0';

        printf("%s ", prefixes[i]);
    }

    return 0;
}

int good_proper_suffix(char **suffixes, char *pat, int patlen)
{
    for (size_t i = 0; i < patlen; i++)
    {
        suffixes[i] = (char *)malloc(sizeof(char) * (patlen + 1));
        if (suffixes[i] == NULL)
        {
            printf("suffixes[i] not allocated\n");
            return i + 1;
        }

        strncpy(suffixes[i], &pat[patlen - i], i);
        suffixes[i][i] = '\0';

        printf("%s ", suffixes[i]);
    }

    return 0;
}

void print_borders(char **prefixes, char **suffixes, int patlen)
{
    int i = 0;
    while (i < patlen)
    {
        if (strcmp(prefixes[i], suffixes[i]) == 0)
        {
            printf("\nfound border: %s", prefixes[i]);
        }

        i++;
    }
}

int search_for_borders(char *pat)
{
    int patlen = strlen(pat);
    int error_code = 0;

    char **prefixes = (char **)malloc(sizeof(char *) * patlen);
    if (prefixes == NULL)
    {
        printf("Could not allocate memory for prefixes\n");
        return 1;
    }

    char **suffixes = (char **)malloc(sizeof(char *) * patlen);
    if (prefixes == NULL)
    {
        free(prefixes);
        printf("Could not allocate memory for suffixes\n");
        return 1;
    }

    printf("\n");
    error_code = good_proper_prefix(prefixes, pat, patlen);
    if (error_code > 0)
    {
        free_memory(error_code, prefixes, patlen);
        free(suffixes);
        return 1;
    }

    printf("\n");
    error_code = good_proper_suffix(suffixes, pat, patlen);
    if (error_code > 0)
    {
        free_memory(0, prefixes, patlen);
        free_memory(error_code, suffixes, patlen);
        return 1;
    }

    printf("\n");
    print_borders(prefixes, suffixes, patlen);

    if (patlen > 1)
    {
        search_for_borders(&pat[1]);
    }

    free_memory(error_code, prefixes, patlen);
    free_memory(error_code, suffixes, patlen);

    return 0;
}

int main(void)
{
    char *pat = "ABCD";
    int error_code = 0;

    error_code = search_for_borders(pat);

    return error_code;
}
