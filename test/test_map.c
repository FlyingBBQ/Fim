#include "map.h"

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#define TEST_MAP_SIZE 16

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
        Map * test_map = NULL;

        // Test empty map.
        map_clean(test_map);

        // Test for memory leaks in different map sizes.
        test_map = map_new(27, 0, init_pos);
        map_clean(test_map);
        test_map = map_new(93, 1, init_pos);
        map_clean(test_map);
        test_map = map_new(235, 87, init_pos);
        map_clean(test_map);
        test_map = map_new(1234, 546, init_pos);
        map_clean(test_map);
}

static void
test_map_set_tile_type(void ** state)
{
        Tiles tile = {0};

        // Default type.
        map_set_tile_type(&tile);
        assert_int_equal(tile.type, TEX_bg);

        set_flag(&tile, F_FINISH);
        map_set_tile_type(&tile);
        assert_int_equal(tile.type, TEX_water);

        unset_flag(&tile, F_FINISH);
        set_flag(&tile, F_SOLUTION);
        map_set_tile_type(&tile);
        assert_int_equal(tile.type, TEX_bg);

        // F_OBSTACLE precedes F_SOLUTION
        set_flag(&tile, F_OBSTACLE);
        map_set_tile_type(&tile);
        assert_int_equal(tile.type, TEX_grass);
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

static int
setup_map(void ** state)
{
        Pos init_pos = {0};
        Map * test_map = map_new(TEST_MAP_SIZE, 0, init_pos);
        if (test_map == NULL) {
                return -1;
        }
        *state = test_map;
        return 0;
}

static int
teardown_map(void ** state)
{
        map_clean(*state);
        return 0;
}

static void
test_map_generate_xy(void ** state)
{
        Map * test_map = *state;
        unsigned int const max_size = (unsigned int)(TILE_SIZE * (TEST_MAP_SIZE - 1));

        assert_int_equal(test_map->tiles[0][TEST_MAP_SIZE - 1].x, 0);
        assert_int_equal(test_map->tiles[0][TEST_MAP_SIZE - 1].y, max_size);
        assert_int_equal(test_map->tiles[TEST_MAP_SIZE - 1][0].x, max_size);
        assert_int_equal(test_map->tiles[TEST_MAP_SIZE - 1][0].y, 0);
}

static void
test_map_generate_random_obstacle(void ** state)
{
        Map * test_map = *state;
        int nr_of_obstacles = TEST_MAP_SIZE + 8;

        map_generate_random_obstacles(test_map, nr_of_obstacles);
}

static const struct CMUnitTest test_map[] = {
        cmocka_unit_test(test_has_flag),
        cmocka_unit_test(test_set_flag),
        cmocka_unit_test(test_unset_flag),
        cmocka_unit_test(test_map_new_memory),
        cmocka_unit_test(test_map_set_tile_type),
        cmocka_unit_test(test_opposite_direction),
        cmocka_unit_test_setup_teardown(test_map_generate_xy, setup_map, teardown_map),
        cmocka_unit_test_setup_teardown(test_map_generate_random_obstacle, setup_map, teardown_map),
};

int
run_test_map(void)
{
        return cmocka_run_group_tests(test_map, NULL, NULL);
}
