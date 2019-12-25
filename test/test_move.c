#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/move.c"

static void
test_move_opposite(void **state)
{
        assert_int_equal(move_opposite(NORTH), SOUTH);
        assert_int_equal(move_opposite(SOUTH), NORTH);
        assert_int_equal(move_opposite(EAST), WEST);
        assert_int_equal(move_opposite(WEST), EAST);

        for (int i = 0; i < WEST; i++) {
                assert_in_range(move_opposite(i), NORTH, WEST);
        }
}

static void
test_move_pos_x(void **state)
{
        Pos fim;

        fim.x = 0;
        assert_false(move_position(&fim, WEST));

        fim.x++;
        assert_true(move_position(&fim, WEST));
        assert_int_equal(fim.x, 0);

        fim.x = MAP_SIZE;
        assert_false(move_position(&fim, EAST));
        assert_true(move_position(&fim, WEST));
        assert_true(move_position(&fim, NORTH));

        /* default case */
        assert_false(move_position(&fim, 42));
}

static void
test_move_pos_y(void **state)
{
        Pos fim;

        fim.y = 0;
        assert_false(move_position(&fim, NORTH));

        fim.y = 15;
        assert_false(move_position(&fim, SOUTH));

        fim.y--;
        assert_true(move_position(&fim, SOUTH));
        assert_int_equal(fim.y, 15);

        fim.y = -1;
        assert_false(move_position(&fim, NORTH));
}

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
test_move_check_free_space_range(void **state)
{
        Map map = {0};

        assert_in_range(move_check_free_space(map, NORTH), 0, MAP_SIZE-1);
        assert_in_range(move_check_free_space(map, EAST), 0, MAP_SIZE-1);
        assert_in_range(move_check_free_space(map, SOUTH), 0, MAP_SIZE-1);
        assert_in_range(move_check_free_space(map, WEST), 0, MAP_SIZE-1);
}

static void
test_move_check_free_space_steps(void **state)
{
        Map map = {0};

        assert_int_equal(move_check_free_space(map, SOUTH), (MAP_SIZE-1));
        /* test if the player did not move */
        assert_int_equal(map.fim.x, 0);
        assert_int_equal(map.fim.y, 0);
}

static void
test_move_check_free_space_flag(void **state)
{
        Map map = {0};
        Tiles *tile = &map.tiles[0][8];

        set_flag(tile, F_BORDER);
        assert_int_equal(tile->flags, F_BORDER);

        assert_int_equal(move_check_free_space(map, SOUTH), 7);
}

const struct CMUnitTest test_move[] = {
        cmocka_unit_test(test_move_opposite),
        cmocka_unit_test(test_move_pos_x),
        cmocka_unit_test(test_move_pos_y),
        cmocka_unit_test(test_has_flag),
        cmocka_unit_test(test_set_flag),
        cmocka_unit_test(test_unset_flag),
        cmocka_unit_test(test_move_check_free_space_range),
        cmocka_unit_test(test_move_check_free_space_steps),
        cmocka_unit_test(test_move_check_free_space_flag),
};

int
run_test_move(void)
{
        return cmocka_run_group_tests(test_move, NULL, NULL);
}
