/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 19:02:36 by esterna           #+#    #+#             */
/*   Updated: 2017/05/23 15:17:05 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int			main(int argc, char **argv)
{
	int		fd;
	char	*ptr;

	if (argc != 2)
	{
		printf("usage:\nget_next_line file\n");
		return (0);
	}
	argv++;
	fd = open(*argv, O_RDONLY);
	while (get_next_line(fd, &ptr) > 0)
		printf("%s\n", ptr);
	printf("%s", ptr);
	return (0);
}
