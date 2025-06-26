/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltantin <ltantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:20:16 by ltantin           #+#    #+#             */
/*   Updated: 2025/06/26 16:20:17 by ltantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libparsing.h"

t_pars	*make_parse(void)
{
	t_pars	*parse;
	int		i;

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
	int		i;

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

char	move_to_char(int fd, int i)
{
	char	a;
	int		nline;

	a = ' ';
	nline = 0;
	while (a && (a == ' ' || (a >= '\t' && a <= '\r')))
	{
		a = reader(fd);
		if (!nline && a == '\n')
			nline++;
	}
	if (i && !nline)
		return ('\n');
	return (a);
}
