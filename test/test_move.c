#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/move.c"

/* mock player_gamer_over() for move_get_collision() */
void
player_game_over(void)
{
        return;
}

static void
test_move_pos_x(void ** state)
{
        Pos player = {0};

        player.x = 0;
        assert_false(move_position(&player, WEST));

        player.x++;
        assert_true(move_position(&player, WEST));
        assert_int_equal(player.x, 0);

        player.x = MAP_SIZE;
        assert_false(move_position(&player, EAST));
        assert_true(move_position(&player, WEST));
        assert_true(move_position(&player, SOUTH));

        /* default case */
        assert_false(move_position(&player, 42));
}

static void
test_move_pos_y(void ** state)
{
        Pos player = {0};

        player.y = 0;
        assert_false(move_position(&player, NORTH));

        player.y = 15;
        assert_false(move_position(&player, SOUTH));

        assert_true(move_position(&player, NORTH));
        assert_int_equal(player.y, 14);

        assert_true(move_position(&player, SOUTH));
        assert_int_equal(player.y, 15);

        player.y = -1;
        assert_false(move_position(&player, NORTH));
}

static void
test_move_check_free_space_range(void ** state)
{
        Map map = {0};

        assert_in_range(move_check_free_space(map, NORTH), 0, MAP_SIZE - 1);
        assert_in_range(move_check_free_space(map, EAST), 0, MAP_SIZE - 1);
        assert_in_range(move_check_free_space(map, SOUTH), 0, MAP_SIZE - 1);
        assert_in_range(move_check_free_space(map, WEST), 0, MAP_SIZE - 1);
}

static void
test_move_check_free_space_steps(void ** state)
{
        Map map = {0};

        assert_int_equal(move_check_free_space(map, SOUTH), (MAP_SIZE - 1));
        /* test if the player did not move */
        assert_int_equal(map.player.x, 0);
        assert_int_equal(map.player.y, 0);
}

static void
test_move_check_free_space_flag(void ** state)
{
        Map map = {0};
        Tiles * tile = &map.tiles[0][8];

        set_flag(tile, F_BORDER);
        assert_int_equal(tile->flags, F_BORDER);

        assert_int_equal(move_check_free_space(map, SOUTH), 7);
}

static void
test_move_get_collision(void ** state)
{
        Map map = {0};
        unsigned int collision = 0;

        /* place a border flag south of 0,0 */
        set_flag(&map.tiles[0][1], F_FINISH);
        collision = move_get_collision(map, SOUTH);
        assert_int_equal(collision, F_FINISH);

        /* move to border for player_game_over() */
        collision = move_get_collision(map, NORTH);
}

static void
test_move_in_direction(void ** state)
{
        Map map = {0};

        move_in_direction(&map, EAST);
        assert_int_equal(map.player.x, MAP_SIZE - 1);

        assert_int_equal(map.player.y, 0);
        move_in_direction(&map, SOUTH);
        assert_int_not_equal(map.player.y, 0);
}

static const struct CMUnitTest test_move[] = {
        cmocka_unit_test(test_move_pos_x),
        cmocka_unit_test(test_move_pos_y),
        cmocka_unit_test(test_move_check_free_space_range),
        cmocka_unit_test(test_move_check_free_space_steps),
        cmocka_unit_test(test_move_check_free_space_flag),
        cmocka_unit_test(test_move_get_collision),
        cmocka_unit_test(test_move_in_direction),
};

int
run_test_move(void)
{
        return cmocka_run_group_tests(test_move, NULL, NULL);
}
