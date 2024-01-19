/*
** EPITECH PROJECT, 2023
** main
** File description:
** quadtree
*/

#include <math.h>
#include "my.h"
#include "csfml.h"

static int check_nw_br(plane_t *plane, quadtree_t *root)
{
    sfVector2f botr =
        {plane->position.x + plane->rect.width / 2,
        plane->position.y + plane->rect.height / 2};

    if ((botr.x < root->pos.x + root->size.x / 2)
        && (botr.x > root->pos.x)
        && (botr.y < root->pos.y + root->size.y / 2)
        && (botr.y > root->pos.y))
        return 1;
    return 0;
}

static int check_nw_bl(plane_t *plane, quadtree_t *root)
{
    sfVector2f botl =
        {plane->position.x - plane->rect.width / 2,
        plane->position.y + plane->rect.height / 2};

    if ((botl.x < root->pos.x + root->size.x / 2)
        && (botl.x > root->pos.x)
        && (botl.y < root->pos.y + root->size.y / 2)
        && (botl.y > root->pos.y))
        return 1;
    return 0;
}

static int check_nw_tr(plane_t *plane, quadtree_t *root)
{
    sfVector2f topr =
        {plane->position.x + plane->rect.width / 2,
        plane->position.y - plane->rect.height / 2};

    if ((topr.x < root->pos.x + root->size.x / 2)
        && (topr.x > root->pos.x)
        && (topr.y < root->pos.y + root->size.y / 2)
        && (topr.y > root->pos.y))
        return 1;
    return 0;
}

static int check_nw_tl(plane_t *plane, quadtree_t *root)
{
    sfVector2f topl =
        {plane->position.x - plane->rect.width / 2,
        plane->position.y - plane->rect.height / 2};

    if ((topl.x < root->pos.x + root->size.x / 2)
        && (topl.x > root->pos.x)
        && (topl.y < root->pos.y + root->size.y / 2)
        && (topl.y > root->pos.y))
        return 1;
    return 0;
}

int insert_nw(quadtree_t *root, nodes_t *tmp,
    sfVector2f root_pos, game_info_t *game_info)
{
    plane_t *plane = tmp->data;
    int (*fptr[])(plane_t *, quadtree_t *) =
        {&check_nw_tl, &check_nw_tr, &check_nw_bl, &check_nw_br};

    for (int i = 0; i < 4; i++) {
        if (!fptr[i](plane, root))
            continue;
        split_quadtree(root, root_pos);
        root->nw->planes_count++;
        show_quadtree(root, game_info);
        push_f_doubly(&root->nw->planes_in_quadrant, plane, UNKNOW);
        insert_plane_in_quadtree(root->nw, tmp, game_info);
        return 1;
    }
    return 0;
}
