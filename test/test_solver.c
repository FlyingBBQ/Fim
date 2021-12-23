#include "solver.h"

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void
test_solver_step(void ** state)
{

}

static const struct CMUnitTest test_solver[] = {
        cmocka_unit_test(test_solver_step),
};

int
run_test_solver(void)
{
        return cmocka_run_group_tests(test_solver, NULL, NULL);
}
