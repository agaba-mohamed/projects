/*
** EPITECH PROJECT, 2021
** my_putstr.c
** File description:
** affiche un char*
*/

#include "../include/my.h"

void my_putstr(char *str)
{
    write(1, str, my_strlen(str));
}

void my_putstr_error(char *str)
{
    write(2, str, my_strlen(str));
}
