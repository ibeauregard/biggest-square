#include "map.h"
#include <stdlib.h>
#include <fcntl.h>

Map* new_map_from_path(const char* map_path)
{
    Map* map = malloc(sizeof (Map));
    map->fd = open(map_path, O_RDONLY);

    return map;
}
