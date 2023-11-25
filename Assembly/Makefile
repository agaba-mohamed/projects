##
## EPITECH PROJECT, 2023
## Assembly
## File description:
## Makefile
##

ASM = nasm

ASFLAGS = -f elf64

SRC =   src/strlen.asm \
		src/strchr.asm \
		src/strcmp.asm \
		src/strncmp.asm \
		src/memset.asm \
		src/memcpy.asm \

OBJ = $(SRC:.asm=.o)

NAME = libasm.so

CC = gcc

CFLAGS = -shared

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -nostdlib -fPIC -o $(NAME) $(OBJ)
	$(CC) -fno-builtin minilib.c libasm.so -o minilib

%.o: %.asm
	$(ASM) $(ASFLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all