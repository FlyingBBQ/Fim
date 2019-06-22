#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/map.c"

static void 
map_genSolution(void **state) 
{
        int solut[SOLUTION_SIZE];
        genSolution(solut);

        for (int i = 0; i < SOLUTION_SIZE; i++)
                assert_in_range(solut[i], NORTH, WEST);
}

static void
map_oppositeWay(void **state)
{
        assert_int_equal(oppositeWay(NORTH), SOUTH);
        assert_int_equal(oppositeWay(SOUTH), NORTH);
        assert_int_equal(oppositeWay(EAST), WEST);
        assert_int_equal(oppositeWay(WEST), EAST);

        for (int i = 0; i < WEST; i++)
                assert_in_range(oppositeWay(i), NORTH, WEST);
}

const struct CMUnitTest test_map[2] = {
        cmocka_unit_test(map_genSolution),
        cmocka_unit_test(map_oppositeWay),
};
