#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

extern const struct CMUnitTest test_level[1];
extern const struct CMUnitTest test_move[9];

/* run the test functions */
int main(void) {
    int failed_tests = 0;

    failed_tests += cmocka_run_group_tests(test_level, NULL, NULL);
    failed_tests += cmocka_run_group_tests(test_move, NULL, NULL);

    return failed_tests;
}
