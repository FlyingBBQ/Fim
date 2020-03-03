#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/map.c"

static void
test_has_flag(void **state)
{
        Tiles tile = {0};

        tile.flags |= F_BORDER;
        assert_true(has_flag(&tile, F_BORDER));
        assert_false(has_flag(&tile, F_SOLUTION));

        tile.flags |= F_SOLUTION;
        assert_true(has_flag(&tile, F_SOLUTION));
        assert_true(has_flag(&tile, F_BORDER));
}

static void
test_set_flag(void **state)
{
        Tiles tile = {0};

        set_flag(&tile, F_BORDER);
        assert_int_equal(tile.flags, F_BORDER);

        set_flag(&tile, F_SOLUTION);
        assert_int_equal(tile.flags, (F_SOLUTION | F_BORDER));
}

static void
test_unset_flag(void **state)
{
        Tiles tile = {0};

        set_flag(&tile, (F_BORDER | F_SOLUTION));
        unset_flag(&tile, F_BORDER);
        assert_int_equal(tile.flags, F_SOLUTION);
}


static const struct CMUnitTest test_map[] = {
        cmocka_unit_test(test_has_flag),
        cmocka_unit_test(test_set_flag),
        cmocka_unit_test(test_unset_flag),
};

int
run_test_map(void)
{
        return cmocka_run_group_tests(test_map, NULL, NULL);
}
