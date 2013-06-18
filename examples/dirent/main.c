#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define IS_RELATIVE_DNAME(dn) \
  (strcmp(dn, ".") == 0 || strcmp(dn, "..") == 0)
#define PRINT_HR() puts("----------------------------------");

char* dtype2str(unsigned char type, char* str);

int main(int argc, char** argv)
{
    DIR *dp;
    struct dirent *ep;

    if (argc < 2) {
        printf("Usage %s </path/to/dir>\n", argv[0]);
        return 0;
    }

    dp = opendir(argv[1]);
    if (dp == NULL) {
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    while (ep = readdir(dp)) {
        if (IS_RELATIVE_DNAME(ep->d_name)) continue;
        printf("d_name: %s\n", ep->d_name);
        printf("d_fileno: %d\n", ep->d_fileno);
        char dt[64];
        printf("d_type: %s %d\n", dtype2str(ep->d_type, dt), ep->d_type);
        PRINT_HR();
    }
    closedir(dp);

    return 0;
}

char* dtype2str(unsigned char type, char* str)
{
    char* p = str;
    switch (type) {
        case DT_UNKNOWN:
            // The type is unknown. Only some filesystems have full support
            // to return the type of the file, others might always return
            // this value.
            strcpy(str, "DT_UNKNOWN");
            break;
        case DT_REG:
            // A regular file.
            strcpy(str, "DT_REG");
            break;
        case DT_DIR:
            // A directory.
            strcpy(str, "DT_DIR");
            break;
        case DT_FIFO:
            // A named pipe, or FIFO.
            strcpy(str, "DT_FIFO");
            break;
        case DT_SOCK:
            // A local-domain socket.
            strcpy(str, "DT_SOCK");
            break;
        case DT_CHR:
            // A character device.
            strcpy(str, "DT_CHR");
            break;
        case DT_BLK:
            // A block device.
            strcpy(str, "DT_BLK");
            break;
        case DT_LNK:
            strcpy(str, "DT_LNK");
            // A symbolic link.
            break;
        default:
          break;
    }
    return p;
}
