#include "utils/readline.h"
#include "utils/_strlen.h"
#include "utils/_atoi.h"
#include "utils/min.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define DEFAULT_MAP_PATH "map.txt"
#define FREE '.'
#define OBSTACLE 'o'

typedef unsigned int uint;

int main(int argc, char* argv[])
{
    int map_fd;
    if (argc > 1) {
        map_fd = open(argv[1], O_RDONLY);
    } else {
        map_fd = open(DEFAULT_MAP_PATH, O_RDONLY);
    }
    char* row = readline(map_fd);
    uint num_rows = _atoi(row);
    free(row);

    // The biggest square data
    uint max_len = 0;
    uint top_left_i;
    uint top_left_j;

    // Handling the 0th row
    row = readline(map_fd);
    uint num_cols = _strlen(row);
    uint lengths[num_cols];
    lengths[0] = 0;
    for (uint j = 0; j < num_cols; j++) {
        if (row[j] == FREE) {
            lengths[j + 1] = 1;
            max_len = 1;
            top_left_i = 0;
            top_left_j = j;
        } else {
            lengths[j + 1] = 0;
        }
    }
    free(row);

    uint prev = 0;
    uint curr;
    // Handling the rest of the rows (1, 2, ..., num_rows - 1)
    for (uint i = 1; i < num_rows; i++) {
        row = readline(map_fd);
        for (uint j = 0; j < num_cols; j++) {
            curr = lengths[j + 1];
            if (row[j] == FREE) {
                lengths[j + 1] = min((int[]){prev, lengths[j], lengths[j + 1]}, 3) + 1;
                if (lengths[j + 1] > max_len) {
                    max_len = lengths[j + 1];
                    top_left_i = i - max_len + 1;
                    top_left_j = j - max_len + 1;
                }
            } else {
                lengths[j + 1] = 0;
            }
            prev = curr;
        }
        free(row);
    }

    // Go back to beginning of file, skip one line
    lseek(map_fd, 0, SEEK_SET);
    readline(map_fd);

    // Now let's print the map!
    for (uint i = 0; i < num_rows; i++) {
        row = readline(map_fd);
        for (uint j = 0; j < num_cols; j++) {
            if (top_left_i <= i && i < top_left_i + max_len
                && top_left_j <= j && j < top_left_j + max_len) {
                row[j] = 'x';
            }
        }
        printf("%s\n", row);
        free(row);
    }

    close(map_fd);
    return 0;
}
