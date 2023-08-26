# NAME = cub3D

# NAME2 = cub3d_bonus

# SRC_MAN =  ./Mandatory/main.c ./Mandatory/rendering/drawing.c \
# 			./Mandatory/rendering/raycasting.c  ./Mandatory/test_pars.c \
# 			./Mandatory/rendering/key_event.c \

# SRC_BON = ./bonus/main.c ./bonus/test_pars.c ./bonus/rendering_bonus/drawing.c ./bonus/rendering_bonus/raycasting.c \
# 			./bonus/rendering_bonus/key_event.c 

# CFLAGS =  -Wall -Wextra -Werror -fsanitize=address -g3 -I /nfs/homes/ysabr/Desktop/minilibx-linux -lXext -lX11 -lm -lz

# all : $(NAME)

# $(NAME) : $(SRC_MAN)
# 		cc  $(CFLAGS) $(SRC_MAN) -o $(NAME) -L /nfs/homes/ysabr/Desktop/minilibx-linux -lmlx_Linux

# bonus : $(NAME2)

# $(NAME2) : $(SRC_BON)
# 		  cc $(CFLAGS) $(SRC_BON) -o $(NAME2) -L /nfs/homes/ysabr/Desktop/minilibx-linux -lmlx_Linux

# clean :
# 		rm -rf $(OBJS)

# fclean : clean
# 		rm -rf $(NAME) $(NAME2)

# re : fclean all


#---------------------------------YACHAAB------------------------------------------------------------#
#---------------------------------YACHAAB------------------------------------------------------------#
#---------------------------------YACHAAB------------------------------------------------------------#
#---------------------------------YACHAAB------------------------------------------------------------#
#---------------------------------YACHAAB------------------------------------------------------------#
NAME = cub3D

BONUS = cub3D_bonus
CC = cc

MLX_DIR = /nfs/homes/yachaab/Desktop/minilibx-linux

MLX_LIB = -L $(MLX_DIR) -lmlx -lXext -lX11 -lm

CFLAGS +=  -Werror -Wall -Wextra -fsanitize=address -g3 

SRC_PAR =	parse.c util/util.c util/ft_split.c util/get_line.c util/ft_atoi.c \
			texture.0.0.c texture.0.1.c map.c util/ft_bspace.c setup.c \
			

SRC_REN = 	main.c rendering/drawing.c \
			rendering/raycasting.c \
			rendering/key_event.c \

SRC_BON = main.c  rendering_bonus/drawing.c rendering_bonus/raycasting.c \
			rendering_bonus/key_event.c 

SRC_PAR_PRE = $(addprefix parssing/, $(SRC_PAR))

SRC_REN_PRE = $(addprefix Mandatory/, $(SRC_REN))

SRC_BON_PRE = $(addprefix bonus/, $(SRC_BON))

OBJ_PAR = $(SRC_PAR_PRE:.c=.o)

OBJ_REN = $(SRC_REN_PRE:.c=.o)

OBJ_BON = $(SRC_BON_PRE:.c=.o)

all : $(NAME)

bonus : $(BONUS)

$(NAME) : $(OBJ_REN) $(OBJ_PAR) 
	@$(CC) $(CFLAGS) -o $@ $^ $(MLX_LIB)

$(BONUS) : $(OBJ_BON) $(OBJ_PAR) 
	@$(CC) $(CFLAGS) -o $@ $^ $(MLX_LIB)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

git : 
	make fclean && git add . && git commit -m "MERGING" && git push -f origin master

clean :
	@rm -fr $(OBJ_PAR) $(OBJ_REN) $(OBJ_BON)

fclean : clean
	@rm -fr $(OBJ_PAR) $(OBJ_BON) $(OBJ_REN) $(NAME) $(BONUS)

re : fclean $(NAME)

#---------------------------------YACHAAB------------------------------------------------------------#
#---------------------------------YACHAAB------------------------------------------------------------#
#---------------------------------YACHAAB------------------------------------------------------------#
#---------------------------------YACHAAB------------------------------------------------------------#
#---------------------------------YACHAAB------------------------------------------------------------#
#---------------------------------YACHAAB------------------------------------------------------------#




# NAME = cub

# BONUS = cub3d_bonus

# CC = cc

# #OBJ_DIR = objects/

# CFLAGS += #-fsanitize=address -g3

# SRC_PAR =	main.c util/util.c util/ft_split.c util/get_line.c util/ft_atoi.c \
# 			texture.0.0.c texture.0.1.c map.c

# SRC_REN = 	rendering/drawing.c rendering/raycasting.c main.c test_pars.c rendering/key_event.c

# SRC_BON = 	main.c test_pars.c rendering_bonus/drawing.c rendering_bonus/raycasting.c \
# 			rendering_bonus/key_event.c 

# SRC_PAR_PRE = $(addprefix parssing/, $(SRC_PAR))

# SRC_REN_PRE = $(addprefix Mandatory/, $(SRC_REN))

# SRC_BON_PRE = $(addprefix bonus/, $(SRC_BON))

# OBJ_PAR = $(SRC_PAR_PRE:.c=.o)
# OBJ_REN = $(SRC_REN_PRE:.c=.o)
# OBJ_BON = $(SRC_BON_PRE:.c=.o)

# all : $(NAME)

# bonus : $(BONUS)

# $(NAME) : $(OBJ_PAR) $(OBJ_REN) 
# 	@$(CC) $(CFLAGS) -o $@ $^ -L /nfs/homes/ysabr/Desktop/minilibx-linux -lmlx_Linux

# $(BONUS) : $(OBJ_BON)
# 	@$(CC) $(CFLAGS) -o $@ $^ -L /nfs/homes/ysabr/Desktop/minilibx-linux -lmlx_Linux

# %.o : %.c
# 	@$(CC) $(CFLAGS) -c $< -o $@

# git : 
# 	make fclean && git add . && git commit -m "PARSING TEXTURES -> NEED TESTING | PARSSING MAP -> JUST STARTED" && git push -f origin master

# clean :
# 	@rm -fr $(OBJ_PAR) $(OBJ_REN) $(OBJ_BON)

# fclean : clean
# 	@rm -fr $(OBJ_PAR) $(OBJ_REN) $(OBJ_BON) $(NAME) $(BONUS)

# re : fclean $(NAME) $(BONUS)