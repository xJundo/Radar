/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include <sys/stat.h>
#include "my.h"
#include "csfml.h"

sfText *init_text(text_t info_text)
{
    sfText *text = sfText_create();
    sfFont *font = sfFont_createFromFile(info_text.police);

    if (font != NULL)
        sfText_setFont(text, font);
    sfText_setString(text, info_text.str);
    sfText_setCharacterSize(text, info_text.size);
    sfText_setColor(text, info_text.color);
    sfText_setStyle(text, info_text.style);
    sfText_setOutlineColor(text, info_text.outline_color);
    sfText_setOutlineThickness(text, info_text.outline_size);
    sfText_setScale(text, info_text.scale);
    sfText_setPosition(text, info_text.position);
    return text;
}

int init_time(game_info_t *game_info)
{
    text_t time = {.str = "00.00",
        .police = "Planer-Regular.ttf",
        .color = sfCyan,
        .size = 100,
        .scale = {1, 1},
        .position = {1700, 0},
        .outline_color = sfBlack,
        .outline_size = 2};

    game_info->clock_time = sfClock_create();
    game_info->time = init_text(time);
    return 0;
}

int init_speedtext(game_info_t *game_info)
{
    text_t speed = {.str = "1x",
        .police = "Planer-Regular.ttf",
        .color = sfRed,
        .size = 100,
        .scale = {1, 1},
        .position = {1700, 100},
        .outline_color = sfBlack,
        .outline_size = 2};

    game_info->speed_t = init_text(speed);
    return 0;
}

int init_altitudetxt(game_info_t *game_info)
{
    text_t altitude = {.str = "z",
            .police = "Planer-Regular.ttf",
            .color = sfRed,
            .size = 30,
            .scale = {1, 1},
            .position = {10, 10},
            .outline_color = sfBlack,
            .outline_size = 2};

    game_info->altitude = init_text(altitude);
    return 0;
}

int init_scaletxt(game_info_t *game_info)
{
    text_t scale = {.str = "Scale : ",
            .police = "Planer-Regular.ttf",
            .color = sfRed,
            .size = 60,
            .scale = {1, 1},
            .position = {10, 10},
            .outline_color = sfBlack,
            .outline_size = 2};

    game_info->scaletxt = init_text(scale);
    return 0;
}
