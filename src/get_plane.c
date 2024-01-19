/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include <math.h>
#include "my.h"
#include "csfml.h"


static int get_alternative_y(plane_t *plane, sfVector2f *pos, float y)
{
    float distance1 = plane->final_pos.y - (plane->position.y - 1080);
    float distance2 = plane->final_pos.y - (plane->position.y + 1080);

    if (ABS(distance1) < ABS(y)) {
        plane->go_by_endh = 1;
        pos->y = pos->y - 1080;
    }
    if (ABS(distance2) < ABS(y)) {
        plane->go_by_starth = 1;
        pos->y = pos->y + 1080;
    }
    return 0;
}

static sfVector2f get_alternative_trajectoire(plane_t *plane)
{
    sfVector2f pos = plane->position;
    float x = plane->final_pos.x - plane->position.x;
    float y = plane->final_pos.y - plane->position.y;
    float distance1 = plane->final_pos.x - (plane->position.x - 1920);
    float distance2 = plane->final_pos.x - (plane->position.x + 1920);

    plane->go_by_endw = 0;
    plane->go_by_startw = 0;
    plane->go_by_endh = 0;
    plane->go_by_starth = 0;
    if (ABS(distance1) < ABS(x)) {
        plane->go_by_endw = 1;
        pos.x = pos.x - 1920;
    }
    if (ABS(distance2) < ABS(x)) {
        plane->go_by_startw = 1;
        pos.x = pos.x + 1920;
    }
    get_alternative_y(plane, &pos, y);
    return pos;
}

static int get_variables(plane_t *plane)
{
    float scale1 = rand() % 2 ? 1.25 : 1.50;
    float scale2 = rand() % 2 ? 1.70 : 1.55;
    float scale = rand() % 2 ? scale1 : scale2;

    plane->land = 0;
    plane->destroyed = 0;
    plane->safe_zone = 0;
    plane->altitude = rand() % 1000;
    plane->scale = (sfVector2f) {scale, scale};
    plane->rect.width *= scale;
    plane->rect.height *= scale;
    if (plane->final_pos.y <= 0 || plane->final_pos.y >= 1080
        || plane->final_pos.x <= 0 || plane->final_pos.x >= 1920
        || plane->position.x <= 0 || plane->position.x >= 1920
        || plane->position.y <= 0 || plane->position.y >= 1080
        || plane->pixels <= 0 || plane->delay < 0)
        return 0;
    return 1;
}

float get_angle(sfVector2f pos, sfVector2f final_pos)
{
    float angle = atan2(final_pos.y - pos.y,
    final_pos.x - pos.x);
    float angle_degrees = angle * 180 / M_PI;

    return angle_degrees;
}

void get_speed(plane_t *plane, sfVector2f final_pos, sfVector2f position)
{
    float distance_x = final_pos.x - position.x;
    float distance_y = final_pos.y - position.y;
    float magnitude = sqrtf(distance_x * distance_x + distance_y * distance_y);

    if (magnitude != 0) {
        plane->speed.x = (distance_x / magnitude) * plane->pixels;
        plane->speed.y = (distance_y / magnitude) * plane->pixels;
    } else {
        my_printf("Error : magnitude = 0\n");
        plane->speed.x = 0;
        plane->speed.y = 0;
    }
}

int next_info_plane(file_t *file, plane_t *plane, int i, int *len_nbr)
{
    sfVector2f pos;

    plane->final_pos.y = my_str_to_float(file->script[i] + *len_nbr + 1);
    *len_nbr += 2 + my_strlen(my_float_to_str(my_str_to_float(
    file->script[i] + *len_nbr + 1), 6));
    plane->pixels = my_str_to_float(file->script[i] + *len_nbr + 1);
    *len_nbr += 2 + my_strlen(my_float_to_str(my_str_to_float(
    file->script[i] + *len_nbr + 1), 6));
    plane->delay = my_str_to_float(file->script[i] + *len_nbr + 1);
    pos = get_alternative_trajectoire(plane);
    get_speed(plane, plane->final_pos, pos);
    plane->angle = get_angle(pos, plane->final_pos);
    if (!get_variables(plane))
        return 0;
    return 1;
}

plane_t *get_plane(file_t *file, int i)
{
    plane_t *plane;
    int len_nbr;

    if (file->script[i][0] == 'A') {
        plane = malloc(sizeof(plane_t));
        plane->position.x = my_str_to_float(file->script[i] + 3);
        len_nbr = 3 + my_strlen(my_float_to_str(my_str_to_float(
        file->script[i] + 3), 6));
        plane->position.y = my_str_to_float(file->script[i] + len_nbr + 1);
        len_nbr += 2 + my_strlen(my_float_to_str(my_str_to_float(
        file->script[i] + len_nbr + 1), 6));
        plane->final_pos.x = my_str_to_float(file->script[i] + len_nbr + 1);
        len_nbr += 1 + my_strlen(my_float_to_str(my_str_to_float(
        file->script[i] + len_nbr + 1), 6));
        plane->rect = (sfIntRect){0, 0, 20, 20};
        if (!next_info_plane(file, plane, i, &len_nbr))
            return NULL;
        push_f_doubly(&file->planes_info, plane, UNKNOW);
    }
    return plane;
}

sprite_t *init_plane(game_info_t *game_info)
{
    sprite_t *plane = init_sprite(game_info->info_window->background_texture,
    "plane", (sfVector2f){0, 0},
    (sfIntRect){1920, 219, 20, 20});

    plane->scale = (sfVector2f){1, 1};
    sfSprite_setScale(plane->sprite, plane->scale);
    plane->origin = (sfVector2f){plane->rect.width / 2,
        plane->rect.height / 2};
    sfSprite_setOrigin(plane->sprite, plane->origin);
    plane->hitbox = malloc(sizeof(shape_t));
    plane->hitbox->rectangle = init_rectangle(plane->position,
    (sfVector2f){plane->rect.width, plane->rect.height}, sfWhite, 1);
    plane->hitbox->circle = NULL;
    plane->text = NULL;
    plane->sound = NULL;
    plane->circle = NULL;
    return plane;
}
