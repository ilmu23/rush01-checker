/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:00:19 by ivalimak          #+#    #+#             */
/*   Updated: 2024/02/25 19:57:27 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static size_t	get_arrsize(void *arr);
static short	*parseline(const char *line, size_t size, size_t lnbr);

short	**getsolution(size_t size)
{
	size_t	i;
	short	**out;

	out = ft_push(ft_alloc(size * sizeof(short *)));
	if (!out)
	{
		chk_perror();
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		out[i] = parseline(ft_push(ft_strtrim(get_next_line(0), " \t\n")),
			size, i);
		if (!out[i++])
		{
			chk_perror();
			return (NULL);
		}
	}
	return (out);
}

static size_t	get_arrsize(void *a)
{
	size_t	i;
	void	**arr;

	i = 0;
	arr = a;
	while (arr[i])
		i++;
	return (i);
}

static short	*parseline(const char *line, size_t size, size_t lnbr)
{
	size_t	i;
	size_t	arrsize;
	short	*out;
	char	**arr;

	out = ft_push(ft_alloc(size * sizeof(short)));
	arr = ft_split(line, ' ');
	if (!line || !out || !arr)
		return (NULL);
	arrsize = get_arrsize(arr);
	if (arrsize > size)
		ft_printf("%sKO: too many numbers on line %u: '%s'%s\n",
			SGR_KO, lnbr + 1, line, SGR_RST);
	if (arrsize < size)
		ft_printf("%sKO: too few numbers on line %u: '%s'%s\n",
			SGR_KO, lnbr + 1, line, SGR_RST);
	if (arrsize != size)
		ft_exit(0);
	i = 0;
	while (arr[i] && i < size)
	{
		out[i] = ft_atoi(arr[i]);
		i++;
	}
	return (out);
}
