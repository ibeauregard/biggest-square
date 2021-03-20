#ifndef MAP_H
#define MAP_H

#include "biggest_square.h"

typedef unsigned int uint;

typedef struct s_map {
    int fd;
    uint num_rows;
    uint nums_cols;
    BiggestSquare *biggest_square;

    void (*identifyBiggestSquare)(struct s_map* self);
    void (*print)(struct s_map* self);
    void (*delete)(struct s_map* self);
} Map;

Map* new_map_from_path(const char* map_path);

#endif
