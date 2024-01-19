/*
** EPITECH PROJECT, 2023
** main
** File description:
** quadtree
*/

#include <math.h>
#include "my.h"
#include "csfml.h"

static int check_se_br(plane_t *plane, quadtree_t *root)
{
    sfVector2f botr =
        {plane->position.x + plane->rect.width / 2,
        plane->position.y + plane->rect.height / 2};

    if ((botr.x < root->pos.x + root->size.x)
        && (botr.x > root->pos.x + root->size.x / 2)
        && (botr.y < root->pos.y + root->size.y)
        && (botr.y > root->pos.y + root->size.y / 2))
        return 1;
    return 0;
}

static int check_se_bl(plane_t *plane, quadtree_t *root)
{
    sfVector2f botl =
        {plane->position.x - plane->rect.width / 2,
        plane->position.y + plane->rect.height / 2};

    if ((botl.x < root->pos.x + root->size.x)
        && (botl.x > root->pos.x + root->size.x / 2)
        && (botl.y < root->pos.y + root->size.y)
        && (botl.y > root->pos.y + root->size.y / 2))
        return 1;
    return 0;
}

static int check_se_tr(plane_t *plane, quadtree_t *root)
{
    sfVector2f topr =
        {plane->position.x + plane->rect.width / 2,
        plane->position.y - plane->rect.height / 2};

    if ((topr.x < root->pos.x + root->size.x)
        && (topr.x > root->pos.x + root->size.x / 2)
        && (topr.y < root->pos.y + root->size.y)
        && (topr.y > root->pos.y + root->size.y / 2))
        return 1;
    return 0;
}

static int check_se_tl(plane_t *plane, quadtree_t *root)
{
    sfVector2f topl =
        {plane->position.x - plane->rect.width / 2,
        plane->position.y - plane->rect.height / 2};

    if ((topl.x < root->pos.x + root->size.x)
        && (topl.x > root->pos.x + root->size.x / 2)
        && (topl.y < root->pos.y + root->size.y)
        && (topl.y > root->pos.y + root->size.y / 2))
        return 1;
    return 0;
}

int insert_se(quadtree_t *root, nodes_t *tmp,
    sfVector2f root_pos, game_info_t *game_info)
{
    plane_t *plane = tmp->data;
    int (*fptr[])(plane_t *, quadtree_t *) =
        {&check_se_tl, &check_se_tr, &check_se_bl, &check_se_br};

    for (int i = 0; i < 4; i++) {
        if (!fptr[i](plane, root))
            continue;
        split_quadtree(root, root_pos);
        root->se->planes_count++;
        show_quadtree(root, game_info);
        push_f_doubly(&root->se->planes_in_quadrant, plane, UNKNOW);
        insert_plane_in_quadtree(root->se, tmp, game_info);
        return 1;
    }
    return 0;
}
