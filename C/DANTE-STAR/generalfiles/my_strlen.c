/*
** EPITECH PROJECT, 2021
** mystrlen.c
** File description:
** Longeur d'un char*
*/

int my_strlen(char const *str)
{
    int n = 0;
    while (str[n] != '\0') {
        n = n + 1;
    }
    return (n);
}
