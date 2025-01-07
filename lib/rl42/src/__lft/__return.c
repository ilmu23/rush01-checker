/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __return.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 07:43:06 by ivalimak          #+#    #+#             */
/*   Updated: 2024/08/15 15:16:26 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__lft.h"

int	__return(int rval)
{
	__popall();
	__clean();
	free(__getvm()->objmap.objs);
	return (rval);
}
