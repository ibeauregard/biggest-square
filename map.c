#include "map.h"
#include "bsq_finder.h"
#include "utils/readline.h"
#include "utils/_atoi.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define BSQ_MARKER 'x'

static void set_num_rows(Map* self);
static char* get_next_row(Map* self);
static void identify_biggest_square(Map* self);
static void print(Map* self);
static void delete(Map* self);

Map* new_map_from_path(const char* map_path)
{
    Map* self = malloc(sizeof (Map));
    self->fd = open(map_path, O_RDONLY);
    set_num_rows(self);

    self->getNextRow = &get_next_row;
    self->identifyBiggestSquare = &identify_biggest_square;
    self->print = &print;
    self->delete = &delete;
    return self;
}

void set_num_rows(Map* self)
{
    char* row = get_next_row(self);
    self->num_rows = _atoi(row);
    free(row);
}

char* get_next_row(Map* self)
{
    return readline(self->fd);
}

void identify_biggest_square(Map* self)
{
    BsqFinder* finder = new_bsq_finder(self);
    self->biggest_square = finder->run(finder);
    finder->delete(finder);
}

static void go_to_start(Map* self);
static void skip_one_line(Map* self);
static void print_regular_rows_between(Map* self, uint start, uint stop);
static void print_biggest_square_rows_between(Map* self, uint start, uint stop);

void print(Map* self)
{
    go_to_start(self);
    skip_one_line(self);
    uint start = 0, stop = self->biggest_square->top_left->i;
    print_regular_rows_between(self, start, stop);
    start = stop; stop = start + self->biggest_square->size;
    print_biggest_square_rows_between(self, start, stop);
    start = stop; stop = self->num_rows;
    print_regular_rows_between(self, start, stop);
}

void go_to_start(Map* self)
{
    lseek(self->fd, 0, SEEK_SET);
}

void skip_one_line(Map* self)
{
    get_next_row(self);
}

static void print_one_regular_row(Map* self);

void print_regular_rows_between(Map* self, uint start, uint stop)
{
    for (uint i = start; i < stop; i++) {
        print_one_regular_row(self);
    }
}

void print_one_regular_row(Map* self)
{
    char* row = get_next_row(self);
    printf("%s\n", row);
    free(row);
}

static void print_one_biggest_square_row(Map* self);

void print_biggest_square_rows_between(Map* self, uint start, uint stop)
{
    for (uint i = start; i < stop; i++) {
        print_one_biggest_square_row(self);
    }
}

void print_one_biggest_square_row(Map* self)
{
    char* row = get_next_row(self);
    for (uint j = self->biggest_square->top_left->j;
            j < self->biggest_square->top_left->j + self->biggest_square->size;
            j++) {
        row[j] = BSQ_MARKER;
    }
    printf("%s\n", row);
    free(row);
}

void delete(Map* self)
{
    self->biggest_square->delete(self->biggest_square);
    close(self->fd);
    free(self);
}
