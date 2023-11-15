/*
** EPITECH PROJECT, 2023
** B-PSU-400-MAR-4-1-ftrace-mohamed-amine.agaba
** File description:
** my_ifs
*/

#include "../includes/my.h"
#include "../includes/syscall.h"

void my_ifs(struct user_regs_struct regs, char *command)
{
    if (table[regs.orig_rax].nargs == 3) {
        printf("Syscall %s(0x%llx, 0x%llx, 0x%llx) = 0x%llx\n",
            table[regs.orig_rax].name,
            regs.rdi, regs.rsi, regs.rdx, regs.rax);
    } else if (table[regs.orig_rax].nargs == 2) {
        printf("Syscall %s(0x%llx, 0x%llx) = 0x%llx\n",
            table[regs.orig_rax].name,
            regs.rdi, regs.rsi, regs.rax);
    } else
        my_ifs2(regs, command);
}

void my_ifs2(struct user_regs_struct regs, char *command)
{
    if (table[regs.orig_rax].nargs == 1) {
        printf("Syscall %s(0x%llx) = 0x%llx\n", table[regs.orig_rax].name,
            regs.rdi, regs.rax);
    } else if (table[regs.orig_rax].nargs == 4) {
        printf("Syscall  %s(0x%llx, 0x%llx, 0x%llx, 0x%llx) = 0x%llx\n",
            table[regs.orig_rax].name, regs.rdi, regs.rsi, regs.rdx,
            regs.r10, regs.rax);
    } else
        my_ifs3(regs, command);
}

void my_ifs3(struct user_regs_struct regs, char *command)
{
    if (table[regs.orig_rax].nargs == 6) {
        printf("Syscall %s(0x%llx, 0x%llx, 0x%llx, \
        0x%llx, 0x%llx, 0x%llx) = 0x%llx\n",
            table[regs.orig_rax].name,
            regs.rdi, regs.rsi, regs.rdx, regs.r10,
            regs.r8, regs.r9, regs.rax);
    } else if (table[regs.orig_rax].nargs == 5) {
        printf("Syscall %s(0x%llx, 0x%llx, 0x%llx, 0x%llx, 0x%llx) = 0x%llx\n",
            table[regs.orig_rax].name,
            regs.rdi, regs.rsi, regs.rdx,
            regs.r10, regs.r8, regs.rax);
    }
}
