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

void show_hitbox_plane(game_info_t *game_info, plane_t *plane, sfVector2f pos)
{
    sfRectangleShape *rectangle = game_info->file->plane->hitbox->rectangle;

    if (!game_info->user_variables->hitbox)
        return;
    sfRectangleShape_setOutlineColor(rectangle, sfMagenta);
    if (!plane->safe_zone)
        sfRectangleShape_setOutlineColor(rectangle, sfWhite);
    sfRectangleShape_setOrigin(rectangle,
    game_info->file->plane->origin);
    sfRectangleShape_setScale(rectangle, plane->scale);
    sfRectangleShape_setPosition(rectangle, pos);
    sfRenderWindow_drawRectangleShape(game_info->info_window->my_window,
    rectangle, NULL);
}

void draw_plane_decalage(plane_t *plane, int decalage, game_info_t *game_info)
{
    sfVector2f pos = plane->position;

    get_pos(decalage, &pos);
    sfSprite_setRotation(game_info->file->plane->sprite, plane->angle);
    sfSprite_setPosition(game_info->file->plane->sprite, pos);
    sfSprite_setScale(game_info->file->plane->sprite, plane->scale);
    show_altitude(game_info, plane, game_info->mouse_pos, pos);
    if (game_info->user_variables->sprite)
        sfRenderWindow_drawSprite(game_info->info_window->my_window,
        game_info->file->plane->sprite, NULL);
    show_hitbox_plane(game_info, plane, pos);
}

int recalcul_alternative(plane_t *plane)
{
    if (plane->position.x > 1920 && plane->go_by_endw)
        plane->position.x -= 1920;
    if (plane->position.x < 0 && plane->go_by_startw)
        plane->position.x += 1920;
    if (plane->position.y > 1080 && plane->go_by_endh)
        plane->position.y -= 1080;
    if (plane->position.y < 0 && plane->go_by_starth)
        plane->position.y += 1080;
    return 0;
}

void show_alternative(game_info_t *game_info, plane_t *plane)
{
    recalcul_alternative(plane);
    draw_plane_decalage(plane, 0, game_info);
}
