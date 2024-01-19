/*
** EPITECH PROJECT, 2023
** main
** File description:
** quadtree
*/

#include <math.h>
#include "my.h"
#include "csfml.h"

static int check_collide(struct plane *plane1,
    plane_t *plane2, float scale)
{
    float left1 = plane1->position.x - (plane1->rect.width * scale) / 2;
    float right1 = plane1->position.x + (plane1->rect.width * scale) / 2;
    float top1 = plane1->position.y - (plane1->rect.height * scale) / 2;
    float bottom1 = plane1->position.y + (plane1->rect.height * scale) / 2;
    float left2 = plane2->position.x - (plane2->rect.width * scale) / 2;
    float right2 = plane2->position.x + (plane2->rect.width * scale) / 2;
    float top2 = plane2->position.y - (plane2->rect.height * scale) / 2;
    float bottom2 = plane2->position.y + (plane2->rect.height * scale) / 2;

    if ((right1 >= left2 && left1 <= right2 && bottom1 >= top2
        && top1 <= bottom2)) {
        plane1->destroyed = 1;
        plane2->destroyed = 1;
        return 1;
    }
    return 0;
}

static int check_second(nodes_t *tmp, plane_t *plane1,
    nodes_t **plane_list, float scale)
{
    plane_t *plane2;

    for (nodes_t *tmp2 = *plane_list; tmp2; tmp2 = tmp2->next) {
        plane2 = tmp2->data;
        if (tmp == tmp2 || plane2->destroyed || plane2->safe_zone)
            continue;
        if (check_collide(plane1, plane2, scale)) {
            return 1;
        }
    }
    return 0;
}

void check_collision_quadtree(quadtree_t *root, game_info_t *game_info)
{
    for (nodes_t *tmp = root->planes_in_quadrant; tmp; tmp = tmp->next) {
        if (check_second(tmp, tmp->data, &root->planes_in_quadrant,
            game_info->user_variables->scale.x)) {
            root->planes_count -= 2;
            break;
        }
    }
}

int check_recursively(quadtree_t *root, game_info_t *game_info)
{
    if (!root || root->planes_count < 2) {
        return 0;
    }
    for (nodes_t *tmp = root->planes_in_quadrant; tmp; tmp = tmp->next) {
        if (root->size.x <= ((plane_t *)tmp->data)->rect.width
            * game_info->user_variables->scale.x * 3) {
            check_collision_quadtree(root, game_info);
            return 1;
        }
    }
    check_recursively(root->nw, game_info);
    check_recursively(root->ne, game_info);
    check_recursively(root->sw, game_info);
    check_recursively(root->se, game_info);
}
