/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 18:41:21 by esterna           #+#    #+#             */
/*   Updated: 2017/05/23 16:11:02 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

void		array_setup(char **line, char *buf, char *overflow, int location)
{
	if (location > 0)
		ft_memdel((void **)line);
	ft_bzero((void *)buf, sizeof(char) * ft_strlen(buf));
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

int			read_loop(int fd, int *rd, char *buf, char **overflow)
{
	int		n;
	char	*tmp;

	while (!(n = check_buf(buf)) && *rd != 0)
	{
		*rd = read(fd, buf, BUFF_SIZE);
		if (*rd == -1)
			return (-2);
		if (!check_buf(buf))
		{
			tmp = ft_strjoin(*overflow, buf);
			ft_memdel((void **)overflow);
			*overflow = tmp;
			ft_bzero((void *)buf, sizeof(char) * ft_strlen(buf));
		}
	}
	return (n);
}

void		fill_line(char **line, char **buf, char **overflow, int n)
{
	char *tmp;

	*line = (char *)malloc(sizeof(char)
			* (ft_strlen(*overflow) + ((n >= 0) ? n : 0) + 1));
	*line = ft_strcpy(*line, *overflow);
	if (n != -1)
	{
		tmp = ft_strjoin(*line, *buf);
		ft_memdel((void **)line);
		*line = tmp;
	}
	(*line)[ft_strlen(*overflow) + ((n >= 0) ? n : 0)] = '\0';
	ft_memdel((void **)buf);
	ft_memdel((void **)overflow);
}

int			get_next_line(const int fd, char **line)
{
	static int		location;
	int				n;
	int				rd[1];
	char			*buf;
	char			*overflow;

	*rd = 1;
	if (fd < 0)
		return (-1);
	buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	overflow = (char *)malloc(sizeof(char) * 0);
	array_setup(line, buf, overflow, location);
	if (buf == NULL || overflow == NULL || fd < 0)
		return (0);
	n = read_loop(fd, rd, buf, &overflow);
	if (n == -2 || (n == -1 && !*overflow) || (*rd == 0 && !ft_strlen(buf) && BUFF_SIZE > 1))
	{
		*line = (char *)malloc(sizeof(char) * 1);
		(*line)[0] = '\0';
		ft_memdel((void **)&buf);
		ft_memdel((void **)&overflow);
		location = (n != -2) ? lseek(fd, location + 1, SEEK_SET) : 0;
		return (*rd <= 0 ? 0 : 1);
	}
	fill_line(line, &buf, &overflow, n);
	location = lseek(fd, location + ft_strlen(*line) + 1, SEEK_SET);
	return ((*rd == 0 && *line == NULL) ? 0 : 1);
}
