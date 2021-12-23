#pragma once

#include "map.h"
#include <stddef.h>

typedef struct {
        unsigned int const * solution;
        size_t solution_size;
        Map ** maps;
        size_t nr_of_maps;
} Level;

Level * level_new(size_t solution_size, size_t nr_of_maps, size_t map_size);
void level_clean(Level * level);
bool level_is_finished(Level * level);
