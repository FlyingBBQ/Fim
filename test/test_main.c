#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

extern const struct CMUnitTest test_one[2];
extern const struct CMUnitTest test_two[2];

/* run the test functions */
int main(void) {
    int failed_tests = 0;

    failed_tests += cmocka_run_group_tests(test_one, NULL, NULL);
    failed_tests += cmocka_run_group_tests(test_two, NULL, NULL);

    return failed_tests;
}
