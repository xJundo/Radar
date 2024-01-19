/*
** EPITECH PROJECT, 2023
** main
** File description:
** display time
*/

#include "csfml.h"
#include "my.h"


int show_altitude(game_info_t *game_info,
    plane_t *plane, sfVector2i mouse_pos, sfVector2f pos)
{
    char str[20] = "height : ";

    if (!(mouse_pos.x >= pos.x - plane->rect.width / 2
        && mouse_pos.x <= pos.x + plane->rect.width / 2
        && mouse_pos.y >= pos.y - plane->rect.height / 2
        && mouse_pos.y <= pos.y + plane->rect.height / 2))
        return 0;
    my_strcat(str, my_str_nbr(plane->altitude));
    my_strcat(str, "m");
    sfText_setString(game_info->altitude, str);
    sfText_setPosition(game_info->altitude, pos);
    sfRenderWindow_drawText(game_info->info_window->my_window,
    game_info->altitude, sfFalse);
    return 0;
}
