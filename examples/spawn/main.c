#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int
main(int argc, char **argv)
{
    pid_t pid;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s /path/to/cat/file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork() failed\n");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        printf("child(PID=%d)\n", getpid());
        execl("/bin/cat", "/bin/cat", argv[1], NULL);
        // It never go to the following code if execl() succeeded.
        exit(EXIT_FAILURE);
    } else {
        printf("parent(PID=%d)\n", getpid());
        int status;
        waitpid(pid, &status, 0);
        printf("child(PID=%d) finished\n", pid);
        printf("  EIFEXITED(status) = %d\n", WIFEXITED(status));
        printf("  WEXITSTATUS(status) = %d\n", WEXITSTATUS(status));
        puts("");
        printf("  EIFSIGNALED(status) = %d\n", WIFSIGNALED(status));
        printf("  ETERMSIG(status) = %d\n", WTERMSIG(status));
        exit(EXIT_SUCCESS);
    }
}
