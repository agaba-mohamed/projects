/*
** EPITECH PROJECT, 2022
** my_str_to_word_array
** File description:
** transforme un char * en char ** a chaque espace qu'il croise
*/

#include "../include/my.h"

char **my_str_to_word_array(char *str)
{
    int x = 0, y = 1, k = 0;
    for (x = 0; str[x] != '\n' && str[x] != '\0'; x++);
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == '\n')
            y++;
    char **array = malloc(sizeof(char *) * (y + 1));
    for (int i = 0; i != y; i++)
        array[i] = malloc(sizeof(char) * (x + 1));
    for (int i = 0; i != y; i++) {
        for (int j = 0; j != x; j++) {
            array[i][j] = str[k];
            k++;
        }
        array[i][x] = '\0';
        k++;
    }
    array[y] = NULL;
    return (array);
}
