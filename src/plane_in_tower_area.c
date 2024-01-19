/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "mylist.h"
#include "my.h"
#include "csfml.h"

static float manhattan_distance(sfVector2f pos_1, sfVector2f pos_2)
{
    return (fabs(pos_1.x - pos_2.x) + fabs(pos_1.y - pos_2.y));
}

static int check_manhattan_bis2(plane_t *plane,
    tower_t *tower, float radius_adjusted, sfVector2f pos)
{
    if ((manhattan_distance((sfVector2f)
        {plane->position.x - plane->rect.width / 2, plane->position.y},
        pos) <= radius_adjusted
        || manhattan_distance((sfVector2f)
        {plane->position.x + plane->rect.width / 2, plane->position.y},
        pos) <= radius_adjusted
        || manhattan_distance((sfVector2f)
        {plane->position.x, plane->position.y - plane->rect.height / 2},
        pos) <= radius_adjusted
        || manhattan_distance((sfVector2f)
        {plane->position.x, plane->position.y + plane->rect.height / 2},
        pos) <= radius_adjusted)) {
        return 1;
    }
    return 0;
}

static int check_manhattan_bis(plane_t *plane,
    tower_t *tower, float radius_adjusted, sfVector2f pos)
{
    sfVector2f bottom_left =
        {plane->position.x - plane->rect.width / 2,
        plane->position.y + plane->rect.height / 2};
    sfVector2f bottom_right =
        {plane->position.x + plane->rect.width / 2,
        plane->position.y + plane->rect.height / 2};

    if (manhattan_distance(bottom_left, pos) <= radius_adjusted
        || manhattan_distance(bottom_right, pos)
        <= radius_adjusted)
        return 1;
    return 0;
}

int get_pos(int decalage, sfVector2f *pos)
{
    if (decalage == 1920)
        pos->x += 1920;
    if (decalage == 1080)
        pos->y += 1080;
    if (decalage == -1920)
        pos->x -= 1920;
    if (decalage == -1080)
        pos->y -= 1080;
    return 1;
}

int check_manhattan(plane_t *plane, tower_t *tower,
    float radius_adjusted, int decalage)
{
    sfVector2f top_left =
        {plane->position.x - plane->rect.width / 2,
        plane->position.y - plane->rect.height / 2};
    sfVector2f top_right =
        {plane->position.x + plane->rect.width / 2,
        plane->position.y - plane->rect.height / 2};
    sfVector2f pos = tower->position;

    get_pos(decalage, &pos);
    if (manhattan_distance(top_left, pos) <= radius_adjusted
        || manhattan_distance(top_right, pos) <= radius_adjusted
        || check_manhattan_bis(plane, tower, radius_adjusted, pos)
        || check_manhattan_bis2(plane, tower, radius_adjusted, pos)) {
        return 1;
    }
    return 0;
}

int distances_conditions(plane_t *plane, tower_t *tower, float radius_adjusted)
{
    if (check_manhattan(plane, tower, radius_adjusted, 0)
        || (tower->end_w
        && check_manhattan(plane, tower, radius_adjusted, 1920))
        || (tower->end_h
        && check_manhattan(plane, tower, radius_adjusted, 1080))
        || (tower->start_w
        && check_manhattan(plane, tower, radius_adjusted, -1920))
        || (tower->start_h
        && check_manhattan(plane, tower, radius_adjusted, -1080))) {
        if (check_euclidian(plane, tower, 0)
            || (tower->end_w && check_euclidian(plane, tower, 1920))
            || (tower->end_h && check_euclidian(plane, tower, 1080))
            || (tower->start_w && check_euclidian(plane, tower, -1920))
            || (tower->start_h && check_euclidian(plane, tower, -1080))) {
            plane->safe_zone = 1;
            return 1;
        } else
            plane->safe_zone = 0;
    }
    return 0;
}

void check_safe_zone(plane_t *plane,
    nodes_t **tower_list)
{
    tower_t *tower;
    float radius_adjusted;

    for (nodes_t *tmp = *tower_list; tmp; tmp = tmp->next) {
        tower = ((tower_t *) tmp->data);
        radius_adjusted = sqrt(2) * tower->radius;
        if (distances_conditions(plane, tower, radius_adjusted))
            return;
        else {
            plane->safe_zone = 0;
        }
    }
}
