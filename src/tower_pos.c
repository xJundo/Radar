/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include <sys/stat.h>
#include "my.h"
#include "mylist.h"
#include "csfml.h"

static void set_tower_endwidth(tower_t *tower, game_info_t *game_info)
{
    if (!(tower->position.x + game_info->file->tower->rect.width / 2 > 1920))
        return;
    sfSprite_setPosition(game_info->file->tower->sprite,
    (sfVector2f){tower->position.x - 1920, tower->position.y});
    if (!game_info->user_variables->sprite)
        return;
    sfRenderWindow_drawSprite(game_info->info_window->my_window,
    game_info->file->tower->sprite, NULL);
}

static void set_tower_endheight(tower_t *tower, game_info_t *game_info)
{
    if (!(tower->position.y + game_info->file->tower->rect.height / 2 > 1080))
        return;
    sfSprite_setPosition(game_info->file->tower->sprite,
    (sfVector2f){tower->position.x, tower->position.y - 1080});
    if (!game_info->user_variables->sprite)
        return;
    sfRenderWindow_drawSprite(game_info->info_window->my_window,
    game_info->file->tower->sprite, NULL);
}

static void set_tower_startwidth(tower_t *tower, game_info_t *game_info)
{
    if (!(tower->position.x - game_info->file->tower->rect.width / 2 < 0))
        return;
    sfSprite_setPosition(game_info->file->tower->sprite,
    (sfVector2f){tower->position.x + 1920, tower->position.y});
    if (!game_info->user_variables->sprite)
        return;
    sfRenderWindow_drawSprite(game_info->info_window->my_window,
    game_info->file->tower->sprite, NULL);
}

static void set_tower_startheight(tower_t *tower, game_info_t *game_info)
{
    if (!(tower->position.y - game_info->file->tower->rect.height / 2 < 0))
        return;
    sfSprite_setPosition(game_info->file->tower->sprite,
    (sfVector2f){tower->position.x, tower->position.y + 1080});
    if (!game_info->user_variables->sprite)
        return;
    sfRenderWindow_drawSprite(game_info->info_window->my_window,
    game_info->file->tower->sprite, NULL);
}

static void set_tower_neutral(tower_t *tower, game_info_t *game_info)
{
    sfSprite_setPosition(game_info->file->tower->sprite,
    tower->position);
    if (!game_info->user_variables->sprite)
        return;
    sfRenderWindow_drawSprite(game_info->info_window->my_window,
    game_info->file->tower->sprite, NULL);
}

void set_and_show_tower(tower_t *tower, game_info_t *game_info)
{
    set_tower_startwidth(tower, game_info);
    set_tower_startheight(tower, game_info);
    set_tower_endwidth(tower, game_info);
    set_tower_endheight(tower, game_info);
    set_tower_neutral(tower, game_info);
}
