#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

static void trap_signal(int sig, void (*handler)(int));
static void print_signal(int sig);
static void test_sigset();

int
main(int argc, char **argv)
{
    puts("Waiting for either SIGINT or SIGHUP ...");
    puts("  SIGINT: Press CTRL-C");
    trap_signal(SIGINT, print_signal);
    printf("  SIGHUP: $ kill %d -HUP\n", getpid());
    trap_signal(SIGHUP, print_signal);
    pause();
}

static void
trap_signal(int sig, void (*handler)(int))
{
    struct sigaction act;

    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART;
    if (sigaction(sig, &act, NULL)) {
        perror("sigaction(2) failed");
        exit(EXIT_FAILURE);
    }
}

static void
print_signal(int sig)
{
    fprintf(stderr, "Trapped by signal %d\n", sig);
}

static void
test_sigset()
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGHUP);
    sigdelset(&set, SIGHUP);
    sigaddset(&set, SIGPIPE);
    printf("SIGINT  = %d\n", sigismember(&set, SIGINT));
    printf("SIGHUP  = %d\n", sigismember(&set, SIGHUP));
    printf("SIGPIPE = %d\n", sigismember(&set, SIGPIPE));
    printf("SIGTERM = %d\n", sigismember(&set, SIGTERM));
    printf("SIGKILL = %d\n", sigismember(&set, SIGKILL));
    printf("SIGCHLD = %d\n", sigismember(&set, SIGCHLD));
    printf("SIGUSR1 = %d\n", sigismember(&set, SIGUSR1));
}
