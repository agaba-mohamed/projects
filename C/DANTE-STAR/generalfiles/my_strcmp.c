/*
** EPITECH PROJECT, 2022
** my_stcmp
** File description:
** strcmp
*/

#include "../include/my.h"

int my_strcmp(char const *str1, char const *str2)
{
    for (int i = 0; str1[i] == str2[i]; i++) {
        if (str1[i] == '\0') {
            return (1);
        }
    }
    return (0);
}
