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

static void set_tower_area_startwidth(tower_t *tower, game_info_t *game_info)
{
    sfVector2f pos = (sfVector2f){tower->position.x - tower->radius - 1920,
        tower->position.y - tower->radius};

    if (!tower->start_w)
        return;
    sfCircleShape_setRadius(game_info->file->tower->circle->circle,
        tower->radius);
    sfCircleShape_setPosition(game_info->file->tower->circle->circle,
    pos);
    if (!game_info->user_variables->hitbox)
        return;
    sfRenderWindow_drawCircleShape(game_info->info_window->my_window,
    game_info->file->tower->circle->circle, NULL);
}

static void set_tower_area_startheight(tower_t *tower, game_info_t *game_info)
{
    sfVector2f pos = (sfVector2f){tower->position.x - tower->radius,
        tower->position.y - tower->radius - 1080};

    if (!tower->start_h)
        return;
    sfCircleShape_setRadius(game_info->file->tower->circle->circle,
        tower->radius);
    sfCircleShape_setPosition(game_info->file->tower->circle->circle,
    pos);
    if (!game_info->user_variables->hitbox)
        return;
    sfRenderWindow_drawCircleShape(game_info->info_window->my_window,
    game_info->file->tower->circle->circle, NULL);
}

static void set_tower_area_endwidth(tower_t *tower, game_info_t *game_info)
{
    sfVector2f pos = (sfVector2f){tower->position.x - tower->radius + 1920,
        tower->position.y - tower->radius};

    if (!tower->end_w)
        return;
    sfCircleShape_setRadius(game_info->file->tower->circle->circle,
        tower->radius);
    sfCircleShape_setPosition(game_info->file->tower->circle->circle,
    pos);
    if (!game_info->user_variables->hitbox)
        return;
    sfRenderWindow_drawCircleShape(game_info->info_window->my_window,
    game_info->file->tower->circle->circle, NULL);
}

static void set_tower_area_endheight(tower_t *tower, game_info_t *game_info)
{
    sfVector2f pos = (sfVector2f){tower->position.x - tower->radius,
        tower->position.y - tower->radius + 1080};

    if (!tower->end_h)
        return;
    sfCircleShape_setRadius(game_info->file->tower->circle->circle,
    tower->radius);
    sfCircleShape_setPosition(game_info->file->tower->circle->circle,
    pos);
    if (!game_info->user_variables->hitbox)
        return;
    sfRenderWindow_drawCircleShape(game_info->info_window->my_window,
    game_info->file->tower->circle->circle, NULL);
}

static void set_tower_area_neutral(tower_t *tower, game_info_t *game_info)
{
    sfVector2f pos = (sfVector2f){tower->position.x - tower->radius,
        tower->position.y - tower->radius};

    sfCircleShape_setRadius(game_info->file->tower->circle->circle,
        tower->radius);
    sfCircleShape_setPosition(game_info->file->tower->circle->circle,
    pos);
    if (!game_info->user_variables->hitbox)
        return;
    sfRenderWindow_drawCircleShape(game_info->info_window->my_window,
    game_info->file->tower->circle->circle, NULL);
}

void set_and_show_tower_area(tower_t *tower, game_info_t *game_info)
{
    set_tower_area_startwidth(tower, game_info);
    set_tower_area_startheight(tower, game_info);
    set_tower_area_endwidth(tower, game_info);
    set_tower_area_endheight(tower, game_info);
    set_tower_area_neutral(tower, game_info);
}
