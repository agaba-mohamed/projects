/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** my_puterror
*/

#include "../includes/my.h"

int my_puterror(char *str)
{
    write(2, str, strlen(str));
    return 0;
}

int my_print_help(void)
{
    my_puterror("USAGE: ./ftrace [-s] [-p <pid>|<command>]");
    exit(84);
}
