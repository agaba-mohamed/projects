/*
** EPITECH PROJECT, 2022
** my_getnbr
** File description:
** my_getnbr
*/

#include "../include/my.h"

int my_getnbr(char *nbr)
{
    int rslt = 0;
    int len = my_strlen(nbr);
    int var = 1;

    if (nbr[0] == '-') {
        var = -var;
        len = len - 1;
        nbr++;
    }
    for (int i = 0; i != len; i++) {
        if (nbr[i] >= 48 && nbr[i] <= 57)
            rslt = (rslt * 10) + (nbr[i] - 48);
    }
    rslt = rslt * var;
    return (rslt);
}
