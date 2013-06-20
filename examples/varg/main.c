#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int sum(size_t size, ...);
char* concat(char* str, ...);

int main(void)
{
    printf("sum(3, 1, 2, 3) = %d\n", sum(3, 1, 2, 3));

    char buf[256];
    concat(buf, "Foo", "Bar", "Buz", NULL);
    printf("concat(\"Foo\", \"Bar\", \"Buz\", NULL) = %s\n", buf);

    concat(buf, NULL);
    printf("concat(NULL) = %s\n", buf);

    concat(buf, "Hoge", "Piyo", NULL);
    printf("concat(\"Hoge\", \"Piyo\", NULL) = %s\n", buf);
}

int sum(size_t size, ...)
{
    va_list args;
    int total;
    int i;

    total = 0;
    va_start(args, size);
    for (i = 0; i < size; i++) {
        total += va_arg(args, int);
    }
    va_end(args);

    return total;
}

char* concat(char* str, ...)
{
    va_list args;
    char* s;
    char* p;

    p = str;

    va_start(args, str);
    *str = '\x0';
    for (s = va_arg(args, char*); s != NULL; s = va_arg(args, char*)) {
        size_t len = strlen(s);
        memcpy(str, s, len);
        str += len;
        *str = '\x0';
    }
    va_end(args);

    return p;
}
