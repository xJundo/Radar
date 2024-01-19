/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include <sys/stat.h>
#include "my.h"
#include "csfml.h"

void show_text(game_info_t *game_info)
{
    show_time(game_info->info_window->my_window,
    game_info->clock_time, game_info->time,
    game_info->user_variables->speeduser);
    show_speed(game_info->speed_t,
    game_info->user_variables->speeduser, game_info->info_window->my_window);
    show_scale(game_info->info_window->my_window,
        game_info->scaletxt, game_info->user_variables->scale);
}

void display_main(game_info_t *game_info)
{
    sfRenderWindow_drawSprite(game_info->info_window->my_window,
    game_info->info_window->background_sprite, NULL);
    game_info->quadtree = init_quadtree((sfVector2f){0, 0},
        (sfVector2f){1920, 1080});
    show_tower(game_info);
    show_plane(game_info);
    show_text(game_info);
    check_recursively(game_info->quadtree, game_info);
    free_quadtree_recursively(game_info->quadtree);
    if (check_end(&game_info->file->planes_info))
        game_info->state = FREE_ALL;
}

void draw_everything(game_info_t *game_info)
{
    sfClock *clock = sfClock_create();

    while (sfRenderWindow_isOpen(game_info->info_window->my_window)) {
        if (game_info->state == FREE_ALL)
            break;
        sfRenderWindow_setFramerateLimit(game_info->info_window->my_window,
        game_info->info_window->f);
        game_info->info_window->delay =
        sfClock_restart(clock).microseconds / 1000000.0;
        game_info->mouse_pos =
        sfMouse_getPositionRenderWindow(game_info->info_window->my_window);
        analyse_events(game_info);
        display_main(game_info);
        sfRenderWindow_display(game_info->info_window->my_window);
        sfRenderWindow_clear(game_info->info_window->my_window, sfBlack);
    }
}
