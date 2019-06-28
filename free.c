/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:00:26 by dslogrov          #+#    #+#             */
/*   Updated: 2019/06/28 14:59:23 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_alloc g_alloc_tiny[ALLOC_NUM_TINY];
t_alloc g_alloc_small[ALLOC_NUM_SMALL];
t_alloc g_alloc_large[ALLOC_NUM_LARGE];
t_alloc g_region_small;
t_alloc g_region_tiny;

static void	dealloc(t_alloc *alloc)
{
	alloc->start = NULL;
	alloc->size = 0;
}

/* TODO: atexit handler for unmap */
void		free(void *ptr)
{
	size_t i;

	if (!g_region_small.start || !g_region_tiny.start || ptr == NULL)
		return ;
	i = -1UL;
	while (++i < ALLOC_NUM_TINY)
		if (g_alloc_tiny[i].start == ptr)
			return ((void)dealloc(&g_alloc_tiny[i]));
	i = -1UL;
	while (++i < ALLOC_NUM_SMALL)
		if (g_alloc_small[i].start == ptr)
			return ((void)dealloc(&g_alloc_small[i]));
	i = -1UL;
	while (++i < ALLOC_NUM_LARGE)
		if (g_alloc_large[i].start == ptr)
		{
			munmap(g_alloc_large[i].start, g_alloc_large[i].size);
			return ((void)dealloc(&g_alloc_large[i]));
		}
}
