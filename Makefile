NAME = cub

CC = cc

CFLAGS += #-fsanitize=address

SRC =	main.c util/util.c util/ft_split.c util/get_line.c util/ft_atoi.c \
		texture.0.0.c texture.0.1.c map.c

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

git : 
	make fclean && git add . && git commit -m "PARSING TEXTURES -> NEED TESTING | PARSSING MAP -> JUST STARTED" && git push -f origin master

clean :
	@rm -fr $(OBJ)

fclean : clean
	@rm -fr $(OBJ) $(NAME)

re : fclean $(NAME)
