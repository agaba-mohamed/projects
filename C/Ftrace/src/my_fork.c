/*
** EPITECH PROJECT, 2023
** B-PSU-400-MAR-4-1-ftrace-mohamed-amine.agaba
** File description:
** my_fork
*/

#include "../includes/my.h"

int my_fork(char *command)
{
    Elf *elf;
    symbol_t *symbols = NULL;
    init_elf(command, &elf);
    symbols = get_symbols(elf);
    pid_t pid = fork();
    if (pid == -1)
        my_puterror("fork");
    if (pid == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execvp(command, &command);
        exit(EXIT_FAILURE);
    } else {
        my_fork2(command, pid, elf, symbols);
    }
    return pid;
}

int my_fork2(char *command,
pid_t pid, Elf *elf, symbol_t *symbols)
{
    int status = 0;
    long res = 0;
    struct user_regs_struct regs;
    wait(&status);
    ptrace(PTRACE_SETOPTIONS, pid, NULL, PTRACE_O_TRACEEXIT);
    while (!WIFEXITED(status)) {
        ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
        wait(&status);
        if (WIFEXITED(status))
            break;
        ptrace(PTRACE_GETREGS, pid, NULL, &regs);
        res = ptrace(PTRACE_PEEKTEXT, pid, regs.rip, NULL);
        if (my_fork3(res, elf, symbols, pid) == -1)
            my_ifs(regs, command);
    }
    return 0;
}

int my_fork3(long res, Elf *elf, symbol_t *symbols,
pid_t pid)
{
    if (is_entering(res)) {
        entering(elf, symbols, pid);
        printf("Entering function at \n");
    } else if (is_leaving(res)) {
        printf("Leaving function \n");
    } else
        return -1;
    return 0;
}
