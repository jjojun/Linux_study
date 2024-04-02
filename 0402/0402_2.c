#include <stdio.h>
#include <dirent.h>
#include <string.h>

void countFilesAndDirectories(const char *path, int *fileCount, int *dirCount) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (dir == NULL) {
        printf("ERROR\n");
        return;
    }

    *fileCount = 0;
    *dirCount = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            if (entry->d_type == DT_DIR) {
                (*dirCount)++;
            } else if (entry->d_type == DT_REG) {
                (*fileCount)++;
            }
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }

    char *directoryPath = argv[1]; 
    int fileCount, dirCount;
    
    countFilesAndDirectories(directoryPath, &fileCount, &dirCount);

    printf("File CNT: %d\n", fileCount);
    printf("DIR CNT: %d\n", dirCount);

    return 0;
}

