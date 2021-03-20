#include "utils/readline.h"
#include "utils/_atoi.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define DEFAULT_MAP_PATH "map.txt"

int main(int argc, char* argv[])
{
    int map_fd;
    if (argc > 1) {
        map_fd = open(argv[1], O_RDONLY);
    } else {
        map_fd = open(DEFAULT_MAP_PATH, O_RDONLY);
    }
    char* line = readline(map_fd);
    int n_rows = _atoi(line);
    free(line);

    for (int i = 0; i < n_rows; i++) {
        line = readline(map_fd);
        printf("%s\n", line);
        free(line);
    }

    close(map_fd);
    return 0;
}
