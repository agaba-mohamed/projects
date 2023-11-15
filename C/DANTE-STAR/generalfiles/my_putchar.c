/*
** EPITECH PROJECT, 2021
** my_putchar.c
** File description:
** Afficher un char
*/

#include "../include/my.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}
