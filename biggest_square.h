#ifndef BIGGEST_SQUARE_H
#define BIGGEST_SQUARE_H

#include "coordinates.h"

typedef unsigned int uint;

typedef struct s_biggest_square {
    uint size;
    Coordinates *top_left;
} BiggestSquare;

#endif
