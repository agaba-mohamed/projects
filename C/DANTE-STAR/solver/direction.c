/*
** EPITECH PROJECT, 2022
** direction
** File description:
** direction
*/

#include "../include/my.h"

int got_a_dir(int type)
{
    if (type == 1) {
        int dir = 1 + rand() % 4;
        return (dir);
    }
    int dir = 1 + rand() % 10;
    if (dir > 0 && dir <= 4)
        dir = 1;
    if (dir > 4 && dir <= 8)
        dir = 4;
    if (dir == 9)
        dir = 3;
    if (dir == 10)
        dir = 2;
    return (dir);
}

int new_direction(int **map_int, pp_t my_pos, info_t info, int type)
{
    int dir = got_a_dir(type);
    if (dir == 1)
        if (my_pos.y == 0 || map_int[my_pos.y - 1][my_pos.x] != 0)
            return (new_direction(map_int, my_pos, info, type));
    if (dir == 2)
        if (my_pos.x == info.l - 1|| map_int[my_pos.y][my_pos.x + 1] != 0)
            return (new_direction(map_int, my_pos, info, type));
    if (dir == 3)
        if (my_pos.y == info.h - 1 || map_int[my_pos.y + 1][my_pos.x] != 0)
            return (new_direction(map_int, my_pos, info, type));
    if (dir == 4)
        if (my_pos.x == 0 || map_int[my_pos.y][my_pos.x - 1] != 0)
            return (new_direction(map_int, my_pos, info, type));
    return (dir);
}

int i_cant_move_anymore(int **map_int, pp_t my_pos, info_t pos)
{
    int var = 4;
    if (my_pos.x == 0 || map_int[my_pos.y][my_pos.x - 1] != 0) {
        var -= 1;
    }
    if (my_pos.x == pos.l - 1 || map_int[my_pos.y][my_pos.x + 1] != 0) {
        var -= 1;
    }
    if (my_pos.y == 0 || map_int[my_pos.y - 1][my_pos.x] != 0) {
        var -= 1;
    }
    if (my_pos.y == pos.h - 1 || map_int[my_pos.y + 1][my_pos.x] != 0) {
        var -= 1;
    }
    if (var < 1)
        return (1);
    return (0);
}

int **update_direction(int **map_int, pp_t my_pos, int poid, int direction)
{
    if (direction == 1) {
        map_int[my_pos.y - 1][my_pos.x] = poid;
        return (map_int);
    }
    if (direction == 2) {
        map_int[my_pos.y][my_pos.x + 1] = poid;
        return (map_int);
    }
    if (direction == 3) {
        map_int[my_pos.y + 1][my_pos.x] = poid;
        return (map_int);
    }
    if (direction == 4) {
        map_int[my_pos.y][my_pos.x - 1] = poid;
        return (map_int);
    }
}

pp_t update_my_pos(pp_t my_pos, int direction)
{
    if (direction == 1) {
        my_pos.y = my_pos.y - 1;
    }
    if (direction == 2) {
        my_pos.x = my_pos.x + 1;
    }
    if (direction == 3) {
        my_pos.y = my_pos.y + 1;
    }
    if (direction == 4) {
        my_pos.x = my_pos.x - 1;
    }
    return (my_pos);    
}
