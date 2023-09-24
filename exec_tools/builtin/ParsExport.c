#include "../../minishell.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int count_strings2(const char *s, char c) {
    int count = 0;
    int flag = 0;

    while (*s != '\0') {
        if (*s == '"')
            flag = !flag;

        if (*s == c && !flag)
            count++;
        s++;
    }
    return count + 1;
}

static char *allocation_string2(const char *s, char c) {
    int len = 0;
    int flag = 0;
    char *str;
    int i = 0;
    
    while (s[len] != '\0') {
        if (s[len] == '"')
            flag = !flag;

        if (s[len] == c && !flag)
            break;
        len++;
    }
    str = (char *)malloc(len + 1);
    if (!str)
        return NULL;
    
    while (i < len) {
        str[i] = s[i];
        i++;
    }
    str[len] = '\0';
    return str;
}

static char **ft_free2(char **str, size_t i) {
    while (i > 0) {
        free(str[i - 1]);
        i--;
    }
    free(str);
    return NULL;
}

char **SplitExpo(const char *s, char c) {
    char **str;
    size_t i = 0;

    if (s == NULL)
        return NULL;
    int flag = 0;
    str = (char **)malloc(sizeof(char *) * (count_strings2(s, c) + 1));
    if (!str)
        return NULL;
    
    while (*s != '\0') {
        if (*s == '"')
            flag = !flag;

        while (*s != '\0' && *s == c && !flag)
            s++;

        if (*s != '\0') {
            str[i] = allocation_string2(s, c);
            if (!str[i]) {
                ft_free2(str, i);
                return NULL;
            }
            i++;
        }

        while (*s != '\0' && (*s != c || flag)) {
            if (*s == '"')
                flag = !flag;
            s++;
        }
    }
    str[i] = NULL;
    return str;
}

void freeSplitExpo(char **str)
{
    int i = 0;
    if (str == NULL)
        return;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

char **ParsExport(char *input) {
    int i = 0;
    char **spl = NULL;

    if (strstr(input, "export")) 
    {
        while (input[i] != ' ' && input[i] != '\0')
            i++;
        char *str = strdup(input + i);
        spl = SplitExpo(str, ' ');
        free(str);
        return spl;
    }

    return NULL;
}