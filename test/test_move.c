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
        assert_false(movePos(&fim, NORTH));

        fim.x++;
        assert_true(movePos(&fim, NORTH));
        assert_int_equal(fim.x, 0);

        fim.x = MAP_SIZE;
        assert_false(movePos(&fim, SOUTH));
}

static void
move_movePos_y(void **state)
{
        Pos fim;

        fim.y = 0;
        assert_false(movePos(&fim, WEST));

        fim.y = MAP_SIZE;
        assert_false(movePos(&fim, EAST));

        fim.y--;
        assert_true(movePos(&fim, EAST));
        assert_int_equal(fim.y, MAP_SIZE);

        fim.y = -1;
        assert_false(movePos(&fim, WEST));
}

const struct CMUnitTest test_move[2] = {
        cmocka_unit_test(move_movePos_x),
        cmocka_unit_test(move_movePos_y)
};
