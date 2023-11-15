/*
** EPITECH PROJECT, 2021
** my_revstr
** File description:
** Miroir d'un char *
*/

#include "../include/my.h"

char *my_revstr(char *str)
{
    int i = my_strlen(str) - 1;
    char c;
    for (int j = 0; j < (i / 2) + 1; j++) {
        c = str[i - j];
        str[i - j] = str[j];
        str[j] = c;
    }
    return (str);
}
