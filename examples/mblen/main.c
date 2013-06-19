#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>
#include <string.h>

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("Usage %s <string>\n", argv[0]);
        return 0;
    }

    printf("MB_LEN_MAX: %d\n", MB_LEN_MAX);

    setlocale(LC_CTYPE, "C");
    printf("LC_TYPE:C MB_CUR_MAX: %d\n", MB_CUR_MAX);

    const char* loc = getenv("LC_CTYPE");
    setlocale(LC_CTYPE, loc);
    printf("LC_TYPE:%s MB_CUR_MAX: %d\n", loc, MB_CUR_MAX);

    printf("strlen: %d\n", strlen(argv[1]));

    char* str = argv[1];
    int i = 0;
    int c = 0;
    while (str[i] != '\x0') {
        int len = mblen(&str[i], MB_CUR_MAX);
        char mbcp[MB_CUR_MAX + 1];
        memcpy(mbcp, &str[i], len);
        mbcp[len] = '\x0';
        printf("%s\n", mbcp);
        i += len;
        c++;
    }
    printf("mblen: %d\n", c);

    return 0;
}
