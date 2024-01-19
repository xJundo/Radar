/*
** EPITECH PROJECT, 2023
** main
** File description:
** display time
*/

#include "csfml.h"
#include "my.h"


int show_speed(sfText *text, int speed_user, sfRenderWindow *window)
{
    char str[7] = {0};

    str[0] = 'x';
    str[5] = '\0';
    my_strcat(str, my_str_nbr(speed_user));
    sfText_setString(text, str);
    sfRenderWindow_drawText(window, text, sfFalse);
    return 0;
}
