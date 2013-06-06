#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_BASE_FROM 10
#define DEFAULT_BASE_TO 10

typedef unsigned char byte;

int base_convert(char* buf, int bufsize, char* str, int from, int to);

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("Usage %s <number> <frombase> <tobase>\n", argv[0]);
        return 0;
    }

    int from = DEFAULT_BASE_FROM;
    int to = DEFAULT_BASE_TO;
    if (argc >= 3) {
        sscanf(argv[2], "%d", &from);
    }
    if (argc >= 4) {
        sscanf(argv[3], "%d", &to);
    }

    char buf[32];
    if (!base_convert(buf, sizeof(buf), argv[1], from, to)) {
        puts("base_convert failed.");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", buf);
    return 0;
}

int base_convert(char* buf, int bufsize, char* str, int from, int to)
{
    if (to == 0) {
        return 0;
    }

    long dec = 0;

    // Convert frombase string to decimal
    {
        int m = strlen(str);
        long b = 1;
        int i;
        for (i = m - 1; i >= 0; i--) {
            int sn = (int) str[i];
            long c;
            if (sn >= '0' && sn <= '9') {
                c = sn - '0';
            }
            else if (sn >= 'a' && sn <= 'z') {
                c = sn - 'a' + 10;
            }
            else if (sn >= 'A' && sn <= 'Z') {
                c = sn - 'A' + 10;
            }
            else {
                // Error: out of range
                return 0;
            }
            if (c >= from) {
                // Error: out of range
                return 0;
            }
            dec += b * c;
            b = b * from;
        }
    }

    // Convert decimal to tobase string
    {
        byte bytes[bufsize + 1];
        int maxlen = sizeof(bytes);
        int len = 0;
        while (dec > 0 && len < maxlen) {
            bytes[len] = (byte) ((dec % to) & 0xff);
            len++;
            dec = dec / to;
        }
        if (len > bufsize) {
            // Error: buffer overflow
            return 0;
        }
        if (len > 0) {
            int m;
            int i = 0;
            for (m = len - 1; m >= 0; m--) {
                byte c = bytes[m];
                if (c >= 0 && c < 10) {
                    buf[i] = (char) ('0' + c);
                }
                else {
                    buf[i] = (char) ('a' + (c - 10));
                }
                i++;
            }
            buf[i] = '\0';
        } else {
            buf[len] = '0';
        }
    }

    return 1;
}
