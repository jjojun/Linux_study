#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#define LOG_FILE "log.txt"
#define DURATION 180

void write_log(pid_t pid, int count, const char *reason) {
    int fd = open(LOG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    time_t now = time(NULL);
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0';  // Remove newline character

    if (count != -1) {
        dprintf(fd, "%-7d %-30s %s\n", pid, time_str, reason);
    } else {
        dprintf(fd, "%-7d %-30s %s\n", pid, time_str, reason);
    }

    close(fd);
}

void handle_sigint(int sig) {
    printf("bye~\nwriting...\n");
    write_log(getpid(), -1, "signal(bye~)");
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
        //write_log(getpid(), i + 1, "exit");
        sleep(1);
    }

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    for (int i = 5; i < 10; i++) {
        printf("I am a child\n");
        //write_log(getpid(), i + 1, "exit");
        sleep(1);
    }

    //write_log(getpid(), 10, "exit");
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

    time_t start_time = time(NULL);
    while (time(NULL) - start_time < DURATION) {
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
            if (WIFEXITED(status)) {
                printf("Child exited with status %d\n", WEXITSTATUS(status));
                write_log(pid, -1, "exit");
            } else {
                printf("Child did not exit successfully\n");
                write_log(pid, -1, "signal");
            }
        }
    }

    return 0;
}
