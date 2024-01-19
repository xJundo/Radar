/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include <sys/stat.h>
#include "my.h"
#include "csfml.h"

static int print_help(char **av)
{
    my_printf("Air radar simulation\n\n");
    my_printf("USAGE\n");
    my_printf("./my_radar [OPTIONS] path_to_script\n\n");
    my_printf("path_to_script\tThe path to the script file.\n\n");
    my_printf("To see the script file format,"
    " please refer to the script.legend file\n");
    my_printf("OPTIONS\n");
    my_printf("\t-h\t\tPrint the usage and quit.\n");
    my_printf("USER INTERACTIONS\n");
    my_printf("\t'Q' key\t\tenable/disable quadtree vizualisation."
    " (Will lag if a lot of planes)\n");
    my_printf("\t'L' key\t\tenable/disable hitboxes and areas.\n");
    my_printf("\t'K' key\t\tenable/disable sprites.\n");
    my_printf("\t'RIGHT' key\tincrease plane's speed.\n");
    my_printf("\t'LEFT' key\tdecrease plane's speed.\n");
    my_printf("\t'UP' key\tincrease plane's scale (so the quadtree).\n");
    my_printf("\t'DOWN' key\tdecrease plane's scale (so the quadtree).\n");
    my_printf("\t'SPACE' key\tenable/disable plane's movement\n");
    return 0;
}

int error_handling(int ac, char **av, game_info_t *game_info, struct stat *s)
{
    if (ac > 2 || ac < 2)
        return 84;
    if (ac == 2 && (my_strcmp(av[1], "-h") == 0)) {
        print_help(av);
        return 0;
    } else if (ac == 2 && stat(av[1], s) == -1) {
        my_putstr_error("Error: File not found\n");
        return 84;
    }
    if (!init_script(game_info, av)) {
        my_putstr_error("Error: Invalid file\n");
        return 84;
    }
    return 1;
}

int my_radar(int ac, char **av)
{
    game_info_t game_info = {0};
    struct stat s;
    int i = error_handling(ac, av, &game_info, &s);

    if (i != 1)
        return i;
    init_game_info(&game_info);
    draw_everything(&game_info);
    free_all(&game_info);
    return 0;
}
