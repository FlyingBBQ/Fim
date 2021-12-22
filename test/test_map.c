#include "map.h"

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void
test_has_flag(void ** state)
{
        Tiles tile = {0};

        tile.flags |= F_OBSTACLE;
        assert_true(has_flag(&tile, F_OBSTACLE));
        assert_false(has_flag(&tile, F_SOLUTION));

        tile.flags |= F_SOLUTION;
        assert_true(has_flag(&tile, F_SOLUTION));
        assert_true(has_flag(&tile, F_OBSTACLE));
}

static void
test_set_flag(void ** state)
{
        Tiles tile = {0};

        set_flag(&tile, F_OBSTACLE);
        assert_int_equal(tile.flags, F_OBSTACLE);

        set_flag(&tile, F_SOLUTION);
        assert_int_equal(tile.flags, (F_SOLUTION | F_OBSTACLE));
}

static void
test_unset_flag(void ** state)
{
        Tiles tile = {0};

        set_flag(&tile, (F_OBSTACLE | F_SOLUTION));
        unset_flag(&tile, F_OBSTACLE);
        assert_int_equal(tile.flags, F_SOLUTION);
}

static void
test_map_new_memory(void ** state)
{
        Pos init_pos = {0};
        Map * test_map = map_new(16, 0, init_pos);
        map_clean(test_map);
}

static void
test_map_set_tile_type(void ** state)
{
        Tiles tile = {0};

        map_set_tile_type(&tile);
        assert_int_equal(tile.type, TEX_bg);

        set_flag(&tile, F_FINISH);
        map_set_tile_type(&tile);
        assert_int_equal(tile.type, TEX_water);
}

static void
test_opposite_direction(void ** state)
{
        assert_int_equal(opposite_direction(NORTH), SOUTH);
        assert_int_equal(opposite_direction(SOUTH), NORTH);
        assert_int_equal(opposite_direction(EAST), WEST);
        assert_int_equal(opposite_direction(WEST), EAST);

        for (int dir = 0; dir < WEST; dir++) {
                assert_in_range(opposite_direction((Direction)dir), NORTH, WEST);
        }
}

static void
test_map_generate_xy(void ** state)
{
        Pos init_pos = {0};
        size_t const map_size = 16;
        unsigned int const max_size = (unsigned int)(TILE_SIZE * (map_size - 1));

        Map * test_map = map_new(map_size, 0, init_pos);

        assert_int_equal(test_map->tiles[0][map_size - 1].x, 0);
        assert_int_equal(test_map->tiles[0][map_size - 1].y, max_size);
        assert_int_equal(test_map->tiles[map_size - 1][0].x, max_size);
        assert_int_equal(test_map->tiles[map_size - 1][0].y, 0);

        map_clean(test_map);
}

static const struct CMUnitTest test_map[] = {
        cmocka_unit_test(test_has_flag),
        cmocka_unit_test(test_set_flag),
        cmocka_unit_test(test_unset_flag),
        cmocka_unit_test(test_map_new_memory),
        cmocka_unit_test(test_map_set_tile_type),
        cmocka_unit_test(test_opposite_direction),
        cmocka_unit_test(test_map_generate_xy),
};

int
run_test_map(void)
{
        return cmocka_run_group_tests(test_map, NULL, NULL);
}
