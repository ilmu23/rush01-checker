/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:29:22 by ivalimak          #+#    #+#             */
/*   Updated: 2024/02/26 12:03:50 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	checkerror(short *visible, size_t i, char edge, char *err);

void	checktop(t_frame *frame, short **grid, size_t size, char *err)
{
	size_t	i;
	size_t	j;
	short	visible[2];
	short	tallest;

	j = 0;
	while (j < size)
	{
		i = 0;
		tallest = grid[i++][j];
		visible[0] = 1;
		visible[1] = frame->top[j];
		while (i < size)
		{
			if (grid[i][j] > tallest)
			{
				tallest = grid[i][j];
				visible[0]++;
			}
			i++;
		}
		checkerror(visible, ++j, 't', err);
	}
}

void	checkbot(t_frame *frame, short **grid, size_t size, char *err)
{
	ssize_t	i;
	size_t	j;
	short	visible[2];
	short	tallest;

	j = 0;
	while (j < size)
	{
		i = size - 1;
		tallest = grid[i--][j];
		visible[0] = 1;
		visible[1] = frame->bottom[j];
		while (i >= 0)
		{
			if (grid[i][j] > tallest)
			{
				tallest = grid[i][j];
				visible[0]++;
			}
			i--;
		}
		checkerror(visible, ++j, 'b', err);
	}
}

void	checkleft(t_frame *frame, short **grid, size_t size, char *err)
{
	size_t	i;
	size_t	j;
	short	visible[2];
	short	tallest;

	i = 0;
	while (i < size)
	{
		j = 0;
		tallest = grid[i][j++];
		visible[0] = 1;
		visible[1] = frame->left[i];
		while (j < size)
		{
			if (grid[i][j] > tallest)
			{
				tallest = grid[i][j];
				visible[0]++;
			}
			j++;
		}
		checkerror(visible, ++i, 'l', err);
	}
}

void	checkright(t_frame *frame, short **grid, size_t size, char *err)
{
	size_t	i;
	ssize_t	j;
	short	visible[2];
	short	tallest;

	i = 0;
	while (i < size)
	{
		j = size - 1;
		tallest = grid[i][j--];
		visible[0] = 1;
		visible[1] = frame->right[i];
		while (j >= 0)
		{
			if (grid[i][j] > tallest)
			{
				tallest = grid[i][j];
				visible[0]++;
			}
			j--;
		}
		checkerror(visible, ++i, 'r', err);
	}
}

static void	checkerror(short *visible, size_t i, char edge, char *err)
{
	if (visible[0] == visible[1])
		return ;
	*err = 1;
	ft_printf("%sKO: ", SGR_KO);
	if (edge == 't')
		ft_printf("col%utop: ", i);
	else if (edge == 'b')
		ft_printf("col%ubot: ", i);
	else if (edge == 'l')
		ft_printf("row%uleft: ", i);
	else
		ft_printf("row%uright: ", i);
	ft_printf("expected %d visible boxes, got %d visible boxes%s\n",
		visible[1], visible[0], SGR_RST);
}
