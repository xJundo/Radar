/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "my.h"
#include "csfml.h"

int my_cmpland_void(void *data, void *data2)
{
    plane_t *plane = data;
    sfVector2f *pos_end = data2;
    float speed_x = plane->speed.x;
    float speed_y = plane->speed.y;
    float final_x = plane->final_pos.x;
    float final_y = plane->final_pos.y;

    if ((speed_x < 0 && plane->position.x >= final_x)
        || (speed_x > 0 && plane->position.x <= final_x)
        || (speed_y < 0 && plane->position.y >= final_y)
        || (speed_y > 0 && plane->position.y <= final_y)) {
        return 1;
    }
    return 0;
}
