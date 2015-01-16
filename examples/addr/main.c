#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
#include<netdb.h>
#include<arpa/inet.h>

int
main(int argc, char **argv)
{
    struct addrinfo hints, *result, *rp;
    struct in_addr addr;
    int err;

    if (2 != argc) {
        fprintf(stderr, "Usage: %s <hostname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    memset(&hints, '\0', sizeof(hints));
    puts("sa_family_t");
    printf("  AF_UNSPEC = %d\n", AF_UNSPEC);
    printf("  AF_INET   = %d\n", AF_INET);  // IPv4
    printf("  AF_INET6  = %d\n", AF_INET6); // IPv6
    printf("  AF_UNIX   = %d\n", AF_UNIX);  // UNIX domain socket
    puts("");
    hints.ai_family = AF_INET;

    hints.ai_socktype = SOCK_STREAM;
      // SOCK_STREAM: Byte-stream socket (TCP)
      // SOCK_DRAM: Datagram socket (UDP)

    hints.ai_flags = AI_PASSIVE | AI_CANONNAME;
    hints.ai_protocol = 0;

    err = getaddrinfo(argv[1], NULL, &hints, &result);
    if (0 != err) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
        exit(EXIT_FAILURE);
    }

    for (rp = result; NULL != rp; rp = rp->ai_next) {
        if (NULL != rp->ai_canonname)
            printf("ai_canonname: %s\n", rp->ai_canonname);
        if (NULL != rp->ai_addr) {
            puts("ai_addr:");
            printf("  sa_family: %d\n", rp->ai_addr->sa_family);
            addr.s_addr = ((struct sockaddr_in *)(rp->ai_addr))->sin_addr.s_addr;
            printf("  IPv4: %s\n", inet_ntoa(addr));
        }
        puts("");
    }

    if (NULL != rp) {
      freeaddrinfo(result);
    }
}
