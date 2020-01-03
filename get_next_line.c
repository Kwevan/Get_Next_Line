/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgouacid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 20:49:15 by kgouacid          #+#    #+#             */
/*   Updated: 2019/12/03 22:22:04 by kgouacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

long		ft_isin(char *haystack, char needle)
{
	long i;

	i = 0;
	while (haystack[i])
	{
		if (haystack[i] == needle)
			return (i);
		i++;
	}
	return (-1);
}

void		ft_memmove(char *s1, char *s2)
{
	long i;

	if (!s2 || !s1)
		return ;
	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}

char		*ft_strndup(char *s, long len)
{
	char *temp;
	long i;

	i = 0;
	temp = NULL;
	temp = (char *)malloc(sizeof(char) * len + 1);
	if (!temp)
		return (NULL);
	temp[len] = '\0';
	while (i < len)
	{
		temp[i] = s[i];
		i++;
	}
	return (temp);
}

int			ft_norm(char **line, char *buf, long pos)
{
	*line = ft_strndup(buf, pos);
	ft_memmove(buf, &buf[pos + 1]);
	return (*line) ? 1 : -1;
}

int			get_next_line(int fd, char **line)
{
	static char		buf[2000000001];
	long			ret;
	long			pos;

	if (read(fd, buf, 0) == -1 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	if ((pos = ft_isin(buf, '\n')) >= 0)
		return (ft_norm(line, buf, pos));
	while (((pos = ft_strlen(buf)) != -1)
		&& (ret = read(fd, &buf[pos], BUFFER_SIZE)) != -1)
	{
		buf[ret + pos] = '\0';
		if ((pos = ft_isin(buf, '\n')) >= 0)
			return (ft_norm(line, buf, pos));
		if (ret == 0)
		{
			*line = ft_strndup(buf, ft_strlen(buf));
			buf[0] = 0;
			return (*line) ? 0 : -1;
		}
	}
	return (-1);
}
