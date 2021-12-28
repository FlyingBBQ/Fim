#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

extern int run_test_move(void);
extern int run_test_map(void);
extern int run_test_level(void);
extern int run_test_solver(void);

int
main(void)
{
        int failed_tests = 0;

        // Run all the test functions.
        failed_tests += run_test_move();
        failed_tests += run_test_map();
        failed_tests += run_test_level();
        failed_tests += run_test_solver();
        return failed_tests;
}
