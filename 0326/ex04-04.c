#include <stdio.h>
#include <unistd.h>

int main() {
    const char *file = "b.txt";
    if (access(file, F_OK) != -1) {
        printf("%s exists\n", file);
    } else {
        printf("%s does not exist\n", file);
    }
    return 0;
}
