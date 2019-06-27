/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:00:36 by dslogrov          #+#    #+#             */
/*   Updated: 2019/06/27 17:14:56 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_alloc g_alloc_tiny[ALLOC_NUM_TINY];
t_alloc g_alloc_small[ALLOC_NUM_SMALL];
t_alloc g_alloc_large[ALLOC_NUM_LARGE];
t_alloc g_region_small;
t_alloc g_region_tiny;

/* TODO: hook main start? */
static void	init_mem()
{
	size_t i;
	t_alloc empty;

	empty.start = NULL;
	empty.size = 0;
	g_region_tiny.start = mmap(NULL,ALLOC_NUM_TINY * ALLOC_SIZE_TINY, 0,
		MAP_ANON | MAP_PRIVATE, -1, NULL);
	g_region_tiny.size = ALLOC_NUM_TINY * ALLOC_SIZE_TINY;
	g_region_small.start = mmap(NULL,ALLOC_NUM_SMALL * ALLOC_SIZE_SMALL, 0,
		MAP_ANON | MAP_PRIVATE, -1, NULL);
	g_region_small.size = ALLOC_NUM_SMALL * ALLOC_SIZE_SMALL;
	i = 0;
	while (i < ALLOC_NUM_TINY)
		g_alloc_tiny[i++] = empty;
	i = 0;
	while (i < ALLOC_NUM_SMALL)
		g_alloc_small[i++] = empty;
	i = 0;
	while (i < ALLOC_NUM_LARGE)
		g_alloc_large[i++] = empty;
}

static void *alloc_tiny(size_t size)
{
	void	*ret;
	size_t	i;
	t_alloc *alloc;

	sort_allocs((t_alloc *)g_alloc_tiny, ALLOC_NUM_TINY);
	ret = alloc_space(g_alloc_tiny, g_region_tiny, ALLOC_NUM_TINY, size);
	alloc = g_alloc_tiny;
	i = 0;
	while (alloc[i].start != NULL && i < ALLOC_NUM_TINY)
		i++;
	if (i == ALLOC_NUM_TINY || !ret)
		return NULL;
	alloc[i].start = ret;
	alloc[i].size = size;
	return ret;
}

static void *alloc_small(size_t size)
{
	void	*ret;
	size_t	i;
	t_alloc *alloc;

	sort_allocs((t_alloc *)g_alloc_small, ALLOC_NUM_SMALL);
	ret = alloc_space(g_alloc_small, g_region_small, ALLOC_SIZE_SMALL, size);
	alloc = g_alloc_small;
	i = 0;
	while (alloc[i].start != NULL && i < ALLOC_NUM_SMALL)
		i++;
	if (i == ALLOC_NUM_SMALL || !ret)
		return NULL;
	alloc[i].start = ret;
	alloc[i].size = size;
	return ret;
}

static void	*alloc_large(size_t size)
{
	void	*ret;
	size_t	i;
	t_alloc *alloc;

	if (size % getpagesize())
		size = ((size / getpagesize()) + 1) * getpagesize();
	ret = mmap(NULL, size, 0, MAP_ANON | MAP_PRIVATE, -1, 0);
	alloc = g_alloc_large;
	i = 0;
	while (alloc[i].start != NULL && i < ALLOC_NUM_LARGE)
		i++;
	if (i == ALLOC_NUM_LARGE || !ret)
		return NULL;
	alloc[i].start = ret;
	alloc[i].size = size;
	return ret;
}

void		*malloc(size_t size)
{
	static char init = 0;

	if (!init)
		init_mem();
	init = 1;
	if (size <= ALLOC_SIZE_TINY)
		return alloc_tiny(size);
	else if (size <= ALLOC_SIZE_SMALL)
		return alloc_small(size);
	else
		return alloc_large(size);
}
