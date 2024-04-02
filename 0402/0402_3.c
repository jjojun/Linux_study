#include <stdio.h>
#include <unistd.h>

int isSymbolicLink(const char *path) {
    if (access(path, F_OK) == 0 && access(path, R_OK) == 0) {
        return (access(path, X_OK) != 0);
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

    if (isSymbolicLink(directoryPath)) {
        printf("YES SYMLINK\n");
    } else {
        printf("NO SYMLINK\n");
    }

    return 0;
}

