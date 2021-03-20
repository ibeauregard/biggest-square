#include "biggest_square.h"
#include <stdlib.h>

static void setSize(BiggestSquare * self, uint size);
static void setTopLeft(BiggestSquare * self, uint i, uint j);
static void delete(BiggestSquare* self);

BiggestSquare* new_biggest_square()
{
    BiggestSquare* bsq = malloc(sizeof (BiggestSquare));
    bsq->size = 0;
    bsq->setSize = &setSize;
    bsq->top_left = new_coordinates();
    bsq->setTopLeft = &setTopLeft;
    bsq->delete = &delete;
    return bsq;
}

void setSize(BiggestSquare * self, uint size)
{
    self->size = size;
}

void setTopLeft(BiggestSquare * self, uint i, uint j)
{
    self->top_left->i = i;
    self->top_left->j = j;
}

void delete(BiggestSquare* self)
{
    self->top_left->delete(self->top_left);
    free(self);
}
