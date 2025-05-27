CC = cc -g
INCLUDES = -I./libs -I./srcs
FLAGS = -Wall -Werror -Wextra $(INCLUDES)
NAME = try
SRC =	srcs/parsing/parsing.c 			\
		srcs/parsing/parsing_utils.c	\
		srcs/parsing/parsing_utils2.c	\
		tester.c 						\
		srcs/parsing/floor_ceiling.c 	\
		srcs/mapping/map_parse.c 		\
		srcs/mapping/map_parse_utils.c 		\
		srcs/gnl/get_next_line.c 				\
		srcs/gnl/get_next_line_utils.c 			\
		srcs/mapping/mapping.c			

OBJ = $(SRC:.c=.o)

all: $(NAME) clean

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) 

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(OBJ) $(NAME)
	
re: clean all

.PHONY: all clean fclean re
