/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:00:36 by dslogrov          #+#    #+#             */
/*   Updated: 2019/08/07 16:20:14 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_alloc_table	g_alloc;
pthread_mutex_t	g_mutex;

static void	*alloc_tiny(size_t size)
{
	void	*ret;
	size_t	i;
	t_alloc *alloc;

	if (!g_alloc.area_t.start)
	{
		g_alloc.area_t.start = mmap(NULL, ALLOC_NUM_TINY * ALLOC_SIZE_TINY, PERM
			, MAP_ANON | MAP_PRIVATE, -1, 0);
		g_alloc.area_t.size = ALLOC_NUM_TINY * ALLOC_SIZE_TINY;
	}
	sort_allocs((t_alloc *)g_alloc.tiny, ALLOC_NUM_TINY);
	ret = alloc_space(g_alloc.tiny, g_alloc.area_t, ALLOC_NUM_TINY, size);
	alloc = g_alloc.tiny;
	i = 0;
	while (alloc[i].start != NULL && i < ALLOC_NUM_TINY)
		i++;
	if (i == ALLOC_NUM_TINY || !ret)
		return (NULL);
	alloc[i].start = ret;
	alloc[i].size = size;
	return (ret);
}

static void	*alloc_small(size_t size)
{
	void	*ret;
	size_t	i;
	t_alloc *alloc;

	if (!g_alloc.area_s.start)
	{
		g_alloc.area_s.start = mmap(NULL, ALLOC_NUM_SMALL * ALLOC_SIZE_SMALL, PERM
			, MAP_ANON | MAP_PRIVATE, -1, 0);
		g_alloc.area_s.size = ALLOC_NUM_SMALL * ALLOC_SIZE_SMALL;
	}
	sort_allocs((t_alloc *)g_alloc.small, ALLOC_NUM_SMALL);
	ret = alloc_space(g_alloc.small, g_alloc.area_s, ALLOC_SIZE_SMALL, size);
	alloc = g_alloc.small;
	i = 0;
	while (alloc[i].start != NULL && i < ALLOC_NUM_SMALL)
		i++;
	if (i == ALLOC_NUM_SMALL || !ret)
		return (NULL);
	alloc[i].start = ret;
	alloc[i].size = size;
	return (ret);
}

static void	*alloc_large(size_t size)
{
	void	*ret;
	size_t	i;
	t_alloc *alloc;

	ret = mmap(NULL, size, PERM, MAP_ANON | MAP_PRIVATE, -1, 0);
	alloc = g_alloc.large;
	i = 0;
	while (alloc[i].start != NULL && i < ALLOC_NUM_LARGE)
		i++;
	if (i == ALLOC_NUM_LARGE || !ret)
		return (NULL);
	alloc[i].start = ret;
	alloc[i].size = size;
	return (ret);
}

void		*malloc(size_t size)
{
	static char init = 0;
	void		*ret;

	if (!init)
	{
		MUTEX_INIT;

		init = 1;
	}
	MUTEX_LOCK;
	if (size <= ALLOC_SIZE_TINY)
		ret = alloc_tiny(size);
	else if (size <= ALLOC_SIZE_SMALL)
		ret = alloc_small(size);
	else
		ret = alloc_large(size);
	MUTEX_UNLOCK;
	return (ret);
}
