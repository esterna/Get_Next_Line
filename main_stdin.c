/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 217/5/23 15:19:35 by esterna           #+#    #+#             */
/*   Ufddated: 217/5/23 15:19:35 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

int			main()
{
	char *line;
	while (get_next_line(0, &line) == 1)
	{
		printf("Result: %s\n", line);
		free(line);
	}
	return (0);
}
