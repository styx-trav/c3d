CC = cc -g
INCLUDES = -I./libs -I./srcs -Imlx
CFLAGS = -Wall -Werror -Wextra $(INCLUDES)
LDFLAGS = -Lmlx -lmlx -lX11 -lXext -lm
NAME = try
SRC =	srcs/parsing/parsing.c 			\
		srcs/parsing/parsing_utils.c	\
		tester.c 						\
		srcs/parsing/floor_ceiling.c 	\
		srcs/parsing/map_parse.c 		\
		get_next_line.c 				\
		get_next_line_utils.c 			\
		srcs/mapping/mapping.c			\
		srcs/graphic/draw.c 			\
		srcs/graphic/image.c 			\
		srcs/graphic/raycasting.c 		\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(OBJ) $(NAME)
	
re: clean all

.PHONY: all clean fclean re
