#include <stdio.h>

void count_chars_words_lines(FILE *file, int *chars, int *words, int *lines) {
    int ch;
    *chars = *words = *lines = 0;
    int in_word = 0;

    while ((ch = fgetc(file)) != EOF) {
        (*chars)++; 

        if (ch == ' ' || ch == '\n' || ch == '\t') {
            if (in_word) {
                in_word = 0;
                (*words)++;
            }
        } else {
            in_word = 1;
        }

        if (ch == '\n') {
            (*lines)++;
        }
    }

    if (in_word) {
        (*words)++;
    }

    if (*chars == 0 && *lines == 0 && *words == 0) {
        *lines = 1;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");

        if (!file) {
            printf("Error: Unable to open file %s\n", argv[i]);
            continue;
        }

        int chars, words, lines;
        count_chars_words_lines(file, &chars, &words, &lines);

        printf("File: %s\n", argv[i]);
        printf("Lines: %d\n", lines);
        printf("Words: %d\n", words);
        printf("Char: %d\n", chars);
	printf("-----------------------------\n");

        fclose(file);
    }

    return 0;
}

