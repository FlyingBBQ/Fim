#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/move.h"
#include "../src/level.c"

static void
test_level_generate_solution(void **state)
{
        int solut[SOLUTION_SIZE];
        level_generate_solution(solut);

        for (int i = 0; i < SOLUTION_SIZE; ++i) {
                assert_in_range(solut[i], NORTH, WEST);
        }
}

const struct CMUnitTest test_level[] = {
        cmocka_unit_test(test_level_generate_solution),
};

int
run_test_level(void)
{
        return cmocka_run_group_tests(test_level, NULL, NULL);
}
