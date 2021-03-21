#include "bsq_finder.h"
#include "utils/min.h"
#include "utils/_strlen.h"
#include <stdlib.h>

#define FREE '.'

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

static void handle_row(BsqFinder* self, char* row);

BiggestSquare* run(BsqFinder* self)
{
    char* row = self->map->getNextRow(self->map);
    self->map->nums_cols = _strlen(row);
    self->sizes = malloc((self->map->nums_cols + 1) * sizeof (uint));
    for (uint i = 0; i < self->map->nums_cols + 1; i++) self->sizes[i] = 0;
    handle_row(self, row);
    free(row);

    while (self->row_index < self->map->num_rows) {
        row = self->map->getNextRow(self->map);
        handle_row(self, row);
        free(row);
    }
    return self->bsq;
}

void handle_row(BsqFinder* self, char* row)
{
    uint prev = 0, curr;
    for (uint j = 0; j < self->map->nums_cols; j++) {
        curr = self->sizes[j + 1];
        if (row[j] == FREE) {
            self->sizes[j + 1] = min((int[]){prev, self->sizes[j], self->sizes[j + 1]}, 3) + 1;
            if (self->sizes[j + 1] > self->bsq->size) {
                self->bsq->setSize(self->bsq, self->sizes[j + 1]);
                self->bsq->setBottomRight(self->bsq, self->row_index, j);
            }
        } else {
            self->sizes[j + 1] = 0;
        }
        prev = curr;
    }
    self->row_index++;
}

void delete(BsqFinder* self)
{
    free(self->sizes);
    free(self);
}
