/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include <sys/stat.h>
#include "my.h"
#include "csfml.h"

int fill_info(file_t *file)
{
    plane_t *plane = NULL;
    tower_t *tower;
    int len_nbr;

    for (int i = 0; file->script[i]; i++) {
        if (!get_plane(file, i) || !get_tower(file, i))
            return 0;
    }
    return 1;
}

static int bad_back(int i, file_t *file)
{
    for (int j = 0; file->script[i][j]; j++)
    if (file->script[i][j] != 'A'
        && file->script[i][j] != 'T'
        && file->script[i][j] != ' '
        && !(file->script[i][j] >= '0' && file->script[i][j] <= '9')
        && file->script[i][j] != '.')
        return 1;
    return 0;
}

int get_info_script(file_t *file)
{
    for (int i = 0; file->script[i]; i++) {
        if (file->script[i][0] != 'A'
            && file->script[i][0] != 'T')
            return 0;
        if (file->script[i][0] == 'T')
            file->nb_towers++;
        if (file->script[i][0] == 'A')
            file->nb_planes++;
    }
    for (int i = 0; file->script[i]; i++) {
        if (bad_back(i, file))
            return 0;
    }
    return 1;
}

int init_script(game_info_t *game_info, char **av)
{
    int fd = open(av[1], O_RDONLY);

    game_info->file = malloc(sizeof(file_t));
    game_info->file->s = malloc(sizeof(struct stat));
    game_info->file->nb_planes = 0;
    game_info->file->nb_towers = 0;
    game_info->file->planes_info = NULL;
    game_info->file->tower_info = NULL;
    stat(av[1], game_info->file->s);
    game_info->file->buffer =
    malloc(sizeof(char) * game_info->file->s->st_size + 1);
    game_info->file->buffer[game_info->file->s->st_size] = '\0';
    read(fd, game_info->file->buffer, game_info->file->s->st_size);
    game_info->file->script = my_str_to_word_array(game_info->file->buffer);
    if (!get_info_script(game_info->file) || !fill_info(game_info->file))
        return 0;
    return 1;
}
