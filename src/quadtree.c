/*
** EPITECH PROJECT, 2023
** main
** File description:
** quadtree
*/

#include <math.h>
#include "my.h"
#include "csfml.h"

static void show_each_root(quadtree_t *root, game_info_t *game_info)
{
    sfRectangleShape_setPosition(game_info->quad->rectangle, root->pos);
    sfRectangleShape_setSize(game_info->quad->rectangle, root->size);
    sfRenderWindow_drawRectangleShape(game_info->info_window->my_window,
    game_info->quad->rectangle, NULL);
}

void show_quadtree(quadtree_t *root, game_info_t *game_info)
{
    if (game_info->user_variables->quad_treeview) {
        show_each_root(root->nw, game_info);
        show_each_root(root->ne, game_info);
        show_each_root(root->sw, game_info);
        show_each_root(root->se, game_info);
    }
}

int split_quadtree(quadtree_t *root, sfVector2f root_pos)
{
    get_nw(root, root_pos);
    get_ne(root, root_pos);
    get_sw(root, root_pos);
    get_se(root, root_pos);
    return 1;
}

void insert_plane_in_quadtree(quadtree_t *root,
    nodes_t *tmp, game_info_t *game_info)
{
    sfVector2f root_pos = {root->pos.x, root->pos.y};

    if (root->size.x <= ((plane_t *)tmp->data)->rect.width * 3)
        return;
    insert_nw(root, tmp, root_pos, game_info);
    insert_ne(root, tmp, root_pos, game_info);
    insert_sw(root, tmp, root_pos, game_info);
    insert_se(root, tmp, root_pos, game_info);
}

void push_in(quadtree_t *root, nodes_t *tmp, game_info_t *game_info)
{
    if (((plane_t *)tmp->data)->safe_zone)
        return;
    push_f_doubly(&root->planes_in_quadrant, tmp->data, UNKNOW);
    root->planes_count++;
    insert_plane_in_quadtree(root, tmp, game_info);
}

quadtree_t *init_quadtree(sfVector2f pos, sfVector2f size)
{
    quadtree_t *root = malloc(sizeof(quadtree_t));

    root->pos = pos;
    root->size = size;
    root->planes_in_quadrant = NULL;
    root->planes_count = 0;
    root->nw = NULL;
    root->ne = NULL;
    root->sw = NULL;
    root->se = NULL;
    return root;
}
