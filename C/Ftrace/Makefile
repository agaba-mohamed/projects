##
## EPITECH PROJECT, 2023
## B-PSU-400-MAR-4-1-ftrace-oscar.samoun
## File description:
## Makefile
##

SRC	=	src/my_puterror.c \
		src/my_ifs.c \
		src/ftrace.c \
		src/syscall.c \
		src/symbol.c \
		src/symbol2.c \
		src/main.c \
		src/my_fork.c \

OBJ	=	$(SRC:.c=.o)

NAME	=	 ftrace

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -Wall -g -o $(NAME) $(SRC) -lelf
	rm -f $(OBJ)
	rm -f *.o

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
