#ifndef LIBPARSING_H
# define LIBPARSING_H
# include <unistd.h>
# include <stdlib.h>

typedef struct s_pars
{
	char	*south;
	char	*north;
	char	*east;
	char	*west;
	int	floor[4];
	int	ceiling[4];
}		t_pars;

//from parsing_utils.c
t_pars	*make_parse(void);
t_pars	*free_parse(t_pars *parse, char *err_msg, int fd);
int	len(char *str);
char	*add_char(char *str, char c);
char	move_to_char(int fd);

//from parsing.c
t_pars	*parsing_pt1_el(char *file);

#endif
