CC = cc -g
INCLUDES = -I./manda/libs -I./manda/srcs
FLAGS = -Wall -Werror -Wextra
NAME = cub3D
B_NAME = cub3D_bonus
SRC =	manda/srcs/parsing/parsing.c 			\
		manda/main.c 						\
		manda/srcs/parsing/parsing_utils.c	\
		manda/srcs/parsing/parsing_utils2.c	\
		manda/srcs/parsing/floor_ceiling.c 	\
		manda/srcs/mapping/map_parse.c 		\
		manda/srcs/mapping/adjust.c 		\
		manda/srcs/mapping/map_parse_utils.c 		\
		manda/srcs/gnl/get_next_line.c 				\
		manda/srcs/gnl/get_next_line_utils.c 			\
		manda/srcs/init/init.c 				\
		manda/srcs/init/init_utils.c 			\
		manda/srcs/mapping/mapping.c			\
		manda/srcs/graphic/hooks.c			\
		manda/srcs/graphic/player.c			\
		manda/srcs/graphic/disp_utils.c			\
		manda/srcs/graphic/rays.c				\
		manda/srcs/graphic/draw.c				\
		manda/srcs/utils.c					\
		manda/srcs/graphic/walls.c
BSRC = 	bonuses/srcs/parsing/parsing.c 			\
		bonuses/main.c 						\
		bonuses/srcs/parsing/parsing_utils.c	\
		bonuses/srcs/parsing/parsing_utils2.c	\
		bonuses/srcs/parsing/floor_ceiling.c 	\
		bonuses/srcs/mapping/map_parse.c 		\
		bonuses/srcs/mapping/map_parse_utils.c 		\
		bonuses/srcs/gnl/get_next_line.c 				\
		bonuses/srcs/gnl/get_next_line_utils.c 			\
		bonuses/srcs/init/init.c 				\
		bonuses/srcs/init/init_utils.c 			\
		bonuses/srcs/mapping/mapping.c			\
		bonuses/srcs/mapping/adjust.c			\
		bonuses/srcs/mapping/mapping_utils.c			\
		bonuses/srcs/mapping/map_add.c			\
		bonuses/srcs/graphic/hooks.c			\
		bonuses/srcs/graphic/player.c			\
		bonuses/srcs/graphic/disp_utils.c			\
		bonuses/srcs/graphic/rays.c				\
		bonuses/srcs/graphic/draw.c				\
		bonuses/srcs/utils.c					\
		bonuses/srcs/graphic/walls.c			\
		bonuses/srcs/graphic/sprite.c			\
		bonuses/srcs/graphic/sprite_utils.c			\
		bonuses/srcs/graphic/draw_sprite.c			\
		bonuses/srcs/minimap/minimap.c\
		bonuses/srcs/minimap/player_arrow.c
		
OBJ = $(SRC:.c=.o)

B_OBJ = $(BSRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -I/usr/include -Imlx -O3 -c $< -o $@

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(INCLUDES) $(SRC) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(OBJ) $(NAME)

$(B_NAME): $(BSRC)
	$(CC) $(FLAGS) -I./bonuses/srcs -I./bonuses/libs $(BSRC) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(B_NAME)

bonus: $(B_NAME)

b_clean:
	rm -f $(B_OBJ)

b_fclean:
	rm -f $(B_OBJ) $(B_NAME)

re: fclean all

rbonus: b_fclean bonus

.PHONY: all clean fclean re bonus b_clean c_fclean rbonus
