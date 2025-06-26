/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltantin <ltantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:20:30 by ltantin           #+#    #+#             */
/*   Updated: 2025/06/26 16:20:31 by ltantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmap.h"

static void	size_map(t_maps *map, int i, int j, char **maps)
{
	if (maps[i][j] == '!' || maps[i][j] == '?'
		|| maps[i][j] == '*' || maps[i][j] == 'S')
		return ;
	if (maps[i][j] == '1')
	{
		if_wall(map, i, j);
		return ;
	}
	if (maps[i][j] == '2')
		maps[i][j] = '?';
	else if (maps[i][j] == '3')
		maps[i][j] = '*';
	else if (maps[i][j] == 'M')
		maps[i][j] = 'S' ;
	else
		maps[i][j] = '!';
	size_map(map, i +1, j, maps);
	size_map(map, i -1, j, maps);
	size_map(map, i, j +1, maps);
	size_map(map, i, j -1, maps);
}

static char	*inloop(char *map, int min, int max)
{
	char	*s;
	int		i;

	i = 0;
	s = malloc(max - min + 2);
	if (!s)
		return (NULL);
	while (map[min + i] != '\n' && min + i <= max)
	{
		s[i] = map[min + i];
		i++;
	}
	while (min + i <= max)
	{
		s[i] = ' ';
		i++;
	}
	s[i] = '\0';
	return (s);
}

static char	**reduce_map(char **map, t_maps *mapp)
{
	char	**nmap;
	int		i;

	nmap = malloc(sizeof(char *) * (mapp->maxi - mapp->mini + 2));
	if (!nmap)
		return (NULL);
	i = 0;
	while (mapp->mini + i <= mapp->maxi)
	{
		nmap[i] = inloop(map[mapp->mini + i], mapp->minj, mapp->maxj);
		if (!nmap[i])
		{
			free_map(nmap);
			return (NULL);
		}
		i++;
	}
	nmap[i] = NULL;
	return (nmap);
}

static void	mapp_set_up(t_maps *mapp, char **map)
{
	get_player(mapp, map);
	mapp->mini = -1;
	mapp->minj = -1;
	mapp->maxi = -1;
	mapp->maxj = -1;
	mapp->dir = map[mapp->i][mapp->j];
	size_map(mapp, mapp->i, mapp->j, map);
}

t_maps	*get_map(char **map)
{
	t_maps	*mapp;

	if (!map)
		return (NULL);
	mapp = (t_maps *)malloc(sizeof(t_maps));
	if (!mapp)
		return (NULL);
	mapp_set_up(mapp, map);
	mapp->map = reduce_map(map, mapp);
	free_map(map);
	mapp->map = expand_map(mapp->map);
	if (!mapp->map)
	{
		perror("map conversion malloc");
		free(mapp);
		return (NULL);
	}
	mapp->i = mapp->i - mapp->mini;
	mapp->j = mapp->j - mapp->minj;
	return (mapp);
}
