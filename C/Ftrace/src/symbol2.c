/*
** EPITECH PROJECT, 2023
** Epitech  tek 2
** File description:
** symbol2
*/

#include "../includes/my.h"
#include <fcntl.h>
#include <gelf.h>
#include <libelf.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long get_addr(symbol_t *list, char *name)
{
    symbol_t *tmp = list;

    while (tmp != NULL) {
        if (!strcmp(tmp->name, name))
            return tmp->addr;
        tmp = tmp->next;
    }
    return 0;
}

bool init_elf(char *command, Elf **elf)
{
    int fd = open(command, O_RDONLY, NULL);

    if (fd < 0)
        return (84);
    if (elf_version(EV_CURRENT) == EV_NONE)
        exit(84);
    *elf = elf_begin(fd, ELF_C_READ, NULL);
    if (*elf == NULL)
        exit(84);
    if (gelf_getclass(*elf) != ELFCLASS64) {

        if (elf_kind(*elf) != ELF_K_ELF) {
            printf("Not an elf file\n");
            exit(84);
        }
        return false;
    }
    return false;
}
