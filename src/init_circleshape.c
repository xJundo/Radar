/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "my.h"
#include "csfml.h"

shape_t *init_circle(sfVector2f position, float radius, sfColor color)
{
    shape_t *shape = malloc(sizeof(shape_t));

    shape->circle = sfCircleShape_create();
    sfCircleShape_setRadius(shape->circle, radius);
    sfCircleShape_setPosition(shape->circle, position);
    shape->position = position;
    sfCircleShape_setFillColor(shape->circle, sfTransparent);
    sfCircleShape_setOutlineColor(shape->circle, color);
    sfCircleShape_setOutlineThickness(shape->circle, 1);
    return shape;
}

sfRectangleShape *init_rectangle(sfVector2f position,
    sfVector2f size, sfColor color, int thickness)
{
    sfRectangleShape *rectangle = sfRectangleShape_create();

    sfRectangleShape_setSize(rectangle, size);
    sfRectangleShape_setFillColor(rectangle, sfTransparent);
    sfRectangleShape_setOutlineColor(rectangle, color);
    sfRectangleShape_setOutlineThickness(rectangle, thickness);
    sfRectangleShape_setPosition(rectangle, position);
    return rectangle;
}
