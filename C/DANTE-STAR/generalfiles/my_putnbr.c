/*
** EPITECH PROJECT, 2021
** my_putnbr.c
** File description:
** affiche un int
*/

#include "../include/my.h"

void my_putnbr(int nb)
{
    int z = 0, y = 0;
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb <= 9)
        my_putchar(nb + 48);
    else {
        my_putnbr(nb / 10);
        my_putnbr(nb % 10);
    }
}
