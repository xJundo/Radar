/*
** EPITECH PROJECT, 2023
** main
** File description:
** display time
*/

#include "csfml.h"
#include "my.h"

char *my_str_float(float nb, int precision)
{
    float temp = nb - (int)nb;
    int len_int = my_strlen(my_str_nbr(nb));
    int n = 8 + len_int;
    char *str = malloc(sizeof(char) * (n + 1));
    int i = 0;
    int temp2;

    my_memset(str, 0, n + 1);
    my_strcat(str, my_str_nbr((int)nb));
    my_strcat(str, ":");
    if (temp < 0)
        temp *= -1;
    while (i < precision && i < 6) {
        temp *= 10;
        temp2 = temp;
        my_strcat(str, my_str_nbr(temp2));
        temp -= temp2;
        i++;
    }
    return str;
}

int show_time(sfRenderWindow *window, sfClock *clock, sfText *time, int speed)
{
    static float minute = 0.0;
    static float temp = 0.0;
    float seconds = sfClock_getElapsedTime(clock).microseconds / 1000000.0;
    char *str;

    if ((int)seconds != 0 && (int)seconds % 60 == 0) {
        minute++;
        sfClock_restart(clock);
    }
    if ((int)minute == 60)
        minute = 0.0;
    temp = minute;
    minute += seconds / 100;
    str = my_str_float(minute, 2);
    sfText_setString(time, str);
    sfRenderWindow_drawText(window, time, sfFalse);
    minute = temp;
    free(str);
    return 0;
}
