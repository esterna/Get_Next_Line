/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 19:06:18 by esterna           #+#    #+#             */
/*   Updated: 2017/07/04 13:35:00 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <limits.h>

static int		read_loop(const int fd, char **overflow)
{
	int		rd;
	char	*end;
	char	buf[BUFF_SIZE + 1];

	ft_bzero(buf, BUFF_SIZE + 1);
	if ((rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (!(overflow[fd]))
			overflow[fd] = ft_strdup(buf);
		else
		{
			end = ft_strjoin(overflow[fd], buf);
			ft_memdel((void **)(overflow + fd));
			overflow[fd] = end;
		}
	}
	return (rd);
}

int				get_next_line(const int fd, char **line)
{
	int				rd;
	char			*end;
	static char		*overflow[MAX_FD];

	if (fd < 0 || fd > INT_MAX - 1 || BUFF_SIZE < 1 || !line)
		return (-1);
	if (!(overflow[fd]))
		overflow[fd] = NULL;
	while (!(end = ft_strchr(overflow[fd], '\n')))
	{
		if ((rd = read_loop(fd, overflow)) < 0)
			return (-1);
		if (rd == 0 && !end)
		{
			if (!overflow[fd] || overflow[fd][0] == '\0')
				return (0);
			*line = overflow[fd];
			ft_memdel((void **)(overflow + fd));
			return (1);
		}
	}
	*line = ft_strsub(overflow[fd], 0, end - overflow[fd]);
	end = ft_strdup(end + 1);
	ft_memdel((void **)(overflow + fd));
	overflow[fd] = end;
	return (1);
}
