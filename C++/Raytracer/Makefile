##
## EPITECH PROJECT, 2023
## B-PDG-300-MAR-3-1-PDGRUSH3-matis.levrault [WSL: fedora]
## File description:
## Makefile
##

SRC 	=	src/*.cpp

OBJ 	=	$(SRC:.cpp=.o)

NAME 	=	raytracer

all:	$(NAME)

$(NAME):
	g++ -o $(NAME) $(SRC) -lconfig++ -O3

clean:
	rm -f $(NAME)

fclean:	clean

re: 	fclean all
