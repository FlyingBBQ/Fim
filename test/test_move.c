#include "move.h"

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#define TEST_MAP_SIZE 16

static void
test_move_pos_x(void ** state)
{
        Map map = {0};
        map.map_size = TEST_MAP_SIZE;

        map.player.x = 0;
        assert_false(move_position(&map, WEST));

        map.player.x++;
        assert_true(move_position(&map, WEST));
        assert_int_equal(map.player.x, 0);

        map.player.x = (int)TEST_MAP_SIZE;
        assert_false(move_position(&map, EAST));
        assert_true(move_position(&map, WEST));
        assert_true(move_position(&map, SOUTH));

        /* default case */
        assert_false(move_position(&map, 42));
}

static void
test_move_pos_y(void ** state)
{
        Map map = {0};
        map.map_size = TEST_MAP_SIZE;

        map.player.y = 0;
        assert_false(move_position(&map, NORTH));

        map.player.y = 15;
        assert_false(move_position(&map, SOUTH));

        assert_true(move_position(&map, NORTH));
        assert_int_equal(map.player.y, 14);

        assert_true(move_position(&map, SOUTH));
        assert_int_equal(map.player.y, 15);

        map.player.y = -1;
        assert_false(move_position(&map, NORTH));
}

static int
setup_map(void ** state)
{
        Pos init_pos = {0};
        Map * test_map = map_new(TEST_MAP_SIZE, 0, init_pos);
        if (test_map == NULL) {
                return -1;
        }
        *state = test_map;
        return 0;
}

static int
teardown_map(void ** state)
{
        map_clean(*state);
        return 0;
}

static void
test_move_check_free_space_range(void ** state)
{
        Map * test_map = *state;

        assert_in_range(move_check_free_space(*test_map, NORTH), 0, TEST_MAP_SIZE - 1);
        assert_in_range(move_check_free_space(*test_map, EAST), 0, TEST_MAP_SIZE - 1);
        assert_in_range(move_check_free_space(*test_map, SOUTH), 0, TEST_MAP_SIZE - 1);
        assert_in_range(move_check_free_space(*test_map, WEST), 0, TEST_MAP_SIZE - 1);
}

static void
test_move_check_free_space_steps(void ** state)
{
        Map * test_map = *state;
        size_t map_size = test_map->map_size - 1;
        int steps = 6;

        test_map->player.x = steps;
        test_map->player.y = 0;

        assert_int_equal(move_check_free_space(*test_map, SOUTH), map_size);
        assert_int_equal(move_check_free_space(*test_map, EAST),
                         map_size - (size_t)steps);
        // Test if the player did not move.
        assert_int_equal(test_map->player.x, steps);
        assert_int_equal(test_map->player.y, 0);
}

static void
test_move_check_free_space_flag(void ** state)
{
        Map * test_map = *state;
        Tiles * tile = &test_map->tiles[0][8];
        test_map->player.x = 0;

        set_flag(tile, F_OBSTACLE);
        assert_int_equal(tile->flags, F_OBSTACLE);
        assert_int_equal(move_check_free_space(*test_map, SOUTH), 7);
}

static void
test_move_get_collision(void ** state)
{
        Map * test_map = *state;
        unsigned int collision = 0;
        test_map->player.x = 0;

        // Place a border flag south of 0,0.
        set_flag(&test_map->tiles[0][1], F_FINISH);
        collision = move_get_collision(*test_map, SOUTH);
        assert_int_equal(collision, F_FINISH);

        // Move to border for player_game_over().
        collision = move_get_collision(*test_map, NORTH);
        assert_int_equal(collision, F_BORDER);
}

static void
test_move_in_direction(void ** state)
{
        Map * test_map = *state;

        // Position the player besides the border.
        test_map->player.x = 1;
        test_map->player.y = 1;

        move_in_direction(test_map, EAST);
        assert_int_equal(test_map->player.x, test_map->map_size - 1);
        // Player did not move on y.
        assert_int_equal(test_map->player.y, 1);
        // Expect to hit border.
        move_in_direction(test_map, SOUTH);
        assert_int_not_equal(test_map->player.y, 0);
}

static const struct CMUnitTest test_move[] = {
        cmocka_unit_test(test_move_pos_x),
        cmocka_unit_test(test_move_pos_y),
        cmocka_unit_test_setup_teardown(test_move_check_free_space_range, setup_map, teardown_map),
        cmocka_unit_test_setup_teardown(test_move_check_free_space_steps, setup_map, teardown_map),
        cmocka_unit_test_setup_teardown(test_move_check_free_space_flag, setup_map, teardown_map),
        cmocka_unit_test_setup_teardown(test_move_get_collision, setup_map, teardown_map),
        cmocka_unit_test_setup_teardown(test_move_in_direction, setup_map, teardown_map),
};

int
run_test_move(void)
{
        return cmocka_run_group_tests(test_move, NULL, NULL);
}
