#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"

size_t string_length(const char* str);
char* string_copy(char* str, const char* buf);
char* string_rtrim(char* str);
char* string_alloc(const char* buf);

int main(void)
{
    char buf[256];

    printf("Enter something > ");
    fgets(buf, sizeof(buf), stdin);
    string_rtrim(buf);

    char* str;
    if ((str = string_alloc(buf)) != NULL) {
        printf("str:%p %s\n", str, str);
        free(str);
        str = NULL;
    }
}

size_t string_length(const char* str)
{
    size_t len = 0;
    while (*str++) len++;
    return len;
}

char* string_copy(char* str, const char* buf)
{
    char* p = str;
    while (*str++ = *buf++);
    return p;
}

char* string_rtrim(char* str)
{
    char* p = str;
    while (*++str);
    do {
        str--;
        if (!isspace(*str)) {
            break;
        }
        *str = '\x0';
    } while (p < str);
    return p;
}

char* string_alloc(const char* buf)
{
    size_t len = string_length(buf);
    char* str = malloc(len + 1);
    if (str == NULL) {
        return str;
    }
    str = string_copy(str, buf);
    return str;
}
