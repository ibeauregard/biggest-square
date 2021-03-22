#include "my_bsq.h"
#include "map.h"
#include <stdlib.h>
#include <stdbool.h>

int my_bsq(const char* map_path)
{
    bool fatal_error = false;
    Map* map = new_map_from_path(map_path, &fatal_error);
    if (fatal_error) {
        return EXIT_FAILURE;
    }
    map->identifyBiggestSquare(map);
    map->print(map);
    map->delete(map);
    return EXIT_SUCCESS;
}
