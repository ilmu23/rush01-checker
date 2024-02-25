/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:03:19 by ivalimak          #+#    #+#             */
/*   Updated: 2024/02/25 19:04:16 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static short	*parsenumbers(char **argarr, size_t argc);
static int		checkargs(char *argstring, size_t argc);
static int		checkvalues(char *argstring, size_t argc);

t_frame	*parseargs(char *argstring, size_t argc)
{
	t_frame	*out;
	char	**argarr;

	if (!checkargs(argstring, argc))
		return (NULL);
	out = ft_push(ft_alloc(sizeof(t_frame)));
	argarr = ft_pusharr(ft_split(ft_strremove(argstring, '\t'), ' '));
	if (!out || !argarr)
	{
		chk_perror();
		return (NULL);
	}
	out->top = ft_push(parsenumbers(argarr, argc / 4));
	out->bottom = ft_push(parsenumbers(argarr + (argc / 4), argc / 4));
	out->left = ft_push(parsenumbers(argarr + (2 * (argc / 4)), argc / 4));
	out->right = ft_push(parsenumbers(argarr + (3 * (argc / 4)), argc / 4));
	if (!out->top || !out->bottom || !out->left || !out->right)
	{
		chk_perror();
		return (NULL);
	}
	return (out);
}

static short	*parsenumbers(char **argarr, size_t argc)
{
	size_t	i;
	short	*out;

	out = ft_alloc(argc * sizeof(short));
	if (!out)
		return (NULL);
	i = 0;
	while (i < argc)
	{
		out[i] = ft_atoi(argarr[i]);
		i++;
	}
	return (out);
}

static int	checkargs(char *argstring, size_t argc)
{
	if (argc < 16)
		chk_puterror("checker: not enough arguments");
	else if (argc > 36)
		chk_puterror("checker: too many arguments");
	else if (argc % 4 != 0)
		chk_puterror("checker: argument count not divisible by 4");
	else if (checkvalues(argstring, argc))
		return (1);
	return (0);
}

static int	checkvalues(char *argstring, size_t argc)
{
	long	n;
	short	err;

	err = 0;
	while (*argstring && !err)
	{
		while (ft_isspace(*argstring))
			argstring++;
		if (!ft_isdigit(*argstring) && *argstring != '+' && *argstring != '-')
			err = 1;
		n = ft_atol(argstring);
		if (n < 1 || n > (long)(argc / 4))
			err = 2;
		if (*argstring == '+' || *argstring == '-')
			argstring++;
		while (ft_isdigit(*argstring))
			argstring++;
		if (*argstring && !ft_isspace(*argstring))
			err = 1;
	}
	if (err == 1)
		chk_puterror("checker: argument not a number");
	else if (err == 2)
		chk_puterror("checker: argument out of range");
	return (!err);
}
