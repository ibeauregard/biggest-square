#include "coordinates.h"
#include <stdlib.h>

static void delete(Coordinates* coordinates);

Coordinates* new_coordinates()
{
    Coordinates* coordinates = malloc(sizeof (Coordinates));
    coordinates->i = 0;
    coordinates->j = 0;
    coordinates->delete = &delete;
    return coordinates;
}

void delete(Coordinates* coordinates)
{
    free(coordinates);
}
