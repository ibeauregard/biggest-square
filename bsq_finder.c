#include "bsq_finder.h"
#include <stdlib.h>

static void delete(BsqFinder* self);

BsqFinder* new_bsq_finder(Map* map)
{
    BsqFinder* self = malloc(sizeof (BsqFinder));
    self->map = map;
    self->row_index = 0;

    self->delete = &delete;

    return self;
}

void delete(BsqFinder* self)
{
    free(self->sizes);
    free(self);
}
