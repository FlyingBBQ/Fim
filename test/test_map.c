#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/map.c"

static void
test_has_flag(void **state)
{
        Tiles tile = {0};

        tile.flags |= F_BORDER;
        assert_true(has_flag(&tile, F_BORDER));
        assert_false(has_flag(&tile, F_SOLUTION));

        tile.flags |= F_SOLUTION;
        assert_true(has_flag(&tile, F_SOLUTION));
        assert_true(has_flag(&tile, F_BORDER));
}

static void
test_set_flag(void **state)
{
        Tiles tile = {0};

        set_flag(&tile, F_BORDER);
        assert_int_equal(tile.flags, F_BORDER);

        set_flag(&tile, F_SOLUTION);
        assert_int_equal(tile.flags, (F_SOLUTION | F_BORDER));
}

static void
test_unset_flag(void **state)
{
        Tiles tile = {0};

        set_flag(&tile, (F_BORDER | F_SOLUTION));
        unset_flag(&tile, F_BORDER);
        assert_int_equal(tile.flags, F_SOLUTION);
}

static void
test_map_set_tile_type(void **state)
{
        Tiles tile = {0};

        map_set_tile_type(&tile);
        assert_int_equal(tile.type, TEX_bg);

        set_flag(&tile, F_FINISH);
        map_set_tile_type(&tile);
        assert_int_equal(tile.type, TEX_water);
}

static void
test_map_generate_xy(void **state)
{
        Tiles tiles[MAP_SIZE][MAP_SIZE] = {0};
        unsigned int const max_size = TILE_SIZE * (MAP_SIZE - 1);

        map_generate_xy(tiles);
        assert_int_equal(tiles[0][MAP_SIZE - 1].x, 0);
        assert_int_equal(tiles[0][MAP_SIZE - 1].y, max_size);
        assert_int_equal(tiles[MAP_SIZE - 1][0].x, max_size);
        assert_int_equal(tiles[MAP_SIZE - 1][0].y, 0);
}

static void
test_map_new(void **state)
{
        map_new();
}

static const struct CMUnitTest test_map[] = {
        cmocka_unit_test(test_has_flag),
        cmocka_unit_test(test_set_flag),
        cmocka_unit_test(test_unset_flag),
        cmocka_unit_test(test_map_set_tile_type),
        cmocka_unit_test(test_map_generate_xy),
        cmocka_unit_test(test_map_new),
};

int
run_test_map(void)
{
        return cmocka_run_group_tests(test_map, NULL, NULL);
}
