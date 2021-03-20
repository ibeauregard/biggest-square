#include "my_bsq.h"

#define DEFAULT_MAP_PATH "map.txt"

int main(int argc, char* argv[])
{
    return my_bsq(argc > 1 ? argv[1] : DEFAULT_MAP_PATH);
}
