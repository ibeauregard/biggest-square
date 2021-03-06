#ifndef BSQ_FINDER_H
#define BSQ_FINDER_H

#include "map.h"

typedef unsigned int uint;

typedef struct s_bsq_finder {
    Map* map;
    uint* size_tracker;
    uint row_index;

    void (*run)(struct s_bsq_finder* self);
    void (*delete)(struct s_bsq_finder* self);
} BsqFinder;

BsqFinder* new_bsq_finder(Map* map);

#endif
