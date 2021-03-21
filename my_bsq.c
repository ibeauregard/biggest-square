#include "my_bsq.h"
#include "map.h"
#include <stdlib.h>

int my_bsq(const char* map_path)
{
    Map* map = new_map_from_path(map_path);
    map->identifyBiggestSquare(map);
    map->print(map);
    map->delete(map);
    return EXIT_SUCCESS;
}
