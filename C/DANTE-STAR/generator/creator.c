/*
** EPITECH PROJECT, 2022
** creator.c
** File description:
** create the lab
*/

#include "../include/my.h"

pp_t change_pos(char **map, int direction, info_t pos, pp_t pp)
{
    if (direction == 1) {
        pp.y = pp.y - 2;
        return (pp);
    } else if (direction == 2) {
        pp.x = pp.x + 2;
        return (pp);
    } else if (direction == 3) {
        pp.y = pp.y + 2;
        return (pp);
    } else if (direction == 4) {
        pp.x = pp.x - 2;
        return (pp);
    }
    return (pp);
}

struct parcours_t *create_parcours(int x, int y, struct parcours_t *pre, struct parcours_t *nxt)
{
    struct parcours_t *parcour = malloc(sizeof(struct parcours_t));
    parcour->x = x;
    parcour->y = y;
    parcour->next = nxt;
    parcour->previous = pre;
    if (pre == NULL)
        parcour->next = nxt;
    else if (nxt == NULL)
        pre->next = parcour;
    else {
        pre->next = parcour;
        nxt->previous = parcour;
    }
    return (parcour);
}

struct parcours_t *change_parcour(pp_t actual_pos, int direction, struct parcours_t *parcour)
{
    struct parcours_t *actual = create_parcours(actual_pos.x, actual_pos.y, parcour, NULL);
    return (actual);
}

pp_t go_back(pp_t actual_pos, struct parcours_t *parcour)
{
    actual_pos.x = parcour->previous->x;
    actual_pos.y = parcour->previous->y;
    return (actual_pos);
}

char **generate(char **map, info_t l_h)
{
    map[0][0] = '*';
    struct parcours_t *parcour = create_parcours(0, 0, NULL, NULL);
    pp_t actual_pos;
    actual_pos.x = 0;
    actual_pos.y = 0;
    while (verify_finished(map, l_h)) {
        int direction = generate_numb(1, 4);
        while (check_direction_outside_map(map, direction, l_h, actual_pos))
            direction = generate_numb(1, 4);
        if (check_direction(map, direction, l_h, actual_pos)) {
            map = change_map(map, direction, l_h, actual_pos);
            actual_pos = change_pos(map, direction, l_h, actual_pos);
            parcour = change_parcour(actual_pos, direction, parcour);
        } else if (check_arround(map, direction, l_h, actual_pos) == 0) {
            actual_pos = go_back(actual_pos, parcour);
            parcour = create_parcours(parcour->previous->x, parcour->previous->y, parcour->previous->previous, NULL);
        }
    }
    return (map);
}
