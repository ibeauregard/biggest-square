#include "map.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static void delete(Map* self);

Map* new_map_from_path(const char* map_path)
{
    Map* map = malloc(sizeof (Map));

    map->fd = open(map_path, O_RDONLY);
    map->delete = &delete;
    return map;
}

void delete(Map* self)
{
    close(self->fd);
    free(self);
}
