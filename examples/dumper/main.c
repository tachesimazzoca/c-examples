#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM_COLS 16

typedef unsigned char byte_t;

void print_ascii_dump(byte_t* dump, size_t size);

int main(int argc, char** argv)
{
    FILE* fp;
    byte_t buf[64];

    if (argc < 2) {
        printf("Usage %s </path/to/file>\n", argv[0]);
        return 0;
    }

    fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        fputs("Error: file open\n", stderr);
        exit(EXIT_FAILURE);
    }

    int err = 0;
    int len = 0;
    byte_t bytes[NUM_COLS];
    while (1) {
        if (feof(fp)) {
            break;
        }
        size_t num = sizeof(buf);
        size_t size = fread(buf, sizeof(byte_t), num, fp);
        if (err = ferror(fp)) {
            break;
        }
        int i = 0;
        for (i = 0; i < size; i++) {
            printf("%02x ", buf[i]);
            bytes[len % NUM_COLS] = buf[i];
            if (len % NUM_COLS == (NUM_COLS - 1)) {
                print_ascii_dump(bytes, sizeof(bytes));
            }
            len++;
        }
    }
    fclose(fp);

    if (err) {
        fputs("Error: file read.\n", stderr);
        exit(EXIT_FAILURE);
    }

    size_t num_bytes = len % NUM_COLS;
    if (num_bytes) {
        int i;
        for (i = 0; i < (NUM_COLS - num_bytes); i++) {
            printf("   ");
        }
        print_ascii_dump(bytes, num_bytes);
    }
    return 0;
}

void print_ascii_dump(byte_t* dump, size_t size)
{
    printf("| ");
    int i;
    for (i = 0; i < size; i++) {
        printf("%c", isprint(dump[i]) ? dump[i] : '.');
    }
    puts("");
}
