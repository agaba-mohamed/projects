/*
** EPITECH PROJECT, 2022
** func_buffer
** File description:
** func_buffer
*/

#include "../include/my.h"

char *func_buffer(char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        my_putstr_error("Invalid file.\n");
        exit (84);
    }
    struct stat buf;
    int status;
    status = stat(filepath, &buf);
    char *buffer = malloc(sizeof(char) * (buf.st_size + 1));
    int red = read(fd, buffer, buf.st_size);
    buffer[buf.st_size] = '\0';
    close(fd);
    return (buffer);
}
