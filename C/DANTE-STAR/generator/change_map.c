/*
** EPITECH PROJECT, 2022
** change_map
** File description:
** change_map
*/

#include "../include/my.h"

int check_arround(char **map, int direction, info_t pos, pp_t pp)
{
    int var = 0;
    if (check_direction_outside_map(map, 1, pos, pp) == 0)
        if (check_direction(map, 1, pos, pp))
            var++;
    if (check_direction_outside_map(map, 2, pos, pp) == 0)
        if (check_direction(map, 2, pos, pp))
            var++;
    if (check_direction_outside_map(map, 3, pos, pp) == 0)
        if (check_direction(map, 3, pos, pp))
            var++;
    if (check_direction_outside_map(map, 4, pos, pp) == 0)
        if (check_direction(map, 4, pos, pp))
            var++;
    if (var == 0)
        return (0);
    return (1);
}

char **change_map(char **map, int direction, info_t pos, pp_t pp)
{
    if (direction == 1) {
        map[pp.y - 1][pp.x] = '*';
        map[pp.y - 2][pp.x] = '*';
        return (map);
    } else if (direction == 2) {
        map[pp.y][pp.x + 1] = '*';
        map[pp.y][pp.x + 2] = '*';
        return (map);
    } else if (direction == 3) {
        map[pp.y + 1][pp.x] = '*';
        map[pp.y + 2][pp.x] = '*';
        return (map);
    } else if (direction == 4) {
        map[pp.y][pp.x - 1] = '*';
        map[pp.y][pp.x - 2] = '*';
        return (map);
    }
    return (map);
}

int verif_num(char *str)
{
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9') {
            return (84);
        }
        i++;
    }
    return (0);
}
