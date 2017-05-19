/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   robin_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 13:36:48 by rschramm          #+#    #+#             */
/*   Updated: 2017/05/18 20:54:04 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int		main(int argc, char **argv)
{
	char	*line;
	int		fd;
	int		res;
	int		num;

	res = 0;
	num = 0;
	line = NULL;
	argc = 0;
	fd = open(argv[1], O_RDONLY);
	
	if (fd > 0)
		while ((res = get_next_line(fd, &line)) > 0)
		{
			printf("[Ret: %d, # of Line: %d, FD: %d] %s\n", res, ++num, fd, line);
			ft_strdel(&line);
		}
	ft_strdel(&line);
	printf("[Ret: %d, # of Line: %d, FD: %d] %s\n", res, ++num, fd, line);
	if ((fd > 0 && (close(fd) == -1 || res != 0)) || fd < 0)
	{
		if (!line)
			write(1, "error\n", 6);
		return (1);
	}
	printf ("/* Ret == 1 ; read line\n   Ret == 0 ; end of line(finish) */\n");
	return (0);
}
