#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/level.c"

/* Mock solver_run() for create_maps() */
bool
solver_run(Map * map, unsigned int const * solution,
           size_t const solution_size)
{
        return true;
}

static void
test_level_generate_solution(void ** state)
{
        size_t const solution_size = 8;
        unsigned int solution[solution_size];
        generate_solution((unsigned int *)&solution, solution_size);

        for (size_t i = 0; i < solution_size; ++i) {
                assert_in_range(solution[i], NORTH, WEST);
        }
}

static const struct CMUnitTest test_level[] = {
        cmocka_unit_test(test_level_generate_solution),
};

int
run_test_level(void)
{
        return cmocka_run_group_tests(test_level, NULL, NULL);
}
