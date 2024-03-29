#include "bsq_finder.h"
#include "utils/min.h"
#include "utils/_strlen.h"
#include <stdlib.h>

#define FREE '.'

static void run(BsqFinder* self);
static void delete(BsqFinder* self);

BsqFinder* new_bsq_finder(Map* map)
{
    BsqFinder* self = malloc(sizeof (BsqFinder));
    self->map = map;
    self->row_index = 0;

    self->run = &run;
    self->delete = &delete;
    return self;
}

static void initialize_size_tracker(BsqFinder* self);
static void handle_row(BsqFinder* self, const char* row);

void run(BsqFinder* self)
{
    char* row = self->map->getNextRow(self->map);
    self->map->nums_cols = _strlen(row);
    initialize_size_tracker(self);
    handle_row(self, row);
    free(row);
    self->row_index++;

    for (; self->row_index < self->map->num_rows; self->row_index++) {
        row = self->map->getNextRow(self->map);
        handle_row(self, row);
        free(row);
    }
}

void initialize_size_tracker(BsqFinder* self)
{
    self->size_tracker = malloc((self->map->nums_cols + 1) * sizeof (uint));
    for (uint i = 0; i < self->map->nums_cols + 1; i++) {
        self->size_tracker[i] = 0;
    }
}

void handle_row(BsqFinder* self, const char* row)
{
    uint prev = 0, curr;
    for (uint j = 0; j < self->map->nums_cols; j++) {
        curr = self->size_tracker[j + 1];
        if (row[j] == FREE) {
            self->size_tracker[j + 1] = min((uint[]) {prev, self->size_tracker[j], self->size_tracker[j + 1]}, 3) + 1;
            if (self->size_tracker[j + 1] > self->map->bsq->size) {
                self->map->bsq->setSize(self->map->bsq, self->size_tracker[j + 1]);
                self->map->bsq->setBottomRight(self->map->bsq, self->row_index, j);
            }
        } else {
            self->size_tracker[j + 1] = 0;
        }
        prev = curr;
    }
}

void delete(BsqFinder* self)
{
    free(self->size_tracker);
    free(self);
}
