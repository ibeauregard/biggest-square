#include "my_bsq.h"
#include "utils/readline.h"
#include "utils/_strlen.h"
#include "utils/_atoi.h"
#include "utils/min.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define FREE '.'

typedef unsigned int uint;

int my_bsq(const char* map_path)
{
    // The biggest square data
    uint max_len = 0;
    uint top_left_i;
    uint top_left_j;

    // Get the file descriptor
    int map_fd = open(map_path, O_RDONLY);

    // Get the number of rows
    char* row = readline(map_fd);
    uint num_rows = _atoi(row);
    free(row);

    // Handle the 0th row
    row = readline(map_fd);
    uint num_cols = _strlen(row);
    uint sizes[num_cols];
    sizes[0] = 0;
    for (uint j = 0; j < num_cols; j++) {
        if (row[j] == FREE) {
            sizes[j + 1] = 1;
            max_len = 1;
            top_left_i = 0;
            top_left_j = j;
        } else {
            sizes[j + 1] = 0;
        }
    }
    free(row);

    // Handle the rest of the rows (1, 2, ..., num_rows - 1)
    uint prev = 0;
    uint curr;
    for (uint i = 1; i < num_rows; i++) {
        row = readline(map_fd);
        for (uint j = 0; j < num_cols; j++) {
            curr = sizes[j + 1];
            if (row[j] == FREE) {
                sizes[j + 1] = min((int[]){prev, sizes[j], sizes[j + 1]}, 3) + 1;
                if (sizes[j + 1] > max_len) {
                    max_len = sizes[j + 1];
                    top_left_i = i - max_len + 1;
                    top_left_j = j - max_len + 1;
                }
            } else {
                sizes[j + 1] = 0;
            }
            prev = curr;
        }
        free(row);
    }

    // Now let's print the map!

    // First, go back to beginning of file
    lseek(map_fd, 0, SEEK_SET);
    // Skip one line
    readline(map_fd);
    if (max_len > 0) {
        uint i;
        for (i = 0; i < top_left_i; i++) {
            row = readline(map_fd);
            printf("%s\n", row);
            free(row);
        }
        for (; i < top_left_i + max_len; i++) {
            row = readline(map_fd);
            for (uint j = top_left_j; j < top_left_j + max_len; j++) {
                row[j] = 'x';
            }
            printf("%s\n", row);
            free(row);
        }
        for (; i < num_rows; i++) {
            row = readline(map_fd);
            printf("%s\n", row);
            free(row);
        }
    } else {
        for (uint i = 0; i < num_rows; i++) {
            row = readline(map_fd);
            printf("%s\n", row);
            free(row);
        }
    }


    close(map_fd);
    return EXIT_SUCCESS;
}
