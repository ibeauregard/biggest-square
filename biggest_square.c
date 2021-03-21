#include "biggest_square.h"
#include <stdlib.h>

static void set_size(BiggestSquare* self, uint size);
static void set_bottom_right(BiggestSquare* self, uint i, uint j);
static void delete(BiggestSquare* self);

BiggestSquare* new_biggest_square()
{
    BiggestSquare* bsq = malloc(sizeof (BiggestSquare));
    bsq->size = 0;
    bsq->setSize = &set_size;
    bsq->top_left = new_coordinates();
    bsq->setBottomRight = &set_bottom_right;
    bsq->delete = &delete;
    return bsq;
}

void set_size(BiggestSquare* self, uint size)
{
    self->size = size;
}

void set_bottom_right(BiggestSquare* self, uint i, uint j)
{
    self->top_left->i = i - self->size + 1;
    self->top_left->j = j - self->size + 1;
}

void delete(BiggestSquare* self)
{
    self->top_left->delete(self->top_left);
    free(self);
}
