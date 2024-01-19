/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include <sys/stat.h>
#include "my.h"
#include "csfml.h"

void init_info_window(game_info_t *game_info)
{
    game_info->info_window = malloc(sizeof(window_info_t));
    game_info->info_window->video_mode = (sfVideoMode) {1920, 1080, 32};
    game_info->info_window->my_window =
    sfRenderWindow_create(game_info->info_window->video_mode,
    "my_window", sfClose, NULL);
    sfRenderWindow_setPosition(game_info->info_window->my_window,
    (sfVector2i) {0, 0});
    game_info->info_window->f = 60;
    sfRenderWindow_setFramerateLimit(game_info->info_window->my_window,
    game_info->info_window->f);
    game_info->info_window->background_texture =
    sfTexture_createFromFile("./assets.png", NULL);
    game_info->info_window->background_sprite = sfSprite_create();
    sfSprite_setTexture(game_info->info_window->background_sprite,
    game_info->info_window->background_texture, false);
    game_info->info_window->delay = 0;
    game_info->info_window->clock = sfClock_create();
}

void init_window(game_info_t *game_info)
{
    init_info_window(game_info);
    game_info->state = MAIN;
}

int init_file(game_info_t *game_info)
{
    game_info->file->plane = init_plane(game_info);
    game_info->file->tower = init_tower(game_info);
    return 0;
}

int init_variables(game_info_t *game_info)
{
    game_info->user_variables = malloc(sizeof(user_variables_t));
    game_info->user_variables->hitbox = 1;
    game_info->user_variables->sprite = 1;
    game_info->user_variables->move = 1;
    game_info->user_variables->quad_treeview = 0;
    game_info->user_variables->speeduser = 1;
    game_info->quad = malloc(sizeof(shape_t));
    game_info->quad->rectangle = init_rectangle((sfVector2f){0, 0},
        (sfVector2f){0, 0}, sfGreen, 1);
    game_info->quad->circle = NULL;
    game_info->user_variables->scale = (sfVector2f){1.0, 1.0};
    return 0;
}

int init_game_info(game_info_t *game_info)
{
    init_window(game_info);
    init_file(game_info);
    init_variables(game_info);
    init_time(game_info);
    init_speedtext(game_info);
    init_altitudetxt(game_info);
    init_scaletxt(game_info);
    return 0;
}
