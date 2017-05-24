/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 16:39:58 by esterna           #+#    #+#             */
/*   Updated: 2017/05/23 18:53:15 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int			get_next_line(const int fd, char **line)
{
	static int location;
	int rd;
	char *tmp;
	char buf[BUFF_SIZE + 1];
	char *overflow;

	rd = 1;
	tmp = NULL;
	overflow = ft_memalloc(0);
	buf[BUFF_SIZE] = '\0';
	/* Ask about MAX_FD */
	if (fd < 0 || BUFF_SIZE < 1 || !line || (read(fd, buf, 0) < 0))
		return (-1);
	while (rd > 0)
	{
		if ((rd = read(fd, buf, BUFF_SIZE)) == -1)
			return (-1);
		if ((tmp = ft_memchr(buf, '\n', sizeof(char) * ft_strlen(buf))) || rd == 0)
		{
			*tmp = '\0';
			*line = (!overflow) ? ft_strdup(buf) : ft_strjoin(overflow, buf);
			ft_memdel((void **)&overflow);
			location = lseek(fd, location + ft_strlen(*line) + 1, SEEK_SET);
			return ((rd != 0) ? 1 : 0);
		}
		else
		{
			tmp = ft_strjoin(overflow, buf);
			ft_memdel((void **)&overflow);
			overflow = tmp;
		}
	}
	return (-1);
}
