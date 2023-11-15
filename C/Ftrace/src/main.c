/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** main
*/

#include "../includes/my.h"

int main(int ac, char **av)
{
    if (ac < 2 || (strncmp(av[1], "--help", 6) == 0))
        my_print_help();
    char *command = av[1];

    my_fork(command);
    return 0;
}
