<<<<<<< HEAD
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
=======
NAME = cub3D

SRC_MAN =   ./utils/ft_strlen.c \
		 ./Mandatory/rendering/drawing.c ./Mandatory/rendering/raycasting.c ./Mandatory/main.c ./Mandatory/test_pars.c ./Mandatory/rendering/key_event.c

CFLAGS =  -Wall -Wextra -Werror -fsanitize=address -g3 -I /nfs/homes/ysabr/Desktop/minilibx-linux -lXext -lX11 -lm -lz

all : $(NAME)
$(NAME) : $(SRC_MAN)
		cc  $(CFLAGS) $(SRC_MAN) -o $(NAME) -L /nfs/homes/ysabr/Desktop/minilibx-linux -lmlx_Linux

clean :
		rm -rf $(OBJS)

fclean : clean
		rm -rf $(NAME)

re : fclean all

>>>>>>> 0332b7f (start)
