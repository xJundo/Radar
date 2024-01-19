/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include <math.h>
#include "my.h"
#include "csfml.h"

void get_nw(quadtree_t *root, sfVector2f root_pos)
{
    if (root->nw != NULL)
        return;
    root->nw = malloc(sizeof(quadtree_t));
    root->nw->pos = root_pos;
    root->nw->size = (sfVector2f){root->size.x / 2, root->size.y / 2};
    root->nw->planes_count = 0;
    root->nw->planes_in_quadrant = NULL;
    root->nw->nw = NULL;
    root->nw->ne = NULL;
    root->nw->sw = NULL;
    root->nw->se = NULL;
}

void get_ne(quadtree_t *root, sfVector2f root_pos)
{
    if (root->ne != NULL)
        return;
    root->ne = malloc(sizeof(quadtree_t));
    root->ne->pos = (sfVector2f){root_pos.x + root->size.x / 2, root_pos.y};
    root->ne->size = (sfVector2f){root->size.x / 2, root->size.y / 2};
    root->ne->planes_count = 0;
    root->ne->planes_in_quadrant = NULL;
    root->ne->nw = NULL;
    root->ne->ne = NULL;
    root->ne->sw = NULL;
    root->ne->se = NULL;
}

void get_sw(quadtree_t *root, sfVector2f root_pos)
{
    if (root->sw != NULL)
        return;
    root->sw = malloc(sizeof(quadtree_t));
    root->sw->pos = (sfVector2f){root_pos.x, root_pos.y + root->size.y / 2};
    root->sw->size = (sfVector2f){root->size.x / 2, root->size.y / 2};
    root->sw->planes_count = 0;
    root->sw->planes_in_quadrant = NULL;
    root->sw->nw = NULL;
    root->sw->ne = NULL;
    root->sw->sw = NULL;
    root->sw->se = NULL;
}

void get_se(quadtree_t *root, sfVector2f root_pos)
{
    if (root->se != NULL)
        return;
    root->se = malloc(sizeof(quadtree_t));
    root->se->pos = (sfVector2f){root_pos.x + root->size.x / 2,
        root_pos.y + root->size.y / 2};
    root->se->size = (sfVector2f){root->size.x / 2, root->size.y / 2};
    root->se->planes_count = 0;
    root->se->planes_in_quadrant = NULL;
    root->se->nw = NULL;
    root->se->ne = NULL;
    root->se->sw = NULL;
    root->se->se = NULL;
}
