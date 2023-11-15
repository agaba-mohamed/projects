/*
** EPITECH PROJECT, 2022
** check_direction
** File description:
** check_direction
*/

#include "../include/my.h"

int generate_numb(int min, int max)
{
    int x = 1 + rand() % 4;
    return (x);
}

int generate_numb_2(int min, int max)
{
    int x = 1 + rand() % 10;
    return (x);
}

int verify_finished(char **map, info_t pos)
{
    int all = ((pos.h / 2) + (pos.h % 2)) * ((pos.l / 2) + (pos.l % 2));
    int var = 0;
    for (int i = 0; i < pos.h; i = i + 2) {
        for (int j = 0; j < pos.l; j = j + 2)
            (map[i][j] != '*') ? var++ : 1;
        if (var != 0)
            return (1);
    }
    return (0);
}

int check_direction_outside_map(char **map, int direction, info_t pos, pp_t pp)
{
    if (direction == 1) {
        if (pp.y == 0)
            return (1);
    } else if (direction == 2 && (pp.x == pos.l - 1 || pp.x == pos.l - 2)) {
        return (1);
    } else if (direction == 3 && (pp.y == pos.h - 1 || pp.y == pos.h - 2)) {
        return (1);
    } else if (direction == 4 && pp.x == 0) {
        return (1);
    }
    return (0);
}

int check_direction(char **map, int direction, info_t pos, pp_t pp)
{
    if (direction == 1 && map[pp.y - 2][pp.x] == '*') {
        return (0);
    } else if (direction == 2 && map[pp.y][pp.x + 2] == '*') {
        return (0);
    } else if (direction == 3 && map[pp.y + 2][pp.x] == '*') {
        return (0);
    } else if (direction == 4 && map[pp.y][pp.x - 2] == '*') {
        return (0);
    }
    return (1);
}
