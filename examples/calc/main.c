#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define FREE(ptr) if (ptr != NULL) { free(ptr); ptr = NULL; }

#define MAX_OPERANDS 32

int safe_realloc(long* vals, size_t size);
long sum_vals(long* vals, size_t num_vals);
float avg_vals(long* vals, size_t num_vals);

int main(void)
{
    char buf[255];
    long* vals;
    long val = 0;
    size_t num_vals = 0;
    size_t max_vals = 2;

    vals = malloc(sizeof(long) * max_vals);
    while (1) {
        if (num_vals == max_vals) {
            if (max_vals >= MAX_OPERANDS) {
                goto max_operands_error;
            }
            max_vals *= 2;
            if (!safe_realloc(vals, sizeof(long) * max_vals)) {
                goto realloc_error;
            }
        }
        fgets(buf, sizeof(buf), stdin);
        if (isspace(buf[0])) {
            break;
        }
        sscanf(buf, "%ld", &val);
        vals[num_vals] = val;
        num_vals++;
        printf("num_vals:%d max_vals:%d\n", num_vals, max_vals);
    }
    max_vals = num_vals;
    if (!safe_realloc(vals, sizeof(long) * max_vals)) {
        goto realloc_error;
    }
    printf("sum:%ld avg:%0.2f\n",
            sum_vals(vals, num_vals), avg_vals(vals, num_vals));
    FREE(vals);

    return 0;

max_operands_error:
    fprintf(stderr, "Error: max operands error.\n");
    goto error;

realloc_error:
    fprintf(stderr, "Error: realloc error.\n");
    goto error;

error:
    FREE(vals);
    exit(EXIT_FAILURE);
}

int safe_realloc(long* vals, size_t size)
{
    long* tmp = realloc(vals, size);
    if (tmp == NULL) {
        free(vals);
        return 0;
    }
    vals = tmp;
    return 1;
}

long sum_vals(long* vals, size_t num_vals)
{
    long n = 0;
    int i;
    for (i = 0; i < num_vals; i++) {
        n += vals[i];
    }
    return n;
}

float avg_vals(long* vals, size_t num_vals)
{
    float sum = (float) sum_vals(vals, num_vals);
    return sum / num_vals;
}
