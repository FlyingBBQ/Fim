#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

extern int run_test_level(void);
extern int run_test_move(void);

int
main(void)
{
        int failed_tests = 0;

        /* run all the test functions */
        failed_tests += run_test_level();
        failed_tests += run_test_move();
        return failed_tests;
}
