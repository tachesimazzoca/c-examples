#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_FREE(vals, num_vals) {\
    if (vals != NULL) {\
        int i;\
        for (i = 0; i < num_vals; i++) {\
            if (vals[i] != NULL) { free(vals[i]); vals[i] = NULL; }\
        }\
        free(vals);\
        vals = NULL;\
    }\
}

typedef int (*cmp_t)(const void*, const void*);

int compare_as_int(const void* a, const void* b);
int compare_as_str(const void* a, const void* b);

int main(int argc, char** argv)
{
    char** vals;
    int num_vals = argc - 2;
    size_t val_size = 256;

    if (num_vals <= 1) {
        goto usage;
    }

    cmp_t cmp;
    if (strcmp(argv[1], "int") == 0) {
        cmp = compare_as_int;
    }
    else if (strcmp(argv[1], "str") == 0) {
        cmp = compare_as_str;
    }
    else {
        cmp = NULL;
    }
    if (cmp == NULL) {
        goto usage;
        printf("Usage: %s <int|str> <val,....>\n", argv[0]);
        return 0;
    }

    vals = (char**) malloc(sizeof(char*) * num_vals);
    if (vals == NULL) {
        goto malloc_error;
    }
    int i;
    for (i = 0; i < num_vals; i++) {
        vals[i] = (char*) malloc(val_size);
        if (vals[i] == NULL) {
            goto malloc_error;
        }
        strcpy(vals[i], argv[i + 2]);
    }

    qsort(vals, num_vals, sizeof(char*), cmp);
    for (i = 0; i < num_vals; i++) {
        printf("%s\n", vals[i]);
    }
    ARRAY_FREE(vals, num_vals);

    return 0;

usage:
    printf("Usage: %s <int|str> <val,....>\n", argv[0]);
    return 0;

malloc_error:
    fprintf(stderr, "Error: malloc error.\n");
    ARRAY_FREE(vals, num_vals);
    return 1;
}

int compare_as_int(const void* a, const void* b)
{
    char** pa = (char**) a;
    char** pb = (char**) b;
    int na;
    int nb;
    sscanf(*pa, "%d", &na);
    sscanf(*pb, "%d", &nb);
    return (na - nb);
}

int compare_as_str(const void* a, const void* b)
{
    char** pa = (char**) a;
    char** pb = (char**) b;
    return strcmp(*pa, *pb);
}
