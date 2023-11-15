/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** ftrace
*/

#include "../includes/my.h"

symbol_t *find_call(pid_t pid, symbol_t *list, unsigned long rip)
{
    symbol_t *tmp = list;

    while (tmp != NULL) {
        if (rip == tmp->addr && tmp->name[0] != '_') {
            if (rip == tmp->addr && tmp->name[0] != '_') {
                return tmp;
            }
            tmp = tmp->next;
        }
    }
    return NULL;
}

int entering(Elf *elf, symbol_t *list, int pid)
{
    symbol_t *symbol = NULL;

    if (symbol != NULL)
        printf("Entering function %s at %#lx\n", symbol->name, symbol->addr);
    return 0;
}

bool is_entering(long code)
{
    if (((code & 0xFF) == 0xe8) || ((code & 0xFF) == 0x3D)) {
        return true;
    }
    return false;
}

bool is_leaving(long code)
{
    if ((code & 0xFF) == 0xc3)
        return true;
    return false;
}
