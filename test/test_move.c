#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/move.c"

static void
move_move_pos_x(void **state)
{
        Pos fim;

        fim.x = 0;
        assert_false(move_pos(&fim, WEST));

        fim.x++;
        assert_true(move_pos(&fim, WEST));
        assert_int_equal(fim.x, 0);

        fim.x = MAP_SIZE;
        assert_false(move_pos(&fim, EAST));
        assert_true(move_pos(&fim, WEST));
        assert_true(move_pos(&fim, NORTH));

        /* default case */
        assert_false(move_pos(&fim, 42));
}

static void
move_move_pos_y(void **state)
{
        Pos fim;

        fim.y = 0;
        assert_false(move_pos(&fim, NORTH));

        fim.y = 15;
        assert_false(move_pos(&fim, SOUTH));

        fim.y--;
        assert_true(move_pos(&fim, SOUTH));
        assert_int_equal(fim.y, 15);

        fim.y = -1;
        assert_false(move_pos(&fim, NORTH));
}

static void
move_has_flag(void **state)
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
move_set_flag(void **state)
{
        Tiles tile = {0};

        set_flag(&tile, F_BORDER);
        assert_int_equal(tile.flags, F_BORDER);

        set_flag(&tile, F_SOLUTION);
        assert_int_equal(tile.flags, (F_SOLUTION | F_BORDER));
}

static void
move_unset_flag(void **state)
{
        Tiles tile = {0};
        set_flag(&tile, (F_BORDER | F_SOLUTION));

        unset_flag(&tile, F_BORDER);
        assert_int_equal(tile.flags, F_SOLUTION);
}

static void
move_free_space_range(void **state)
{
        Map map = {0};
        assert_in_range(free_space(map, NORTH), 0, MAP_SIZE-1);
        assert_in_range(free_space(map, EAST), 0, MAP_SIZE-1);
        assert_in_range(free_space(map, SOUTH), 0, MAP_SIZE-1);
        assert_in_range(free_space(map, WEST), 0, MAP_SIZE-1);
}

static void
move_free_space_steps(void **state)
{
        static Map map = {0};
        assert_int_equal(free_space(map, SOUTH), (MAP_SIZE-1));

        assert_int_equal(map.fim.x, 0);
        assert_int_equal(map.fim.y, 0);
}

const struct CMUnitTest test_move[8] = {
        cmocka_unit_test(move_move_pos_x),
        cmocka_unit_test(move_move_pos_y),
        cmocka_unit_test(move_has_flag),
        cmocka_unit_test(move_set_flag),
        cmocka_unit_test(move_unset_flag),
        cmocka_unit_test(move_free_space_range),
        cmocka_unit_test(move_free_space_steps),
};
