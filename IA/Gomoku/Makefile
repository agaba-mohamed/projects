SRC	=  	src/example.cpp \
		src/pisqpipe.cpp
OBJ	=	$(SRC:.o)

NAME	=	pbrain-gomoku-ai

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -o $(NAME) $(SRC) -lpthread
	rm -f $(OBJ)
	rm -f *.o

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all