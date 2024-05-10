#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ROWS 4
#define COLS 4
#define MAX_WORD_LENGTH 20
#define MAX_GRID_SIZE (ROWS * COLS)

char grid[ROWS][COLS];

// Function to convert a word to lowercase and remove punctuation
void sanitizeWord(char *word) {
    int i, j = 0;
    for (i = 0; word[i]; i++) {
        if (isalpha(word[i])) {
            word[j++] = tolower(word[i]);
        }
    }
    word[j] = '\0';
}

// Function to check if a word is present in the grid
int isWordPresent(char *word) {
    int len = strlen(word);
    int i, j, k;
    int visited[ROWS][COLS];

    sanitizeWord(word); // Convert word to lowercase and remove punctuation

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (grid[i][j] == word[0]) {
                int dirRow[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
                int dirCol[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
                for (k = 0; k < 8; k++) {
                    int row = i + dirRow[k];
                    int col = j + dirCol[k];
                    int pos = 1;
                    memset(visited, 0, sizeof(visited));
                    while (pos < len && row >= 0 && row < ROWS && col >= 0 && col < COLS &&
                           grid[row][col] == word[pos] && !visited[row][col]) {
                        visited[row][col] = 1;
                        pos++;
                        row += dirRow[k];
                        col += dirCol[k];
                    }
                    if (pos == len) return 1;
                }
            }
        }
    }
    return 0;
}

// Function to find words in the grid and print them once
void findWordsInGrid(char *wordListFile) {
    FILE *file = fopen(wordListFile, "r");
    if (file == NULL) {
        printf("Error opening word list file.\n");
        return;
    }

    char word[MAX_WORD_LENGTH];
    printf("Words found in the grid:\n");
    while (fscanf(file, "%s", word) != EOF) {
        if (strlen(word) <= MAX_GRID_SIZE && isWordPresent(word)) {
            printf("%s\n", word);
            // After printing a word, set its first character to '\0' to mark it as printed
            word[0] = '\0';
        }
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <word_list_file> <grid_characters>\n", argv[0]);
        return 1;
    }

    if (strlen(argv[2]) != MAX_GRID_SIZE) {
        printf("Invalid grid. Grid should have 16 characters.\n");
        return 1;
    }

    int i, j, k = 0;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            grid[i][j] = argv[2][k++];
        }
    }

    findWordsInGrid(argv[1]);

    return 0;
}
