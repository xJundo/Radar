/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"
#include "my.h"

void free_quadtree_recursively(quadtree_t *root)
{
    if (!root)
        return;
    if (root->nw || root->ne || root->sw || root->se) {
        free_quadtree_recursively(root->nw);
        free_quadtree_recursively(root->ne);
        free_quadtree_recursively(root->sw);
        free_quadtree_recursively(root->se);
    }
    delete_list(&root->planes_in_quadrant, "node");
    free(root);
}

static int free_text(sfText *text)
{
    sfText_destroy(text);
    return 0;
}

static int free_shape(shape_t *shape)
{
    if (shape->rectangle)
        sfRectangleShape_destroy(shape->rectangle);
    if (shape->circle)
        sfCircleShape_destroy(shape->circle);
    return 0;
}

int free_sprite(sprite_t *sprite_inf)
{
    sfSprite_destroy(sprite_inf->sprite);
    if (sprite_inf->text)
        sfText_destroy(sprite_inf->text);
    if (sprite_inf->hitbox)
        free_shape(sprite_inf->hitbox);
    if (sprite_inf->circle)
        free_shape(sprite_inf->circle);
    if (sprite_inf->sound)
        sfSound_destroy(sprite_inf->sound);
    return 0;
}

int free_file(file_t *file)
{
    free(file->buffer);
    for (int i = 0; file->script[i]; i++)
        free(file->script[i]);
    delete_list(&file->planes_info, "nd");
    delete_list(&file->tower_info, "nd");
    free_sprite(file->plane);
    free_sprite(file->tower);
    return 0;
}

int free_info_window(window_info_t *info_window)
{
    sfTexture_destroy(info_window->background_texture);
    sfSprite_destroy(info_window->background_sprite);
    sfRenderWindow_destroy(info_window->my_window);
    sfClock_destroy(info_window->clock);
    return 0;
}

int free_all(game_info_t *game_info)
{
    free_info_window(game_info->info_window);
    free_file(game_info->file);
    free_text(game_info->time);
    free_text(game_info->speed_t);
    free_text(game_info->altitude);
    free_shape(game_info->quad);
    sfClock_destroy(game_info->clock_time);
    return 0;
}
