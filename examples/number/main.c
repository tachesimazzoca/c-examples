#include <stdio.h>
#include <limits.h>

int main(void)
{
    printf("CHAR_BIT: %d\n", CHAR_BIT);
    printf("CHAR_(MIN|MAX): %d ... %d\n", CHAR_MIN, CHAR_MAX);
    printf("SHRT_(MIN|MAX): %d ... %d\n", SHRT_MIN, SHRT_MAX);
    printf("INT_(MIN|MAX): %d ... %d\n", INT_MIN, INT_MAX);
    printf("LONG_(MIN|MAX): %ld ... %ld\n", LONG_MIN, LONG_MAX);

    printf("UCHAR_MAX: %u\n", UCHAR_MAX);
    printf("USHRT_MAX: %u\n", USHRT_MAX);
    printf("UINT_MAX: %u\n", UINT_MAX);
    printf("ULONG_MAX: %lu\n", ULONG_MAX);

    printf("sizeof(char) %lu\n", sizeof(char));
    printf("sizeof(short) %lu\n", sizeof(short));
    printf("sizeof(int) %lu\n", sizeof(int));
    printf("sizeof(float) %lu\n", sizeof(float));
    printf("sizeof(long) %lu\n", sizeof(long));
    printf("sizeof(double) %lu\n", sizeof(double));

    return 0;
}
