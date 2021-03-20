#ifndef BIGGEST_SQUARE_H
#define BIGGEST_SQUARE_H

#include "coordinates.h"

typedef unsigned int uint;

typedef struct s_biggest_square {
    uint size;
    Coordinates *top_left;

    void (*setSize)(struct s_biggest_square* self, uint size);
    void (*setBottomRight)(struct s_biggest_square* self, uint i, uint j);
    void (*delete)(struct s_biggest_square* self);
} BiggestSquare;

BiggestSquare* new_biggest_square();

#endif
