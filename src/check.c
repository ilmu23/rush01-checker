/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:00:41 by ivalimak          #+#    #+#             */
/*   Updated: 2024/02/25 20:12:20 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	checkduplicates(short **grid, size_t size, char *err);
static void	checkcol(t_frame *frame, short **grid, size_t size, char *err);
static void	checkrow(t_frame *frame, short **grid, size_t size, char *err);

void	checksolution(t_frame *frame, short **grid, size_t size)
{
	char	err;

	err = 0;
	checkduplicates(grid, size, &err);
	checkcol(frame, grid, size, &err);
	checkrow(frame, grid, size, &err);
	if (!err)
		ft_printf("%sOK%s\n", SGR_OK, SGR_RST);
}

static void	checkduplicates(short **grid, size_t size, char *err)
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

static void	checkcol(t_frame *frame, short **grid, size_t size, char *err)
{
	(void)frame;
	(void)grid;
	(void)size;
	(void)err;
}

static void	checkrow(t_frame *frame, short **grid, size_t size, char *err)
{
	(void)frame;
	(void)grid;
	(void)size;
	(void)err;
}
