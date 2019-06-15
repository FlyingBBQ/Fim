#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void test_1(void **state) {
    assert_int_equal(1, 2);
}

static void test_2(void **state) {
    assert_int_equal(4, 4);
}

const struct CMUnitTest test_one[2] = {
    cmocka_unit_test(test_1),
    cmocka_unit_test(test_2),
};
