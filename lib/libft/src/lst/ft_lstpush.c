/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:15:32 by ivalimak          #+#    #+#             */
/*   Updated: 2024/05/26 19:38:52 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_lstpush.c
 */

#include "lft_gc.h"
#include "lft_lst.h"

/** @brief Pushes the node and its content
 * 
 * @param *node Address of the node
 * @retval t_list* Address of the node
 */
t_list	*ft_lstpush(const t_list *node)
{
	ft_push(node);
	ft_push(node->blk);
	return ((t_list *)node);
}
