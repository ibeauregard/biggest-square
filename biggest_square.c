#include "biggest_square.h"
#include <stdlib.h>

static void delete(BiggestSquare* self);

BiggestSquare* new_biggest_square()
{
    BiggestSquare* bsq = malloc(sizeof (BiggestSquare));
    bsq->size = 0;
    bsq->top_left = new_coordinates();
    return bsq;
}

void delete(BiggestSquare* self)
{
    self->top_left->delete(self->top_left);
    free(self);
}

