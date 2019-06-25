#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/move.c"

static void
move_movePos_x(void **state)
{
        Pos fim;

        fim.x = 0;
        assert_false(movePos(&fim, WEST));

        fim.x++;
        assert_true(movePos(&fim, WEST));
        assert_int_equal(fim.x, 0);

        fim.x = MAP_SIZE;
        assert_false(movePos(&fim, EAST));
        assert_true(movePos(&fim, WEST));
        assert_true(movePos(&fim, NORTH));

        /* default case */
        assert_false(movePos(&fim, 42));
}

static void
move_movePos_y(void **state)
{
        Pos fim;

        fim.y = 0;
        assert_false(movePos(&fim, NORTH));

        fim.y = 15;
        assert_false(movePos(&fim, SOUTH));

        fim.y--;
        assert_true(movePos(&fim, SOUTH));
        assert_int_equal(fim.y, 15);

        fim.y = -1;
        assert_false(movePos(&fim, NORTH));
}

static void
move_hasFlag(void **state)
{
        Tiles tile = {0};

        tile.flags |= F_BORDER;

        assert_true(hasFlag(&tile, F_BORDER));
        assert_false(hasFlag(&tile, F_SOLUTION));

        tile.flags |= F_SOLUTION;
        assert_true(hasFlag(&tile, F_SOLUTION));
        assert_true(hasFlag(&tile, F_BORDER));
}

static void
move_setFlag(void **state)
{
        Tiles tile = {0};

        setFlag(&tile, F_BORDER);
        assert_int_equal(tile.flags, F_BORDER);

        setFlag(&tile, F_SOLUTION);
        assert_int_equal(tile.flags, (F_SOLUTION | F_BORDER));
}

static void
move_unsetFlag(void **state)
{
        Tiles tile = {0};
        setFlag(&tile, (F_BORDER | F_SOLUTION));

        unsetFlag(&tile, F_BORDER);
        assert_int_equal(tile.flags, F_SOLUTION);
}

static void
move_freeSpace_range(void **state)
{
        Map map = {0};
        assert_in_range(freeSpace(map, NORTH), 0, MAP_SIZE-1);
        assert_in_range(freeSpace(map, EAST), 0, MAP_SIZE-1);
        assert_in_range(freeSpace(map, SOUTH), 0, MAP_SIZE-1);
        assert_in_range(freeSpace(map, WEST), 0, MAP_SIZE-1);
}

static void
move_freeSpace_steps(void **state)
{
        static Map map = {0};
        assert_int_equal(freeSpace(map, SOUTH), (MAP_SIZE-1));

        assert_int_equal(map.fim.x, 0);
        assert_int_equal(map.fim.y, 0);
}
const struct CMUnitTest test_move[8] = {
        cmocka_unit_test(move_movePos_x),
        cmocka_unit_test(move_movePos_y),
        cmocka_unit_test(move_hasFlag),
        cmocka_unit_test(move_setFlag),
        cmocka_unit_test(move_unsetFlag),
        cmocka_unit_test(move_freeSpace_range),
        cmocka_unit_test(move_freeSpace_steps),
};
