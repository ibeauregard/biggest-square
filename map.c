#include "map.h"
#include "utils/readline.h"
#include "utils/_atoi.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static void set_num_rows(Map* self);
static void delete(Map* self);

Map* new_map_from_path(const char* map_path)
{
    Map* map = malloc(sizeof (Map));
    map->fd = open(map_path, O_RDONLY);
    map->biggest_square = new_biggest_square();
    set_num_rows(map);

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

void delete(Map* self)
{
    self->biggest_square->delete(self->biggest_square);
    close(self->fd);
    free(self);
}
