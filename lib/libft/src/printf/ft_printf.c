/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 05:31:01 by ivalimak          #+#    #+#             */
/*   Updated: 2024/05/02 02:20:13 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio/ft_printf.h"

ssize_t	ft_printf(const char *f, ...)
{
	va_list	args;
	ssize_t	rval;

	va_start(args, f);
	rval = ft_vprintf(f, args);
	va_end(args);
	return (rval);
}
