/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:49:31 by ivalimak          #+#    #+#             */
/*   Updated: 2024/02/25 19:58:52 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	main(int argc, char **argv)
{
	size_t	argn;
	t_frame	*frame;
	short	**grid;

	if (argc != 2)
	{
		chk_puterror("checker: incorrect argument count");
		return (ft_return(1));
	}
	argn = ft_wordcount(argv[1]);
	frame = parseargs(argv[1], argn);
	if (!frame)
		return (ft_return(2));
	grid = getsolution(argn / 4);
	if (!grid)
		return (ft_return(3));
	chk_putgrid(frame, grid, argn / 4);
	checksolution(frame, grid, argn / 4);
	return (ft_return(0));
}
