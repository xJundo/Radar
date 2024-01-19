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

void show_tower(game_info_t *game_info)
{
    for (nodes_t *tmp = game_info->file->tower_info; tmp; tmp = tmp->next) {
        set_and_show_tower(tmp->data, game_info);
        set_and_show_tower_area(tmp->data, game_info);
    }
}

int check_error(tower_t *tower)
{
    if (tower->position.x <= 0 || tower->position.x >= 1920
        || tower->position.y <= 0 || tower->position.y >= 1080
        || tower->radius <= 0 || tower->radius >= 1920) {
        my_printf("Bad tower position\n");
        return 1;
    }
    return 0;
}

static float max(float a, float b)
{
    if (a > b)
        return a;
    return b;
}

static float min(float a, float b)
{
    if (a < b)
        return a;
    return b;
}

static int check_if_override(tower_t *tower,
    int decalage, sfIntRect rect, int *enable)
{
    sfVector2f pos = (sfVector2f){tower->position.x, tower->position.y};
    float x_closest;
    float y_closest;

    get_pos(decalage, &pos);
    x_closest = max(0, min(pos.x, 0 + 1920));
    y_closest = max(0, min(pos.y, 0 + 1080));
    if (euclidean_distance(pos,
        (sfVector2f){x_closest, y_closest}) <= tower->radius)
        *enable = 1;
    return 0;
}

int get_window(tower_t *tower)
{
    sfIntRect rect = (sfIntRect){0, 0, 1920, 1080};

    tower->start_w = 0;
    tower->start_h = 0;
    tower->end_w = 0;
    tower->end_h = 0;
    check_if_override(tower, 1920, rect, &tower->end_w);
    check_if_override(tower, 1080, rect, &tower->end_h);
    check_if_override(tower, -1920, rect, &tower->start_w);
    check_if_override(tower, -1080, rect, &tower->start_h);
    return 0;
}

tower_t *get_tower(file_t *file, int i)
{
    tower_t *tower;
    int len_nbr;

    if (file->script[i][0] == 'T') {
        tower = malloc(sizeof(tower_t));
        tower->position.x = my_str_to_float(file->script[i] + 3);
        len_nbr = 3 + my_strlen(my_float_to_str(my_str_to_float(
                file->script[i] + 3), 6));
        tower->position.y = my_str_to_float(file->script[i] + len_nbr + 1);
        len_nbr += 2 + my_strlen(my_float_to_str(my_str_to_float(
                file->script[i] + len_nbr + 1), 6));
        tower->radius = my_str_to_float(file->script[i] + len_nbr + 1);
        if (tower->radius > 100 || tower->radius < 0 || check_error(tower))
            return NULL;
        tower->radius = 1920 * (tower->radius / 100);
        tower->area = M_PI * tower->radius * tower->radius;
        get_window(tower);
        push_f_doubly(&file->tower_info, tower, UNKNOW);
    }
    return tower;
}

sprite_t *init_tower(game_info_t *game_info)
{
    sprite_t *tower = init_sprite(game_info->info_window->background_texture,
        "tower", (sfVector2f){0, 0},
        (sfIntRect) {1920, 87, 40, 60});

    tower->origin = (sfVector2f){20, 30};
    sfSprite_setOrigin(tower->sprite, tower->origin);
    tower->scale = (sfVector2f){1, 1};
    sfSprite_setScale(tower->sprite, tower->scale);
    tower->circle = init_circle((sfVector2f){0, 0}, 10, sfMagenta);
    tower->circle->rectangle = NULL;
    tower->text = NULL;
    tower->sound = NULL;
    tower->hitbox = NULL;
    return tower;
}
