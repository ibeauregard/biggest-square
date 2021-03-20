#include "map.h"
#include "utils/readline.h"
#include "utils/_atoi.h"
#include "utils/_strlen.h"
#include "utils/min.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define FREE '.'

static void set_num_rows(Map* self);
static void identifyBiggestSquare(Map* self);
static void print(Map* self);
static void delete(Map* self);

Map* new_map_from_path(const char* map_path)
{
    Map* map = malloc(sizeof (Map));
    map->fd = open(map_path, O_RDONLY);
    map->biggest_square = new_biggest_square();
    set_num_rows(map);

    map->identifyBiggestSquare = &identifyBiggestSquare;
    map->print = &print;
    map->delete = &delete;
    return map;
}

static char* get_next_row(Map* self);

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

void identifyBiggestSquare(Map* self)
{
    char* row;
    // Handle the 0th row
    row = get_next_row(self);
    self->nums_cols = _strlen(row);
    uint sizes[self->nums_cols];
    sizes[0] = 0;
    for (uint j = 0; j < self->nums_cols; j++) {
        if (row[j] == FREE) {
            sizes[j + 1] = 1;
            self->biggest_square->setSize(self->biggest_square, 1);
            self->biggest_square->setTopLeft(self->biggest_square, 0, j);
        } else {
            sizes[j + 1] = 0;
        }
    }
    free(row);

    // Handle the rest of the rows (1, 2, ..., num_rows - 1)
    uint prev = 0;
    uint curr;
    for (uint i = 1; i < self->num_rows; i++) {
        row = get_next_row(self);
        for (uint j = 0; j < self->nums_cols; j++) {
            curr = sizes[j + 1];
            if (row[j] == FREE) {
                sizes[j + 1] = min((int[]){prev, sizes[j], sizes[j + 1]}, 3) + 1;
                if (sizes[j + 1] > self->biggest_square->size) {
                    self->biggest_square->setSize(self->biggest_square, sizes[j + 1]);
                    self->biggest_square->setTopLeft(self->biggest_square, i - self->biggest_square->size + 1, j - self->biggest_square->size + 1);
                }
            } else {
                sizes[j + 1] = 0;
            }
            prev = curr;
        }
        free(row);
    }
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
        row[j] = 'x';
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
