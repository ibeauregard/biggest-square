#include "bsq_finder.h"
#include <stdlib.h>

BsqFinder* new_bsq_finder(Map* map)
{
    BsqFinder* self = malloc(sizeof (BsqFinder));
    self->map = map;
    self->row_index = 0;

    return self;
}
