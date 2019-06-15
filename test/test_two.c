#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void test_4(void **state) {
    assert_int_equal(1, 2);
}

static void test_5(void **state) {
    assert_int_equal(4, 4);
}

const struct CMUnitTest test_two[2] = {
    cmocka_unit_test(test_4),
    cmocka_unit_test(test_5),
};
