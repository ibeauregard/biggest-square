#include "bsq_finder.h"
#include <stdlib.h>

static BiggestSquare* run(BsqFinder* self);
static void delete(BsqFinder* self);

BsqFinder* new_bsq_finder(Map* map)
{
    BsqFinder* self = malloc(sizeof (BsqFinder));
    self->map = map;
    self->row_index = 0;
    self->bsq = new_biggest_square();

    self->run = &run;
    self->delete = &delete;

    return self;
}

BiggestSquare* run(BsqFinder* self)
{




    return self->bsq;
}

void delete(BsqFinder* self)
{
    free(self->sizes);
    free(self);
}
