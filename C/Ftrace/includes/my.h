/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_

    #include "../includes/syscall.h"
    #include "string.h"
    #include "unistd.h"
    #include <fcntl.h>
    #include <gelf.h>
    #include <libelf.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/ptrace.h>
    #include <sys/reg.h>
    #include <sys/types.h>
    #include <sys/user.h>
    #include <sys/wait.h>
    #include <syscall.h>
    #include <unistd.h>

typedef struct data_s {
    Elf64_Shdr *shdr;
    Elf64_Sym *symtab;
    Elf_Scn *scn;
    Elf_Data *data;
} data_t;

typedef struct elf_s {
    Elf *elf;
    Elf_Scn *scn;
    Elf_Data *data;
    int fd;
} elf_t;

typedef struct symbol_s {
    unsigned long addr;
    char *name;
    struct symbol_s *next;
    struct symbol_s *prev;
} symbol_t;

int my_fork(char *command);
int my_fork2(char *command,
pid_t pid, Elf *elf, symbol_t *symbols);
int my_fork3(long res, Elf *elf, symbol_t *symbols,
pid_t pid);
symbol_t *find_call(pid_t pid, symbol_t *list, unsigned long rip);
int entering(Elf *elf, symbol_t *list, int pid);
bool is_entering(long code);
bool is_leaving(long code);

int my_puterror(char *str);
int my_print_help(void);
void my_ifs(struct user_regs_struct regs, char *command);
void my_ifs2(struct user_regs_struct regs, char *command);
void my_ifs3(struct user_regs_struct regs, char *command);

void print_symbol_name_and_address(Elf *e,
Elf_Scn *scn, GElf_Shdr shdr, size_t shstrndx);
void print_symbol_name_and_address_cs(Elf *e,
Elf_Scn *scn, GElf_Shdr shdr, size_t shstrndx);
void print_syscall(struct user_regs_struct regs);

int prepare_elf(const char *path, elf_t *elf_data);
char *get_symbols_data(elf_t *elf_data, long long unsigned int addr,
Elf64_Shdr *shdr);
char *get_symbols_tab(elf_t *elf_data, long long unsigned int addr);

bool init_elf(char *command, Elf **elf);
symbol_t *get_symbols(Elf *elf);

#endif /* !MY_H_ */
