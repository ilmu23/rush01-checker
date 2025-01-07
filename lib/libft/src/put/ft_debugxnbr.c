/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debugxnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:20:49 by ivalimak          #+#    #+#             */
/*   Updated: 2024/03/23 11:17:52 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lft_to.h"
#include "lft_put.h"

void	ft_debugxnbr(uint64_t n, char f)
{
	const char	*hexarr = "0123456789abcdef";

	if (f == 'p')
	{
		ft_putstr_fd("0x", DEBUGFD);
		f = 'x';
	}
	while (n > 15)
	{
		ft_debugxnbr(n / 16, f);
		if (f == 'x')
			ft_putchar_fd(hexarr[n % 16], DEBUGFD);
		else
			ft_putchar_fd(ft_toupper(hexarr[n % 16]), DEBUGFD);
		return ;
	}
	if (f == 'x')
		ft_putchar_fd(hexarr[n % 16], DEBUGFD);
	else
		ft_putchar_fd(ft_toupper(hexarr[n % 16]), DEBUGFD);
}
