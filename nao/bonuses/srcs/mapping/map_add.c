/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naorakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:40:42 by naorakot          #+#    #+#             */
/*   Updated: 2025/06/12 14:40:43 by naorakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmap.h"

static int	passage_way(char **map)
{
	int	i;
	int	end;
	int	col;

	i = 0;
	col = -1;
	while (map && map[i])
	{
		end = ft_strlen(map[i]) - 1;
		if (map[i][end] == '1' && map[i][end - 1] != '0'
			&& map[i][end - 1] != '1' && map[i][end - 1] != ' '
			&& i && map[i + 1])
			col = i;
		i++;
	}
	return (col);
}

static char	*join(char *s1, char *s2, int i)
{
	int		j;
	char	*str;

	j = 0;
	while (s1 && s1[i])
		i++;
	while (s2 && s2[j])
		j++;
	str = malloc(j + i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

static char	**outsiders(char **map, int place)
{
	char	*str;

	map[place - 1][ft_strlen(map[place - 1]) - 1] = '1';
	str = join(map[place -1], "11", 0);
	if (!str)
	{
		free_map(map);
		return (NULL);
	}
	free(map[place -1]);
	map[place -1] = str;
	map[place + 1][ft_strlen(map[place + 1]) - 1] = '1';
	str = join(map[place +1], "11", 0);
	if (!str)
	{
		free_map(map);
		return (NULL);
	}
	free(map[place +1]);
	map[place +1] = str;
	return (map);
}

char	**expand_map(char **map)
{
	int		place;
	char	*str;

	place = passage_way(map);
	if (place == -1)
		return (map);
	map[place][ft_strlen(map[place]) - 1] = '*';
	str = join(map[place], "001", 0);
	if (!str)
	{
		free_map(map);
		return (NULL);
	}
	free(map[place]);
	map[place] = str;
	map = outsiders(map, place);
	return (map);
}
