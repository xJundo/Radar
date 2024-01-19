/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "mylist.h"
#include "my.h"
#include "csfml.h"

void manage_touch_2(game_info_t *game_info)
{
    if (game_info->info_window->event.key.code == sfKeyUp
        && game_info->user_variables->scale.x < 4.0) {
        game_info->user_variables->scale.x *= 2.0;
        game_info->user_variables->scale.y *= 2.0;
    }
    if (game_info->info_window->event.key.code == sfKeyDown
        && game_info->user_variables->scale.x > 0.50) {
        game_info->user_variables->scale.x /= 2.0;
        game_info->user_variables->scale.y /= 2.0;
    }
}

void manage_touch(game_info_t *game_info)
{
    if (game_info->info_window->event.key.code == sfKeyL)
        game_info->user_variables->hitbox = !game_info->user_variables->hitbox;
    if (game_info->info_window->event.key.code == sfKeyS)
        game_info->user_variables->sprite = !game_info->user_variables->sprite;
    if (game_info->info_window->event.key.code == sfKeyQ)
        game_info->user_variables->quad_treeview =
        !game_info->user_variables->quad_treeview;
    if (game_info->info_window->event.key.code == sfKeyRight
        && game_info->user_variables->speeduser < 128)
        game_info->user_variables->speeduser *= 2;
    if (game_info->info_window->event.key.code == sfKeyLeft
        && game_info->user_variables->speeduser > 1)
        game_info->user_variables->speeduser /= 2;
    if (game_info->info_window->event.key.code == sfKeySpace)
        game_info->user_variables->move = !game_info->user_variables->move;
    manage_touch_2(game_info);
}

void close_window(sfRenderWindow *window)
{
    sfRenderWindow_close(window);
}

void analyse_events(game_info_t *game_info)
{
    while (sfRenderWindow_pollEvent(game_info->info_window->my_window,
        &game_info->info_window->event)) {
        if (game_info->info_window->event.type == sfEvtClosed)
            close_window(game_info->info_window->my_window);
        if (game_info->info_window->event.type == sfEvtKeyPressed) {
            manage_touch(game_info);
        }
    }
}
