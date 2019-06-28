/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:00:40 by dslogrov          #+#    #+#             */
/*   Updated: 2019/06/28 17:11:50 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_alloc_table			g_alloc;

static t_alloc_search	search_result(
	t_alloc *alloc, int index, size_t area_max, size_t distance
)
{
	t_alloc_search	result;

	if (alloc == NULL || index == -1)
	{
		result.alloc = NULL;
		result.index = -1;
		result.area_max = -1U;
		result.distance = 0;
	}
	else
	{
		result.alloc = alloc;
		result.index = index;
		result.area_max = area_max;
		result.distance = distance;
	}
	return (result);
}

/*
** I apologise for the weird spacing. Norminette seems to think it's correct
*/

static t_alloc_search	find_entry(void *ptr)
{
	int				i;

	sort_allocs(g_alloc.tiny, ALLOC_NUM_TINY);
	i = -1;
	while (++i < ALLOC_NUM_TINY)
		if (g_alloc.tiny[i].start == ptr)
			return (search_result(&(g_alloc.tiny[i]), i, ALLOC_SIZE_TINY, (i ==
				ALLOC_NUM_TINY ? g_alloc.area_t.start + g_alloc.area_t.size
				: g_alloc.tiny[i + 1].start) - g_alloc.tiny[i].start));
			sort_allocs(g_alloc.small, ALLOC_NUM_SMALL);
	i = -1;
	while (++i < ALLOC_NUM_SMALL)
		if (g_alloc.small[i].start == ptr)
			return (search_result(&(g_alloc.small[i]), i, ALLOC_SIZE_SMALL, (i ==
				ALLOC_NUM_SMALL ? g_alloc.area_s.start + g_alloc.area_s.size
				: g_alloc.small[i + 1].start) - g_alloc.small[i].start));
			sort_allocs(g_alloc.large, ALLOC_NUM_LARGE);
	i = -1;
	while (++i < ALLOC_NUM_LARGE)
		if (g_alloc.large[i].start == ptr)
			return (search_result(&(g_alloc.large[i]), i, SIZE_T_MAX, 0));
	return (search_result(NULL, -1, 0, 0));
}

void					*realloc(void *ptr, size_t size)
{
	t_alloc_search	search;
	void			*alloc;

	if (!ptr || (search = find_entry(ptr)).index == -1)
		return (NULL);
	if ((search.alloc->size <= ALLOC_SIZE_TINY && size > ALLOC_SIZE_TINY) ||
		(search.alloc->size <= ALLOC_SIZE_SMALL && (ALLOC_SIZE_TINY >= size ||
		ALLOC_SIZE_SMALL < size)) || (search.alloc->size > ALLOC_SIZE_SMALL &&
		size <= ALLOC_SIZE_SMALL) || search.distance < size)
	{
		alloc = malloc(size);
		ft_memcpy(alloc, search.alloc->start, MIN(size, search.alloc->size));
		free(ptr);
		return (alloc);
	}
	else
	{
		search.alloc->size = size;
		return (ptr);
	}
}
