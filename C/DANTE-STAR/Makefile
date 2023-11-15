##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## makefile
##

SRC1	=	generator/*.c \
			generalfiles/*.c

SRC2	=	solver/*.c \
			generalfiles/*.c

OBJ	=	$(SRC:.c=.o)

NAME	=	ant

NAME1	=	generator

NAME2	=	solver

EXEC1	=	generator

EXEC2	=	solver

all:	$(NAME)

$(NAME):
	gcc -o $(NAME1)/$(EXEC1) $(SRC1) -g3
	gcc -o $(NAME2)/$(EXEC2) $(SRC2) -g3

clean:
	rm $(NAME1)/$(EXEC1)
	rm $(NAME2)/$(EXEC2)
fclean:	clean

re:	fclean
	gcc -o $(NAME1)/$(EXEC1) $(SRC1) -g3
	gcc -o $(NAME2)/$(EXEC2) $(SRC2) -g3
