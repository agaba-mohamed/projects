/*
** EPITECH PROJECT, 2022
** solver.c
** File description:
** main of the solver project
*/

#include "../include/my.h"

char **concat_map(int **map_int, char **map, info_t pos)
{
    int poid = map_int[0][0];
    map[0][0] = 'o';
    pp_t my_pos = {0, 0};
    for (int i = 0; poid != map_int[pos.h - 1][pos.l - 1]; i++) {
        my_pos = know_my_direction(map_int, my_pos, pos);
        map[my_pos.y][my_pos.x] = 'o';
        poid--;
    }
    return (map);
}

int **transform_map_into_int(char **map, info_t info)
{
    int **map_int = malloc(sizeof(int *) * (info.h + 1));
    for (int i = 0; i != info.h; i++)
        map_int[i] = malloc(sizeof(int) * (info.l + 1));
    int j = 0;
    for (int i = 0; i != info.h; j++) {
        map_int[i][j] = -1;
        if (map[i][j] == '*')
            map_int[i][j] = 0;
        if (j == info.h) {
            map_int[i][j] = -2;
            i++;
            j = -1;
        }
    }
    map_int[info.h - 1][info.l - 1] = 1;
    map_int[info.h] = NULL;
    return (map_int);
}

int main(int ac, char **av)
{
    srand(time(NULL));
    if (check_error(ac, av)) return (84);
    char **map = load_2d_array_from_file(av[1]);
    info_t pos = know_info(map);
    int **map_int = transform_map_into_int(map, pos);
    map_int = made_my_algo(map_int, pos);
    map = concat_map(map_int, map, pos);
    my_puttab(map);
    return (0);
}
