CC = cc -g
INCLUDES = -I./manda/libs -I./manda/srcs
FLAGS = -Wall -Werror -Wextra $(INCLUDES)
NAME = try
SRC =	manda/srcs/parsing/parsing.c 			\
		tester.c 						\
		manda/srcs/parsing/parsing_utils.c	\
		manda/srcs/parsing/parsing_utils2.c	\
		manda/srcs/parsing/floor_ceiling.c 	\
		manda/srcs/mapping/map_parse.c 		\
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

OBJ = $(SRC:.c=.o)

all: $(NAME) clean

#$(NAME): $(OBJ)
#	$(CC) $(FLAGS) -o $(NAME) $(OBJ) 

#%.o: %.c
#	$(CC) $(FLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(FLAGS) -I/usr/include -Imlx -O3 -c $< -o $@

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(SRC) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(OBJ) $(NAME)

re: clean all

.PHONY: all clean fclean re
