/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "my.h"
#include "csfml.h"

sprite_t *init_sprite(sfTexture *texture,
    char *text, sfVector2f pos, sfIntRect bite)
{
    sprite_t *sprite = malloc(sizeof(sprite_t));

    sprite->sprite = sfSprite_create();
    sprite->text = sfText_create();
    sprite->rect = bite;
    sfSprite_setTexture(sprite->sprite, texture, false);
    sfSprite_setTextureRect(sprite->sprite, sprite->rect);
    sfSprite_setPosition(sprite->sprite, pos);
    sprite->position = sfSprite_getPosition(sprite->sprite);
    sprite->id = text;
    return sprite;
}
