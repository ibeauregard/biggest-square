#ifndef MAP_H
#define MAP_H

typedef unsigned int uint;

typedef struct s_map {
    int fd;
    uint num_rows;
    uint nums_cols;

    void (*identifyBiggestSquare)(struct s_map* self);
    void (*print)(struct s_map* self);
    void (*delete)(struct s_map* self);
} Map;

Map* new_map_from_path(const char* map_path);

#endif
