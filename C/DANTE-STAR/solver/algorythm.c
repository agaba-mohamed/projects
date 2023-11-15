/*
** EPITECH PROJECT, 2022
** algorythm
** File description:
** algorythm
*/

#include "../include/my.h"


int know_type(int **map_int, info_t pos)
{
    if (map_int[pos.h - 2][pos.l - 1] == 0) {
        if (map_int[pos.h - 1][pos.l - 2] == 0) {
            return (2);
        }
    }
    return (1);
}

void check_no_solutions(int poid)
{
    if (poid <= 2) {
        printf("no solution found");
        exit(0);
    }
}

int **made_my_algo(int **map_int, info_t pos)
{
    struct parcours_t *pa = create_par(pos.h - 1, pos.l - 1, NULL, NULL);
    int type = know_type(map_int, pos);
    pp_t my_pos;
    my_pos.x = pos.l - 1;
    my_pos.y = pos.h - 1;
    int poid = 2;
    while (finish(map_int, pos)) {
        while (i_cant_move_anymore(map_int, my_pos, pos)) {
            check_no_solutions(poid);
            my_pos.x = pa->previous->x;
            my_pos.y = pa->previous->y;
            pa = create_par(pa->previous->x, pa->previous->y, pa->previous->previous, NULL);
            poid -= 1;
        }
        int direction = new_direction(map_int, my_pos, pos, type);
        map_int = update_direction(map_int, my_pos, poid, direction);
        my_pos = update_my_pos(my_pos, direction);
        pa = create_par(my_pos.x, my_pos.y, pa, NULL);
        poid++;
    }
    return (map_int);
}

pp_t know_my_direction(int **map_int, pp_t my_pos, info_t pos)
{
    int poid = map_int[my_pos.y][my_pos.x] - 1;
    if (my_pos.x != 0 && map_int[my_pos.y][my_pos.x - 1] == poid) {
        my_pos.x--;
        return (my_pos);
    }
    if (my_pos.x != pos.l - 1) {
        if (map_int[my_pos.y][my_pos.x + 1] == poid) {
            my_pos.x++;
            return (my_pos);
        }
    }
    if (my_pos.y != 0 && map_int[my_pos.y - 1][my_pos.x] == poid) {
        my_pos.y--;
        return (my_pos);
    }
    if (my_pos.y != pos.h - 1) {
        if (map_int[my_pos.y + 1][my_pos.x] == poid) {
            my_pos.y++;
            return (my_pos);
        }
    }
    return (my_pos);
}
