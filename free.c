/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:00:26 by dslogrov          #+#    #+#             */
/*   Updated: 2019/07/30 15:46:40 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	dealloc(t_alloc *alloc)
{
	alloc->start = NULL;
	alloc->size = 0;
	pthread_mutex_unlock(&g_mutex);
}

void		free(void *ptr)
{
	size_t i;

	pthread_mutex_lock(&g_mutex);
	if (!g_alloc.area_s.start || !g_alloc.area_t.start || ptr == NULL)
	{
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	i = -1UL;
	while (++i < ALLOC_NUM_TINY)
		if (g_alloc.tiny[i].start == ptr)
			return ((void)dealloc(&g_alloc.tiny[i]));
	i = -1UL;
	while (++i < ALLOC_NUM_SMALL)
		if (g_alloc.small[i].start == ptr)
			return ((void)dealloc(&g_alloc.small[i]));
	i = -1UL;
	while (++i < ALLOC_NUM_LARGE)
		if (g_alloc.large[i].start == ptr)
		{
			munmap(g_alloc.large[i].start, g_alloc.large[i].size);
			return ((void)dealloc(&g_alloc.large[i]));
		}
}
