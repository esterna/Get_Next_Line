/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:59:19 by esterna           #+#    #+#             */
/*   Updated: 2017/05/24 16:27:02 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int			get_next_line(const int fd, char **line)
{
	int				rd;
	char			*tmp;
	static char		*overflow[MAX_FD];
	char			buf[BUFF_SIZE + 1];

	ft_bzero(buf, BUFF_SIZE + 1);
	if (fd < 0 || BUFF_SIZE < 1 || !line || (read(fd, buf, 0) < 0))
		return (-1);
	while ((rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (!(overflow[fd]))
			overflow[fd] = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(overflow[fd], buf);
			ft_memdel((void **)(overflow + fd));
			overflow[fd] = tmp;
		}
		ft_bzero(buf, BUFF_SIZE);
	}
	if (overflow[fd] && !(tmp = ft_strchr(overflow[fd], '\n')))
	{
		*line = ft_strdup(overflow[fd]);
		overflow[fd] = NULL;
		return (rd);
	}
	else if ((!overflow[fd] || !overflow[fd][0]) && rd == 0)
	{
		*line = "";
		return (0);
	}
	else
	{
		*line = ft_memalloc(sizeof(char) * ((rd = tmp - overflow[fd]) > 0 ? (tmp - overflow[fd]) + 1 : 2));
		*line = ft_strncpy(*line, overflow[fd], sizeof(char) * ((tmp - overflow[fd]) > 0 ? (tmp - overflow[fd]) : 1));
		(*line)[((tmp - overflow[fd]) > 0 ? (tmp - overflow[fd]) : 1)] = '\0';
		overflow[fd] = overflow[fd] + (tmp - overflow[fd]) + 1;
		return (1);
	}
}
