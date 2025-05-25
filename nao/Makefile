CC=cc
FLAGS=-Wall -Werror -Wextra
NAME=try
OBJ=parsing.c parsing_utils.c tester.c floor_ceiling.c map_parse.c get_next_line.c get_next_line_utils.c mapping.c

all: $(NAME)

$(NAME): $(OBJ) libparsing.h libmap.h
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) 

clean:
	rm -f try
	
re: clean all

.PHONY: all clean re
