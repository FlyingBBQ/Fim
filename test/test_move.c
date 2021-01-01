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

/* static implementations of tile functions */
static Tiles **
tiles_new(size_t const map_size)
{
        Tiles ** tiles = calloc(map_size, sizeof(Tiles *));
        if (tiles == NULL) {
                return NULL;
        }
        for (size_t i = 0; i < map_size; ++i) {
                tiles[i] = calloc(map_size, sizeof(Tiles));
                if (tiles[i] == NULL) {
                        free(tiles);
                        return NULL;
                }
        }
        return tiles;
}

static void
tiles_clean(Tiles ** tiles, size_t const map_size)
{
        for (size_t i = 0; i < map_size; ++i) {
                free(tiles[i]);
        }
        free(tiles);
}

static void
test_move_pos_x(void ** state)
{
        Map map = {0};
        map.map_size = 16;

        map.player.x = 0;
        assert_false(move_position(&map, WEST));

        map.player.x++;
        assert_true(move_position(&map, WEST));
        assert_int_equal(map.player.x, 0);

        map.player.x = 16;
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
        map.map_size = 16;

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
        map.map_size = 16;
        map.tiles = tiles_new(map.map_size);

        assert_int_equal(move_check_free_space(map, SOUTH), (map.map_size - 1));
        /* test if the player did not move */
        assert_int_equal(map.player.x, 0);
        assert_int_equal(map.player.y, 0);

        tiles_clean(map.tiles, map.map_size);
}

static void
test_move_check_free_space_flag(void ** state)
{
        Map map = {0};
        map.map_size = 16;
        map.tiles = tiles_new(map.map_size);
        Tiles * tile = &map.tiles[0][8];

        set_flag(tile, F_OBSTACLE);
        assert_int_equal(tile->flags, F_OBSTACLE);

        assert_int_equal(move_check_free_space(map, SOUTH), 7);

        tiles_clean(map.tiles, map.map_size);
}

static void
test_move_get_collision(void ** state)
{
        Map map = {0};
        map.map_size = 16;
        map.tiles = tiles_new(map.map_size);
        unsigned int collision = 0;

        /* place a border flag south of 0,0 */
        set_flag(&map.tiles[0][1], F_FINISH);
        collision = move_get_collision(map, SOUTH);
        assert_int_equal(collision, F_FINISH);

        /* move to border for player_game_over() */
        collision = move_get_collision(map, NORTH);

        tiles_clean(map.tiles, map.map_size);
}

static void
test_move_in_direction(void ** state)
{
        Map map = {0};
        map.map_size = 16;
        map.tiles = tiles_new(map.map_size);

        move_in_direction(&map, EAST);
        assert_int_equal(map.player.x, map.map_size - 1);

        assert_int_equal(map.player.y, 0);
        move_in_direction(&map, SOUTH);
        assert_int_not_equal(map.player.y, 0);

        tiles_clean(map.tiles, map.map_size);
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
