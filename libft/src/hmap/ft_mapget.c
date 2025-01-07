/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 04:06:26 by ivalimak          #+#    #+#             */
/*   Updated: 2024/05/23 21:04:26 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lft_str.h"
#include "_internal/lft_hmap_internal.h"

void	*ft_mapget(t_hmap *hmap, const char *key)
{
	t_hmap_pair	*pair;
	size_t		i;
	size_t		j;

	if (!hmap || !key || !hmap->count)
		return (NULL);
	j = 0;
	i = gethash(key, hmap->size, j++);
	pair = hmap->items[i];
	while (pair)
	{
		if (pair != (void *)&g_hmap_sentinel && ft_strequals(pair->key, key))
			return (pair->value);
		i = gethash(key, hmap->size, j++);
		pair = hmap->items[i];
	}
	return (NULL);
}
