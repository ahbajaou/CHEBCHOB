#include "../../minishell.h"


static int count_strings2(const char *s, char c)
{
    int count = 0;
    int quotes = 0;

    while (*s != '\0')
    {
        if (*s == '"')
            quotes = !quotes;

        if (*s == c && !quotes)
            count++;
        s++;
    }
    return count + 1;
}

static char *allocation_string2(const char *s, char c)
{
    int len = 0;
    int quotes = 0;

    while (s[len] != '\0')
    {
        if (s[len] == '"')
            quotes = !quotes; 

        if (s[len] == c && !quotes)
            break;
        len++;
    }

    char *str = (char *)malloc(len + 1);
    if (!str)
        return NULL;

    for (int i = 0; i < len; i++)
        str[i] = s[i];
    str[len] = '\0';

    return str;
}

static char **ft_free2(char **strings, size_t i)
{
    while (i > 0)
    {
        free(strings[i - 1]);
        i--;
    }
    free(strings);
    return NULL;
}

char **SplitExpo(char const *s, char c)
{
    char **strings;
    size_t i;

    if (s == NULL)
        return NULL;
    int quotes = 0;
    i = 0;
    strings = (char **)malloc(sizeof(char *) * (count_strings2(s, c) + 1));
    if (!strings)
        return NULL;


    while (*s != '\0')
    {
        if (*s == '"')
            quotes = !quotes;

        while (*s != '\0' && *s == c && !quotes)
            s++;

        if (*s != '\0')
        {
            strings[i] = allocation_string2(s, c);
            if (!strings[i])
                return ft_free2(strings, i);
            i++;
        }

        while (*s != '\0' && (*s != c || quotes))
        {
            if (*s == '"')
                quotes = !quotes;
            s++;
        }
    }
    strings[i] = NULL;
    return strings;
}
char **ParsExport(char *input)
{
    int i = 0;
    char **spl;
    spl = NULL;
    if (strstr(input,"export"))
    {
        while (input[i] != ' ' && input[i] != '\0')
            i++;
        char *str = ft__strdup(input + i);
        spl = SplitExpo(str,' ');
        free(str);
        return (spl);

    }
    return (spl);
}
