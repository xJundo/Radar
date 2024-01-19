/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "mylist.h"
#include "my.h"
#include "csfml.h"

float euclidean_distance(sfVector2f pos_1, sfVector2f pos_2)
{
    return (sqrt(pow(pos_1.x - pos_2.x, 2) + pow(pos_1.y - pos_2.y, 2)));
}

int check_euclidian_bis(plane_t *plane, tower_t *tower, sfVector2f pos)
{
    if (euclidean_distance((sfVector2f)
        {plane->position.x - plane->rect.width / 2, plane->position.y},
        pos) <= tower->radius
        || euclidean_distance((sfVector2f)
        {plane->position.x + plane->rect.width / 2, plane->position.y},
        pos) <= tower->radius
        || euclidean_distance((sfVector2f)
        {plane->position.x, plane->position.y - plane->rect.height / 2},
        pos) <= tower->radius
        || euclidean_distance((sfVector2f) {plane->position.x,
        plane->position.y + plane->rect.height / 2},
        pos) <= tower->radius)
        return 1;
    return 0;
}

static sfVector2f get_top_left(plane_t *plane)
{
    sfVector2f top_left =
        {plane->position.x - plane->rect.width / 2,
        plane->position.y - plane->rect.height / 2};

    return top_left;
}

static sfVector2f get_top_right(plane_t *plane)
{
    sfVector2f top_right =
        {plane->position.x + plane->rect.width / 2,
        plane->position.y - plane->rect.height / 2};

    return top_right;
}

static sfVector2f get_bottom_left(plane_t *plane)
{
    sfVector2f bottom_left =
        {plane->position.x - plane->rect.width / 2,
        plane->position.y + plane->rect.height / 2};

    return bottom_left;
}

static sfVector2f get_bottom_right(plane_t *plane)
{
    sfVector2f bottom_right =
        {plane->position.x + plane->rect.width / 2,
        plane->position.y + plane->rect.height / 2};

    return bottom_right;
}

int check_euclidian(plane_t *plane, tower_t *tower, int decalage)
{
    sfVector2f top_left = get_top_left(plane);
    sfVector2f top_right = get_top_right(plane);
    sfVector2f bottom_left = get_bottom_left(plane);
    sfVector2f bottom_right = get_bottom_right(plane);
    sfVector2f pos = tower->position;

    if (!get_pos(decalage, &pos))
        return 0;
    if (euclidean_distance(top_left, pos) <= tower->radius
        || euclidean_distance(top_right, pos) <= tower->radius
        || euclidean_distance(bottom_left, pos) <= tower->radius
        || euclidean_distance(bottom_right, pos) <= tower->radius
        || check_euclidian_bis(plane, tower, pos))
        return 1;
    return 0;
}
