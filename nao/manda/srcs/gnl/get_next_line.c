/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naorakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:48:10 by naorakot          #+#    #+#             */
/*   Updated: 2024/11/06 19:48:49 by naorakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	new_i(char buf[BUFFER_SIZE +1], size_t i)
{
	if (buf == NULL)
		return (0);
	while (buf[i] != '\0' && buf[i] != '\n')
		i++;
	if (buf[i] == '\0' && i < BUFFER_SIZE)
		return (0);
	if (buf[i] == '\n')
		i++;
	if (i >= BUFFER_SIZE || buf[i] == '\0')
		return (0);
	return (i);
}

char	*join(char *str, char *s, char buf[BUFFER_SIZE +1], size_t i)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (s && s[j])
	{
		str[j] = s[j];
		j++;
	}
	while (buf[i + k] != '\0' && buf[i + k] != '\n')
	{
		str[j + k] = buf[i + k];
		k++;
	}
	str[j + k] = buf[i + k];
	if (str[j + k] == '\n')
		str[j + k + 1] = '\0';
	return (str);
}

size_t	add_to_str(char **s, char buf[BUFFER_SIZE +1], size_t i)
{
	char	*str;

	str = malloc((len_str(*s) + lenn(buf, i) + 1) * sizeof(char));
	if (str)
		str = join(str, *s, buf, i);
	if (*s != NULL)
		free(*s);
	if (str && str[0] == '\0')
	{
		free(str);
		str = NULL;
	}
	*s = str;
	if (str == NULL || i + lenn(buf, i) != BUFFER_SIZE
		|| (len_str(str) > 0 && str[len_str(str) - 1] == '\n'))
		return (1);
	return (0);
}

ssize_t	get_previous(char **str, char buf[BUFFER_SIZE +1], size_t *i)
{
	ssize_t	done;

	done = 0;
	if (*i && *i != 0)
	{
		done = add_to_str(str, buf, *i);
		*i = new_i(buf, *i);
	}
	return (done);
}

char	*get_next_line(int fd)
{
	static size_t	i;
	static char		buf[BUFFER_SIZE +1];
	char			*str;
	ssize_t			done;

	str = NULL;
	if (get_previous(&str, buf, &i))
		return (str);
	done = 0;
	while (done < BUFFER_SIZE +1)
		buf[done++] = '\0';
	while (read(fd, buf, BUFFER_SIZE) > 0)
	{
		done = add_to_str(&str, buf, 0);
		i = new_i(buf, 0);
		if (done)
			return (str);
		done = 0;
		while (done < BUFFER_SIZE +1)
			buf[done++] = '\0';
	}
	return (str);
}
