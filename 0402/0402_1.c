#include <stdio.h>
#include <unistd.h>

int isDirectoryExists(const char *path) {
    if (access(path, F_OK) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }

    char *directoryPath = argv[1];

    if (isDirectoryExists(directoryPath)) {
        printf("YES DIR\n");
    } else {
        printf("NO DIR\n");
    }

    return 0;
}


