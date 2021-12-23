#include "level.h"

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void
test_level_new_memory(void ** state)
{
        size_t const solution_size = 8;
        size_t const nr_of_maps = 4;
        size_t const map_size = 16;
        Level * test_level = NULL;

        level_clean(test_level);

        // Test various combinations for memory leaks.
        test_level = level_new(solution_size, nr_of_maps, map_size);
        level_clean(test_level);
        test_level = level_new(solution_size, nr_of_maps + nr_of_maps, map_size);
        level_clean(test_level);
        test_level = level_new(solution_size, nr_of_maps, map_size + map_size);
        level_clean(test_level);
        test_level = level_new(solution_size * 2, nr_of_maps * 4, map_size * 8);
        level_clean(test_level);
}

static void
test_level_is_finished(void ** state)
{
        Level * test_level = NULL;

        // Test finished map.
        test_level = level_new(8, 1, 32);
        test_level->maps[0]->finished = true;
        if (test_level != NULL) {
                assert_true(level_is_finished(test_level));
                level_clean(test_level);
        }

        // Test unfinished map.
        test_level = level_new(6, 2, 20);
        if (test_level != NULL) {
                assert_false(level_is_finished(test_level));
                level_clean(test_level);
        }

        // Test (almost) impossible map to solve. Expect it to fail.
        test_level = level_new(20, 4, 8);
        if (test_level != NULL) {
                level_clean(test_level);
        } else {
                assert_null(test_level);
        }

        // Test player quitting.
        test_level = level_new(4, 1, 10);
        player_quit_game();
        if (test_level != NULL) {
                assert_true(level_is_finished(test_level));
                level_clean(test_level);
        }
}

static const struct CMUnitTest test_level[] = {
        cmocka_unit_test(test_level_new_memory),
        cmocka_unit_test(test_level_is_finished),
};

int
run_test_level(void)
{
        return cmocka_run_group_tests(test_level, NULL, NULL);
}
