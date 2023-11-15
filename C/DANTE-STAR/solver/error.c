/*
** EPITECH PROJECT, 2022
** error
** File description:
** error
*/

#include "../include/my.h"

int check_error(int ac, char **av)
{
    if (ac < 2) {
        my_putstr_error("Not enought arguments.\n");
        return (1);
    }
    if (ac > 2) {
        my_putstr_error("Too many arguments.\n");
        return (1);
    }
    char *map = func_buffer(av[1]);
    for (int i = 0; map[i] != '\0'; i++) {
        if (map[i] != '\n' && map[i] != 'X' && map[i] != '*') {
            my_putstr_error("Invalid map.\n");
            return (1);
        }
    }
    return (0);
}

struct parcours_t *create_par(int x, int y, struct parcours_t *previous, struct  parcours_t *next)
{
    struct parcours_t *parcour = malloc(sizeof(struct parcours_t));
    parcour->x = x;
    parcour->y = y;
    parcour->next = next;
    parcour->previous = previous;
    if (previous == NULL)
        parcour->next = next;
    else if (next == NULL)
        previous->next = parcour;
    else {
        previous->next = parcour;
        next->previous = parcour;
    }
    return (parcour);
}

char **load_2d_array_from_file(char *filepath)
{
    char *str = func_buffer(filepath);
    char **map = my_str_to_word_array(str);
    return (map);
}

info_t know_info(char **map)
{
    info_t pos;
    for (pos.h = 0; map[pos.h] != NULL; pos.h++);
    for (pos.l = 0; map[0][pos.l] != '\0'; pos.l++);
    return (pos);
}

int finish(int **map, info_t info)
{
    int j = 0;
    for (int i = 0; i != info.h; j++) {
        if (map[i][j] == 0)
            return (1);
        if (j == info.h) {
            j = -1;
            i++;
        }
    }
    return (0);
}
