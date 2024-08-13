/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:59:34 by ivalimak          #+#    #+#             */
/*   Updated: 2024/08/13 16:40:00 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static char	*format_line(short left, short *mid, short right, size_t size);

void	chk_perror(void)
{
	ft_dprintf(2, "%schecker: %s%s\n", SGR_ERR, strerror(errno), SGR_RST);
}

void	chk_puterror(const char *err)
{
	ft_dprintf(2, "%s%s%s\n", SGR_ERR, err, SGR_RST);
}

void	chk_putgrid(t_frame *frame, short **grid, size_t size)
{
	char	*line;
	size_t	i;

	i = 0;
	line = format_line(0, frame->top, 0, size);
	ft_printf("%s%s\n", line, SGR_RST);
	while (i < size)
	{
		line = format_line(frame->left[i], grid[i], frame->right[i], size);
		ft_printf("%s%s\n", line, SGR_RST);
		i++;
	}
	line = format_line(0, frame->bottom, 0, size);
	ft_printf("%s%s\n\n", line, SGR_RST);
}

static char	*format_line(short left, short *mid, short right, size_t size)
{
	size_t	i;
	char	*out;

	i = 0;
	if (left)
	{
		out = ft_strdup(SGR_FRM);
		out = ft_strjoin(out, ft_itoa(left));
		out = ft_strjoin(out, SGR_GRD);
	}
	else
	{
		out = ft_strdup(" ");
		out = ft_strjoin(out, SGR_FRM);
	}
	while (i < size)
		out = ft_strsjoin(out, ft_itoa(mid[i++]), ' ');
	if (right)
	{
		out = ft_strjoin(out, SGR_FRM);
		out = ft_strsjoin(out, ft_itoa(right), ' ');
	}
	return (out);
}
