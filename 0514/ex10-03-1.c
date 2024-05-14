#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_interrupt(int signal) {
    FILE *file = fopen("a.txt", "w");
    if (file != NULL) {
        fprintf(file, "Goodbye!\n");
        fclose(file);
    }
    exit(0);
}

int main() {
    signal(SIGINT, handle_interrupt);

    while (1) {
        printf("I'm sleepy\n");
        sleep(1);
    }

    return 0;
}

