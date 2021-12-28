#include "solver.h"

#include "map.h"
#include "move.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>

static void
test_solver_solvable(void ** state)
{
        // Create a simple solution with a very high probability to be solvable.
        unsigned int solution[] = {SOUTH, EAST};
        size_t const solution_size = sizeof(solution) / sizeof(unsigned int);
        unsigned int const map_size = 8;
        Pos init_pos = {0};

        Map * test_map = map_new(map_size, solution[0], init_pos);
        assert_non_null(test_map);

        solver_solve_map(test_map, solution, solution_size);
        bool solvable = solver_is_solvable(*test_map, solution, solution_size);
        assert_true(solvable);

        map_clean(test_map);
}

static void
test_solver_unsolvable(void ** state)
{
        // Use a solution that is unsolvable by the algorithm.
        unsigned int solution[] = {SOUTH, NORTH, SOUTH, NORTH};
        size_t const solution_size = sizeof(solution) / sizeof(unsigned int);
        unsigned int const map_size = 8;
        Pos init_pos = {0};

        Map * test_map = map_new(map_size, solution[0], init_pos);
        assert_non_null(test_map);

        solver_solve_map(test_map, solution, solution_size);
        bool solvable = solver_is_solvable(*test_map, solution, solution_size);
        assert_false(solvable);

        map_clean(test_map);
}

static const struct CMUnitTest test_solver[] = {
        cmocka_unit_test(test_solver_solvable),
        cmocka_unit_test(test_solver_unsolvable),
};

int
run_test_solver(void)
{
        return cmocka_run_group_tests(test_solver, NULL, NULL);
}
