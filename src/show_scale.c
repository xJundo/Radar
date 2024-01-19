/*
** EPITECH PROJECT, 2023
** main
** File description:
** display time
*/

#include "csfml.h"
#include "my.h"

int show_scale(sfRenderWindow *window, sfText *txt, sfVector2f scale)
{
    char str[25] = "Global Scale : ";

    my_strcat(str, my_float_to_str(scale.x, 2));
    sfText_setString(txt, str);
    sfRenderWindow_drawText(window, txt, sfFalse);
    return 0;
}
