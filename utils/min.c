#include "min.h"

uint min(const uint array[], size_t array_size)
{
    uint min_value = array[0];
    for (size_t i = 1; i < array_size; i++) {
        if (array[i] < min_value) {
            min_value = array[i];
        }
    }
    return min_value;
}
