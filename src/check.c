/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:00:41 by ivalimak          #+#    #+#             */
/*   Updated: 2024/02/26 11:28:57 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	checkduprow(short **grid, size_t size, char *err);
static void	checkdupcol(short **grid, size_t size, char *err);

void	checksolution(t_frame *frame, short **grid, size_t size)
{
	char	err;

	err = 0;
	checkduprow(grid, size, &err);
	checkdupcol(grid, size, &err);
	checktop(frame, grid, size, &err);
	checkbot(frame, grid, size, &err);
	checkleft(frame, grid, size, &err);
	checkright(frame, grid, size, &err);
	if (!err)
		ft_printf("%sOK%s\n", SGR_OK, SGR_RST);
}

static void	checkduprow(short **grid, size_t size, char *err)
{
	size_t	i;
	size_t	j;
	size_t	sum;
	size_t	csum;

	i = 0;
	while (i < size)
	{
		j = 0;
		sum = 0;
		csum = 4;
		while (j < size)
		{
			sum += grid[i][j];
			csum += j++;
		}
		if (sum != csum)
		{
			*err = 1;
			ft_printf("%sKO: duplicate number on line %u%s\n",
				SGR_KO, i + 1, SGR_RST);
		}
		i++;
	}
}

static void	checkdupcol(short **grid, size_t size, char *err)
{
	size_t	i;
	size_t	j;
	size_t	sum;
	size_t	csum;

	j = 0;
	while (j < size)
	{
		i = 0;
		sum = 0;
		csum = 4;
		while (i < size)
		{
			sum += grid[i][j];
			csum += i++;
		}
		if (sum != csum)
		{
			*err = 1;
			ft_printf("%sKO: duplicate number on column %u%s\n",
				SGR_KO, j + 1, SGR_RST);
		}
		j++;
	}
}
