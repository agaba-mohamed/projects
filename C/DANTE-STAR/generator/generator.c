/*
** EPITECH PROJECT, 2022
** generator.c
** File description:
** main of the task
*/

#include "../include/my.h"

char **create_my_map(int l, int h)
{
    char **map = malloc(sizeof(char *) * (h + 1));
    for (int i = 0; i != h + 1; i++)
        map[i] = malloc(sizeof(char) * (l + 1));
    for (int i = 0; i != h; i++) {
        for (int j = 0; j != l; j++)
            map[i][j] = 'X';
        map[i][l] = '\0';
    }
    if (l % 2 == 0 || h % 2 == 0)
        map[h - 1][l - 1] = '*';
    if (l % 2 == 0 && h % 2 == 0)
        map[h - 1][l - 2] = '*';
    map[h] = NULL;
    return (map);
}

char change_map_x(char c)
{
    if (c == 'X') {
        int x = generate_numb_2(0, 100);
        if (x > 8) {
            c = '*';
        }
    }
    return (c);
}

char **change_for_imperfect(char **map, info_t pos)
{
    for (int i = 0; i != pos.h; i++) {
        for (int j = 0; j != pos.l; j++) {
            map[i][j] = change_map_x(map[i][j]);
        }
    }
    if (pos.h != 1 && pos.l != 1) {
        map[pos.h - 1][pos.l - 2] = '*';
        map[pos.h - 2][pos.l - 1] = '*';
    }
    return (map);
}

int create(int ac, char **av)
{
    int largeur = my_getnbr(av[1]);
    int hauteur = my_getnbr(av[2]);
    if (largeur <= 0 || hauteur <= 0)
        return (84);
    char **map = create_my_map(largeur, hauteur);
    info_t pos;
    pos.l = largeur;
    pos.h = hauteur;
    map = generate(map, pos);
    if (ac == 3)
        map = change_for_imperfect(map, pos);
    my_puttab(map);
    return (0);
}

int main (int ac, char **av, char **env)
{
    srand(time(NULL));
    if (ac != 3 && ac != 4) {
        my_putstr("USAGE : ./generator [largeur]");
        my_putstr(" [hauteur] (optional : perfect)\n");
        return (84);
    }
    if (verif_num(av[1]) == 84 || verif_num(av[2]) == 84)
        return (84);
    return (create(ac, av));
}
