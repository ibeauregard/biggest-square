#ifndef COORDINATES_H
#define COORDINATES_H

typedef unsigned int uint;

typedef struct s_coordinates {
    uint i;
    uint j;
    void (*delete)(struct s_coordinates* self);
} Coordinates;

Coordinates* new_coordinates();

#endif
