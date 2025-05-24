#include "libparsing.h"

t_pars	*make_parse(void)
{
	t_pars	*parse;
	int	i;

	parse = (t_pars *)malloc(sizeof(t_pars));
	if (!parse)
	{
		perror("parsing_pt1, malloc");
		return (NULL);
	}
	parse->south = NULL;
	parse->east = NULL;
	parse->west = NULL;
	parse->north = NULL;
	i = 0;
	while (i < 4)
	{
		parse->floor[i] = 0;
		parse->ceiling[i] = 0;
		i++;
	}
	return (parse);
}

t_pars	*free_parse(t_pars *parse, char *err_msg)
{
	if (parse->fd != -1)
		close(parse->fd);
	if (err_msg)
	{
		write(2, "Error\n", 6);
		printf("%s\n", err_msg);
	}
	if (parse->south)
	{
		printf("south texture :: %s\n", parse->south);
		free(parse->south);
	}
	if (parse->east)
	{
		printf("east texture :: %s\n", parse->east);
		free(parse->east);
	}
	if (parse->west)
	{
		printf("west texture :: %s\n", parse->west);
		free(parse->west);
	}
	if (parse->north)
	{
		printf("north texture :: %s\n", parse->north);
		free(parse->north);
	}
	if (parse->floor[0])
		printf("floor color : %d.%d.%d\n", parse->floor[1], parse->floor[2], parse->floor[3]);
	if (parse->ceiling[0])
		printf("ceiling color : %d.%d.%d\n", parse->ceiling[1], parse->ceiling[2], parse->ceiling[3]);
	free(parse);
	return (NULL);
}

int	len(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*add_char(char *str, char c)
{
	char	*s;
	int	i;

	s = malloc(len(str) + 2);
	if (!s)
		return (NULL);
	i = 0;
	while (str && str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i] = c;
	s[i + 1] = '\0';
	if (str)
		free(str);
	return (s);
}

char	reader(int fd)
{
	char	a;

	if (!read(fd, &a, 1))
		return ('\0');
	return (a);
}

char	move_to_char(int fd)
{
	char	a;

	a = ' ';
	while (a && (a == ' ' || (a >= '\t' && a <= '\r')))
		a = reader(fd);
	return (a);
}
