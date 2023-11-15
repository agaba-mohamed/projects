/*
** EPITECH PROJECT, 2022
** my_puttab.c
** File description:
** disp a char **
*/

#include "../include/my.h"

int my_puttab(char **tab)
{
    for (int i = 0; tab[i] != NULL; i++) {
        my_putstr(tab[i]);
        if (tab[i + 1] != NULL)
            my_putstr("\n");
    }
    return (0);
}