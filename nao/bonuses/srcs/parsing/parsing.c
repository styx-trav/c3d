#include "libparsing.h"

static char	**get_dir(char c, int fd, t_pars *parse)
{
	char	a;
	char	**res;

	if (!read(fd, &a, 1))
		return (NULL);
	if (c == 'S' && a == 'O')
		res = &(parse->south);
	else if (c == 'N' && a == 'O')
		res = &(parse->north);
	else if (c == 'E' && a == 'A')
		res = &(parse->east);
	else if (c == 'W' && a == 'E')
		res = &(parse->west);
	else
		return (NULL);
	if (*res)
		return (NULL);
	return (res);
}

static char	*get_texture(char c, int fd, t_pars *parse)
{
	char	**s;

	s = get_dir(c, fd, parse);
	if (!s)
		return ("invalid element name");
	c = reader(fd);
	if (c == '\0' || (c != ' ' && c != '\t'))
		return ("invalid element name");
	while (c == ' ' || c == '\t')
		c = reader(fd);
	while (c != '\0' && c != '\n' && c != ' ' && c != '\t')
	{
		*s = add_char(*s, c);
		if (!(*s))
			return ("textures, malloc");
		c = reader(fd);
	}
	return (NULL);
}

static char	*get_element(char c, int fd, t_pars *parse)
{
	if (c == 'S' || c == 'N' || c == 'W' || c == 'E')
		return (get_texture(c, fd, parse));
	if (c == 'F' || c == 'C')
		return (get_color(c, fd, parse));
	return ("invalid element name");
}

static char	*parse_elements(int fd, t_pars *parse)
{
	int		i;
	char	a;
	char	*err;

	i = 0;
	err = NULL;
	while (i != 6)
	{
		if (err)
			a = move_to_char(fd, 0);
		else
			a = move_to_char(fd, i);
		if (a == '\0' || a == '1')
			return ("missing elements of parsing");
		if (a == '\n')
				return ("bad element formatting");
		err = get_element(a, fd, parse);
		if (err && err[0])
			return (err);
		i++;
	}
	return (NULL);
}

t_pars	*parsing_pt1_el(char *file)
{
	t_pars	*parse;
	int		fd;
	char	*err_msg;

	if (!is_cub(file))
	{
		printf("Error\nbad file formatting\n");
		return (NULL);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nopening file\n");
		return (NULL);
	}
	parse = make_parse();
	if (!parse)
		return (NULL);
	parse->fd = fd;
	err_msg = parse_elements(fd, parse);
	if (err_msg)
		return (free_parse(parse, err_msg));
	return (parse);
}
