#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/map.c"

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

        for (int i = 0; i < WEST; i++) {
                assert_in_range(opposite_direction(i), NORTH, WEST);
        }
}

static void
test_map_generate_xy(void ** state)
{
        size_t const map_size = 16;
        unsigned int const max_size = (unsigned int)(TILE_SIZE * (map_size - 1));

        Map map = {
                .map_size = map_size,
                .tiles = tiles_new(map_size),
        };

        map_generate_xy(&map);
        assert_int_equal(map.tiles[0][map_size - 1].x, 0);
        assert_int_equal(map.tiles[0][map_size - 1].y, max_size);
        assert_int_equal(map.tiles[map_size - 1][0].x, max_size);
        assert_int_equal(map.tiles[map_size - 1][0].y, 0);

        tiles_clean(map.tiles, map.map_size);
}

static const struct CMUnitTest test_map[] = {
        cmocka_unit_test(test_has_flag),
        cmocka_unit_test(test_set_flag),
        cmocka_unit_test(test_unset_flag),
        cmocka_unit_test(test_opposite_direction),
        cmocka_unit_test(test_map_set_tile_type),
        cmocka_unit_test(test_map_generate_xy),
};

int
run_test_map(void)
{
        return cmocka_run_group_tests(test_map, NULL, NULL);
}
