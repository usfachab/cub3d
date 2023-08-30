CC			=	cc

NAME		=	cub3D

BONUS		=	cub3D_bonus

MLX_DIR		=	/nfs/homes/yachaab/Desktop/minilibx-linux

MLX_LIB		=	-L $(MLX_DIR) -lmlx -lXext -lX11 -lm

CFLAGS		= 	-Werror -Wall -Wextra -fsanitize=address -g3

SRC_PAR		=	parse.c texture.0.0.c texture.0.1.c map.0.0.c map.0.1.c \
				util/ft_split.c util/util.0.0.c util/util.0.1.c util/util.0.2.c
			

SRC_REN		= 	main.c rendering/drawing.c \
				rendering/raycasting.c \
				rendering/key_event.c \

SRC_BON		=	main.c  rendering/drawing.c rendering/raycasting.c \
				rendering/key_event.c parssing/parse.c parssing/texture.0.0.c \
				parssing/texture.0.1.c parssing/map.0.0.c parssing/map.0.1.c \
				parssing/util/ft_split.c parssing/util/util.0.0.c \
				parssing/util/util.0.1.c parssing/util/util.0.2.c parssing/anim_setup.c

SRC_PAR_PRE	= 	$(addprefix Mandatory/parssing/, $(SRC_PAR))

SRC_REN_PRE = 	$(addprefix Mandatory/, $(SRC_REN))

SRC_BON_PRE = 	$(addprefix bonus/, $(SRC_BON))

OBJ_PAR 	= 	$(SRC_PAR_PRE:.c=.o)

OBJ_REN 	= 	$(SRC_REN_PRE:.c=.o)

OBJ_BON 	= 	$(SRC_BON_PRE:.c=.o)

all : $(NAME)

bonus : $(BONUS)

$(NAME) : $(OBJ_PAR)  $(OBJ_REN)
	@$(CC) $(CFLAGS) -o $@ $^ $(MLX_LIB)

$(BONUS) : $(OBJ_BON)
	@$(CC) $(CFLAGS) -o $@ $^ $(MLX_LIB)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

git : 
	make fclean && git add . && git commit -m "ADD DOOR TEXTURE | BONUS -> OK | NORM PARSSING -> OK | ON TESTING PHASE" && git push -f origin master

clean :
	@rm -fr $(OBJ_PAR) $(OBJ_REN) $(OBJ_BON)

fclean : clean
	@rm -fr $(OBJ_PAR) $(OBJ_BON) $(OBJ_REN) $(NAME) $(BONUS)

re : fclean $(NAME)
