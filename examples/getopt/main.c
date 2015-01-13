#include<stdio.h>
#include<unistd.h>

static void print_usage(char *cmd);

static void print_opt_status();

int
main(int argc, char **argv)
{
    int opt;

    // Whether or not the function getopt prints
    // an error message to stderr.
    opterr = 1;

    while ((opt = getopt(argc, argv, "vhp:")) != -1)
    {
        switch(opt) {
        case 'v':
            puts("example-getopt version 0.1.0");
            break;
        case 'h':
            print_usage(argv[0]);
            break;
        case 'p':
            print_opt_status();
            break;
        case '?':
            break;
        default:
            break;
        }
    }
}

static void
print_usage(char *cmd)
{
    printf("%s -vh -p [parameter]\n", cmd);
}

static void
print_opt_status()
{
    printf("optarg = %s\n", optarg); // The text of the following argv-element
    printf("optind = %d\n", optind); // The index of the next element to be processed in argv
    printf("optopt = %c\n", optopt); // The actual option character
}
