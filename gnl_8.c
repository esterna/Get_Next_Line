/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 14:04:06 by esterna           #+#    #+#             */
/*   Updated: 2017/07/10 16:55:54 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <limits.h>

char			**setup_line(char **line, char **overflow)
{
	char	*end;

	if ((end = ft_strchr(*overflow, '\n')))
		*line = ft_strncpy(ft_strnew(end - *overflow), *overflow, end - *overflow);
	else
		*line = ft_strdup(*overflow);
	return (overflow);
}

void			fill_overflow(char **overflow)
{
	char	*end;
	char	*tmp;

	end = ft_strchr(*overflow, '\n');
	if (end)
	{
		tmp = ft_strdup(end + 1);
		ft_strdel(overflow);
		*overflow = tmp;
	}
	else
	{
		ft_strdel(overflow);
		*overflow = NULL;
	}
}

int				get_next_line(const int fd, char **line)
{
	int				rd;
	char			buf[BUFF_SIZE + 1];
	char			*tmp;
	static char		*overflow[MAX_FD];

	if (fd < 0 || fd > INT_MAX - 1 || BUFF_SIZE < 1 || !line || read(fd, buf, 0) < 0)
		return (-1);
	if (!(overflow[fd]))
		overflow[fd] = ft_strnew(BUFF_SIZE);
	ft_bzero(buf, BUFF_SIZE + 1);
	while ((rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[rd] = '\0';
		tmp = ft_strjoin(overflow[fd], buf);
		ft_strdel(overflow + fd);
		overflow[fd] = tmp;
		if ((tmp = ft_strchr(overflow[fd], '\n')))
			break ;
	}
	if (rd == 0 && overflow[fd][0] == 0)
	{
		ft_strdel(overflow + fd);
		return (0);
	}
	fill_overflow(setup_line(line, overflow + fd));
	return (1);
}
