#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int n;
    printf("num : ");
    scanf("%d", &n);

    pid_t pid = fork();

    if (pid > 0) {
        int product = 1;
        for (int i = 1; i <= n; ++i) {
            product *= i;
        }
        printf("mul = %d\n", product);
    } else if (pid == 0) {
        int sum = 0;
        for (int i = 1; i <= n; ++i) {
            sum += i;
        }
        printf("sum = %d\n", sum);
    } else {
        fprintf(stderr, "Error\n");
        return 1;
    }

    return 0;
}

