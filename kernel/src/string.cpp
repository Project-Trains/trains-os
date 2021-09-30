#include "string.h"

char *strcpy(char *s1, const char *s2)
{
    strncpy(s1, s2, strlen(s2) + 1);
    s1[strlen(s2)] = '\0';
    return s1;
}

char *strncpy(char *s1, const char *s2, size_t n)
{
    unsigned int j = 0;
    for (unsigned int i = 0; i < n; i++) {
        if (s2[i] != '\0') {
            s1[i] = s2[i];
        } else {
            s1[i] = s2[i];
            j = i + 1;
            break;
        }
    }

    while (j < n) {
        s1[j] = '\0';
        j++;
    }

    return s1;
}

uint32_t strcmp(const char *s1, const char *s2)
{
    if (strlen(s1) != strlen(s2))
        return s2 - s1;
    return strncmp(s1, s2, strlen(s1));
}

uint32_t strncmp(const char *s1, const char *s2, size_t n)
{
    unsigned int count = 0;
    while (count < n) {
        if (s1[count] == s2[count]) {
            if (s1[count] == '\0')
                return 0;
            else
                count++;
        } else {
            return s1[count] - s2[count];
        }
    }
    return 0;
}

uint32_t strlen(const char *str)
{
    const char *s;

    for (s = str; *s; ++s);
    return (s - str);
}
