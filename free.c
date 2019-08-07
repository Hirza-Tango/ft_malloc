/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:00:26 by dslogrov          #+#    #+#             */
/*   Updated: 2019/08/07 12:19:32 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	dealloc(t_alloc *alloc)
{
	alloc->start = NULL;
	alloc->size = 0;
	MUTEX_UNLOCK;
}

void		free(void *ptr)
{
	size_t i;

	if (ptr == NULL)
		return ;
	MUTEX_LOCK;
	i = -1UL;
	while (++i < ALLOC_NUM_TINY && g_alloc.tiny)
		if (g_alloc.tiny[i].start == ptr)
			return ((void)dealloc(&g_alloc.tiny[i]));
	i = -1UL;
	while (++i < ALLOC_NUM_SMALL && g_alloc.small)
		if (g_alloc.small[i].start == ptr)
			return ((void)dealloc(&g_alloc.small[i]));
	i = -1UL;
	while (++i < ALLOC_NUM_LARGE && g_alloc.large)
		if (g_alloc.large[i].start == ptr)
		{
			munmap(g_alloc.large[i].start, g_alloc.large[i].size);
			return ((void)dealloc(&g_alloc.large[i]));
		}
	MUTEX_UNLOCK;
	ft_putendl_fd("Attempted to free unallocated memory", 2);
}
