/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:00:40 by dslogrov          #+#    #+#             */
/*   Updated: 2019/06/27 17:21:20 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_alloc g_alloc_tiny[ALLOC_NUM_TINY];
t_alloc g_alloc_small[ALLOC_NUM_SMALL];
t_alloc g_alloc_large[ALLOC_NUM_LARGE];
t_alloc g_region_small;
t_alloc g_region_tiny;

/* TODO: this */
void	*realloc(void *ptr, size_t size)
{
	//find pointer in table
	//check if start + new length overlaps
	//if no overlap:
		//change size
		//return original pointer
	//else:
		//allocate new area
		//copy over old size bytes
		//free old allocation
		//return new allocation
	
	(void)(ptr && size);
	return (NULL);
}
