/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:00:19 by ivalimak          #+#    #+#             */
/*   Updated: 2024/02/27 13:52:37 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static size_t	get_arrsize(void *arr);
static short	*parseline(const char *line, size_t size, size_t lnbr, char *e);
static int		convert(short *shortarr, char **strarr, size_t size, char *e);

short	**getsolution(size_t size)
{
	size_t	i;
	short	**out;
	char	err;

	out = ft_push(ft_alloc(size * sizeof(short *)));
	if (!out)
	{
		chk_perror();
		return (NULL);
	}
	i = 0;
	err = 0;
	while (i < size)
	{
		out[i] = parseline(ft_push(ft_strtrim(get_next_line(0), " \t\n")),
			size, i, &err);
		if (!out[i++])
		{
			chk_perror();
			return (NULL);
		}
	}
	if (err)
		ft_exit(0);
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

static short	*parseline(const char *line, size_t size, size_t lnbr, char *e)
{
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
		*e = 1;
	if (!convert(out, arr, size, e))
		ft_printf("%sKO: number out of range on line %u%s\n",
			SGR_KO, lnbr + 1, SGR_RST);
	return (out);
}


static int	convert(short *shortarr, char **strarr, size_t size, char *e)
{
	size_t	i;
	int		rv;

	i = 0;
	rv = 1;
	while (i < size)
	{
		shortarr[i] = ft_atoi(strarr[i]);
		if (shortarr[i] < 1 || shortarr[i] > (short)size)
			rv = 0;
		i++;
	}
	if (!rv)
		*e = 1;
	return (rv);
}
