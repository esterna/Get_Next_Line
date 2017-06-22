/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_real.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 20:27:32 by esterna           #+#    #+#             */
/*   Updated: 2017/05/24 20:37:08 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <limits.h>

int			read_loop(const int fd, char **overflow)
{
	int		rd;
	char	*end;
	char	buf[BUFF_SIZE + 1];

	ft_bzero(buf, BUFF_SIZE + 1);
	if ((rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
		end = ft_strjoin(overflow[fd], buf);
		ft_memdel((void **)&overflow[fd]);
		overflow[fd] = end;
	}
	return (rd);
}

int			get_next_line(const int fd, char **line)
{
	int				rd;
	char			*end;
	static char		*overflow[MAX_FD];

	if (fd < 0 || fd > INT_MAX - 1 || BUFF_SIZE < 1 || !line)
		return (-1);
	if (!(overflow[fd]))
		overflow[fd] = ft_strnew(1);
	while (!(end = ft_strchr(overflow[fd], '\n')))
	{
		if ((rd = read_loop(fd, overflow)) < 0)
			return (-1);
		if (rd == 0 && !end)
		{
			if (overflow[fd][0] == '\0')
				return (0);
			*line = overflow[fd];
			overflow[fd] = NULL;
			return (1);
		}
	}
	*line = ft_strsub(overflow[fd], 0, end - overflow[fd]);
	overflow[fd] = ft_strdup(end + 1);
	return (1);
}
