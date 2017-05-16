/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 18:41:21 by esterna           #+#    #+#             */
/*   Updated: 2017/05/16 16:53:37 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

void		array_setup(char *buf, char *overflow)
{
	ft_memdel((void **)line);
	buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	ft_bzero((void *)buf, sizeof(char) * ft_strlen(buf));
	overflow = (char *)malloc(sizeof(char) * 0);
	ft_bzero((void *)overflow, sizeof(char) * ft_strlen(overflow));
	buf[BUFF_SIZE] = '\0';
}

int			check_buf(char *buf)
{
	int i;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (i == BUFF_SIZE)
		return (0);
	else if (i == 0 && buf[i] == '\n')
		return (-1);
	return (i);
}

void		read_loop(int fd, int *rd, char *buf, char *overflow)
{
	int n;

	while (!(n = check_buf(buf)) && *rd != 0)
	{
		*rd = read(fd, buf, BUFF_SIZE);
		if (!check_buf(buf))
		{
			overflow = ft_strjoin(overflow, buf);
			ft_bzero((void *)buf, sizeof(char) * ft_strlen(buf));
		}
	}
}

void		fill_line(char *line, char *buf, char *overflow, int n)
{
	*line = (char *)malloc(sizeof(char)
			* (ft_strlen(overflow) + ((n >= 0) ? n : 0) + 1));
	*line = ft_strcpy(*line, overflow);
	if (n != -1)
		*line = ft_strjoin(*line, buf);
	(*line)[ft_strlen(overflow) + ((n >= 0) ? n : 0)] = '\0';
	ft_memdel((void **)&buf);
	ft_memdel((void **)&overflow);
}

int			get_next_line(const int fd, char **line)
{
	static int		location;
	int				n;
	int				*rd;
	char			*buf;
	char			*overflow;

	*rd = 1;
	array_setup(buf, overflow);
	if (buf == NULL || overflow == NULL)
		return (0);
	n = read_loop(fd, rd, buf, overflow);
	if ((n == -1 && !*overflow) || (rd == 0 && !ft_strlen(buf)))
	{
		*line = (char *)malloc(sizeof(char) * 1);
		(*line)[0] = '\0';
		ft_memdel((void **)&buf);
		ft_memdel((void **)&overflow);
		if (rd == 0)
			return (0);
		location = lseek(fd, location + 1, SEEK_SET);
		return (1);
	}
	fill_line(*line, buf, overflow, n);
	location = lseek(fd, location + ft_strlen(*line) + 1, SEEK_SET);
	return ((rd == 0 || *line == NULL) ? 0 : 1);
}
