/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "mylist.h"
#include "my.h"
#include "csfml.h"

//sfRectangleShape_setRotation(game_info->file->plane->hitbox->rectangle,
//plane->angle);

int check_end(nodes_t **list)
{
    plane_t *plane;

    for (nodes_t *tmp = *list; tmp; tmp = tmp->next) {
        plane = tmp->data;
        if (!(plane->land || plane->destroyed))
            return 0;
    }
    return 1;
}

void move_plane(int speeduser, float delay, sfSprite *sprite, nodes_t *tmp)
{
    plane_t *plane = tmp->data;
    sfVector2f position = sfSprite_getPosition(sprite);
    sfVector2f old_speed = plane->speed;

    plane->speed.x = plane->speed.x * delay * speeduser;
    plane->speed.y = plane->speed.y * delay * speeduser;
    if ((position.x <= plane->final_pos.x - 10
        || position.x >= plane->final_pos.x + 10)
        || (position.y <= plane->final_pos.y - 10
        || position.y >= plane->final_pos.y + 10))
        sfSprite_move(sprite, plane->speed);
    else
        plane->land = 1;
    plane->position = sfSprite_getPosition(sprite);
    plane->speed = old_speed;
}

void update(game_info_t *game_info, nodes_t *tmp,
    plane_t *plane, sfVector2f old_scale)
{
    plane->rect.width = plane->rect.width * game_info->user_variables->scale.x;
    plane->rect.height = plane->rect.height
        * game_info->user_variables->scale.y;
    show_alternative(game_info, plane);
    if (game_info->user_variables->move)
        move_plane(game_info->user_variables->speeduser,
        game_info->info_window->delay, game_info->file->plane->sprite, tmp);
    check_safe_zone(tmp->data, &game_info->file->tower_info);
    push_in(game_info->quadtree, tmp, game_info);
    plane->rect = plane->old_rect;
    plane->scale = old_scale;
}

int show_plane(game_info_t *game_info)
{
    float seconds;
    plane_t *plane;
    sfVector2f old_scale;

    for (nodes_t *tmp = game_info->file->planes_info; tmp; tmp = tmp->next) {
        seconds =
        sfClock_getElapsedTime(game_info->info_window->clock).microseconds /
        1000000.0;
        plane = tmp->data;
        if (plane->land || plane->destroyed || (seconds < plane->delay))
            continue;
        old_scale = plane->scale;
        plane->old_rect = plane->rect;
        plane->scale.x = plane->scale.x * game_info->user_variables->scale.x;
        plane->scale.y = plane->scale.y * game_info->user_variables->scale.y;
        update(game_info, tmp, plane, old_scale);
    }
    return 0;
}
