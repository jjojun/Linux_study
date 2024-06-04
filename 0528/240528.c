#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#define LOG_FILE "log.txt"

void write_log(pid_t pid, const char *time_str, const char *reason) {
    int fd = open(LOG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    dprintf(fd, "%-7d %-30s %s\n", pid, time_str, reason);
    close(fd);
}

void handle_sigint(int sig) {
    time_t now = time(NULL);
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0';  // Remove newline character

    printf("bye~\nwriting...\n");
    write_log(getpid(), time_str, "signal(bye~)");
    exit(0);
}

void child_process() {
    signal(SIGINT, handle_sigint);

    sigset_t newmask, oldmask;
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 5; i++) {
        printf("I am a child\n");
        sleep(1);
    }

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    for (int i = 5; i < 10; i++) {
        printf("I am a child\n");
        sleep(1);
    }

    time_t now = time(NULL);
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0';  // Remove newline character

    write_log(getpid(), time_str, "exit");
    exit(0);
}

int main() {
    // Create or clear the log file and write the header
    int fd = open(LOG_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    dprintf(fd, "PID     TIME                          REASON\n");
    close(fd);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        child_process();
    } else {
        int status;
        waitpid(pid, &status, 0);
        time_t now = time(NULL);
        char *time_str = ctime(&now);
        time_str[strlen(time_str) - 1] = '\0';  // Remove newline character

        if (WIFEXITED(status)) {
            printf("Child exited with status %d\n", WEXITSTATUS(status));
            write_log(pid, time_str, "exit");
        } else {
            printf("Child did not exit successfully\n");
            write_log(pid, time_str, "signal");
        }
    }

    return 0;
}

