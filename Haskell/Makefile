SRC =	Pushswap.hs	\

NAME =	pushswap_checker

all :	$(NAME)

$(NAME) :
	ghc -o $(NAME) $(SRC) -g3

clean :
	rm -f *.o
	rm -f *.hi

fclean :	clean
	rm -f $(NAME)

re :	fclean all