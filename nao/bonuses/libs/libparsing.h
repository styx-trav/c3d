#ifndef LIBPARSING_H
# define LIBPARSING_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "get_next_line.h"

typedef struct s_pars
{
	char	*south;
	char	*north;
	char	*east;
	char	*west;
	int		floor[4];
	int		ceiling[4];
	int		fd;
}		t_pars;

//from parsing/parsing_utils.c
t_pars	*make_parse(void);
int		len(char *str);
char	*add_char(char *str, char c);
char	reader(int fd);
char	move_to_char(int fd, int i);

//from parsing/parsing_utils2.c
t_pars	*free_parse(t_pars *parse, char *err_msg);
int		is_cub(char *str);

//from parsing/parsing.c
t_pars	*parsing_pt1_el(char *file);

//from parsing/floor_ceiling.c
char	*get_color(char c, int fd, t_pars *parse);

//from tester.c
void	free_map(char **map);

//from mapping/map_parse.c
char	**make_map(t_pars *parse);
int		last_map_check(char **map);

//from mapping/map_parse_utils.c
int		instr(char *str, char a);
int		is_empty(char *line);
char	**map_errors(char a, char **map);
int		check_door(char **map, int i, int j);

//from adjust.c
char	**adjust_map(char **map);

#endif
