/*
** EPITECH PROJECT, 2023
** Epitech  tek 2
** File description:
** symbol
*/

#include "../includes/my.h"
// #include <fcntl.h>
// #include <gelf.h>
// #include <libelf.h>
// #include <stdio.h>
// #include <stdlib.h>

// int symbol()
// {
//     int fd;
//     Elf *e;
//     Elf_Scn *scn;
//   //  GElf_Sym sym;
//     const char *name;
//     size_t shstrndx;

//     /* Open the executable file. */
//     fd = open("my_program", O_RDONLY);
//     if (fd < 0) {
//         printf("Failed to open file\n");
//         return 1;
//     }

//     /* Initialize the ELF library. */
//     if (elf_version(EV_CURRENT) == EV_NONE) {
//         printf("Failed to initialize ELF library\n");
//         return 1;
//     }

//     /* Open the ELF file. */
//     e = elf_begin(fd, ELF_C_READ, NULL);
//     if (e == NULL) {
//         printf("Failed to open ELF file\n");
//         return 1;
//     }

//     /* Get the section header string table index. */
//     if (elf_getshdrstrndx(e, &shstrndx) != 0) {
//         printf("Failed to get section header string table index\n");
//         return 1;
//     }

//     /* Iterate over the sections in the ELF file. */
//     scn = NULL;
//     while ((scn = elf_nextscn(e, scn)) != NULL) {
//         /* Get the section header. */
//         GElf_Shdr shdr;
//         if (gelf_getshdr(scn, &shdr) == NULL) {
//             printf("Failed to get section header\n");
//             continue;
//         }

//         /* Check if the section contains symbols. */
//         if (shdr.sh_type == SHT_SYMTAB || shdr.sh_type == SHT_DYNSYM) {
//             /* Iterate over the symbols in the section. */
//             Elf_Data *data;
//             data = elf_getdata(scn, NULL);
//             if (data == NULL) {
//                 printf("Failed to get section data\n");
//                 continue;
//             }

//             int i;
//             int count = shdr.sh_size / shdr.sh_entsize;
//             for (i = 0; i < count; i++) {
//                 /* Get the symbol. */
//                 GElf_Sym sym;
//                 if (gelf_getsym(data, i, &sym) == NULL) {
//                     printf("Failed to get symbol\n");
//                     continue;
//                 }

//                 /* Get the symbol name. */
//                 name = elf_strptr(e, shstrndx, sym.st_name);
//                 if (name == NULL) {
//                     printf("Failed to get symbol name\n");
//                     continue;
//                 }

//                 /* Print the symbol name and address. */
//                 printf("%s: %lx\n", name, (unsigned long)sym.st_value);
//             }
//         }
//     }

//     /* Close the ELF file. */
//     if (elf_end(e) != 0) {
//         printf("Failed to close ELF file\n");
//         return 1;
//     }

//     /* Close the file descriptor. */
//     if (close(fd) != 0) {
//         printf("Failed to close file\n");
//         return 1;
//     }

//     return 0;
// }

#include <fcntl.h>
#include <gelf.h>
#include <libelf.h>
#include <stdio.h>
#include <stdlib.h>

static symbol_t *symbol_add(long addr, char *name)
{
    symbol_t *new = malloc(sizeof(symbol_t));

    new->addr = addr;
    new->name = name;
    new->next = NULL;
    new->prev = NULL;
    return new;
}

symbol_t *symbol_list_add(symbol_t *list, data_t *data, Elf *elf, int i)
{
    char* name = elf_strptr(elf,
    data->shdr->sh_link, data->symtab[i].st_name);
    symbol_t *new = symbol_add(data->symtab[i].st_value,name);
    symbol_t *tmp = list;

    if (list == NULL)
        return new;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    new->prev = tmp;
    return list;
}

static symbol_t *process_symbol(Elf *elf, data_t *data)
{
    symbol_t *list = NULL;
    int size = data->shdr->sh_size / data->shdr->sh_entsize;

    data->data = elf_getdata(data->scn, NULL);
    data->symtab = (Elf64_Sym *)data->data->d_buf;
    for (int i = 0, st_type = 0; i != size; ++i) {
        st_type = ELF64_ST_TYPE(data->symtab[i].st_info);
        if (st_type == STT_FUNC) {
            list = symbol_list_add(list, data, elf, i);
            if (list == NULL)
                return NULL;
        }
    }
    return list;
}

symbol_t *get_symbols(Elf *elf)
{
    data_t data;

    while ((data.scn = elf_nextscn(elf, data.scn)) != NULL) {
        data.shdr = elf64_getshdr(data.scn);
        if (!data.shdr)
            return NULL;
        if (data.shdr->sh_type == SHT_SYMTAB)
            return process_symbol(elf, &data);
    }
    fprintf(stderr, "Error: no symbol found.\n");
    return NULL;
}
