/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:00:45 by dslogrov          #+#    #+#             */
/*   Updated: 2019/06/26 17:00:47 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <stdio.h>

t_alloc g_alloc_tiny[ALLOC_NUM_TINY];
t_alloc g_alloc_small[ALLOC_NUM_SMALL];
t_alloc g_alloc_large[ALLOC_NUM_LARGE];
t_alloc g_region_small;
t_alloc g_region_tiny;

static size_t	show_tiny(void)
{
	size_t	i;
	size_t	ret;
	t_alloc	current;
	
	printf("TINY : %p\n", g_region_tiny.start);
	sort_allocs((t_alloc *)g_alloc_tiny, ALLOC_NUM_TINY);
	i = 0;
	ret = 0;
	while (i < ALLOC_NUM_TINY)
	{
		current = g_alloc_tiny[i++];
		if (current.start != NULL)
		{
			printf("%p - %p : %zu bytes\n", current.start, (char *)
				current.start + current.size, current.size);
			ret += current.size;
		}
	}
	return ret;
}

static size_t	show_small(void)
{
	size_t	i;
	size_t	ret;
	t_alloc	current;
	
	printf("SMALL : %p\n", g_region_small.start);
	sort_allocs((t_alloc *)g_alloc_small, ALLOC_NUM_SMALL);
	i = 0;
	ret = 0;
	while (i < ALLOC_NUM_SMALL)
	{
		current = g_alloc_small[i++];
		if (current.start != NULL)
		{
			printf("%p - %p : %zu bytes\n", current.start, (char *)
				current.start + current.size, current.size);
			ret += current.size;
		}
	}
	return ret;
}

static size_t	show_large(void)
{
	size_t	i;
	size_t	ret;
	t_alloc	current;
	
	printf("LARGE : \n");
	sort_allocs((t_alloc *)g_alloc_large, ALLOC_NUM_LARGE);
	i = 0;
	ret = 0;
	while (i < ALLOC_NUM_LARGE)
	{
		current = g_alloc_large[i++];
		if (current.start != NULL)
		{
			printf("%p - %p : %zu bytes\n", current.start, (char *)
				current.start + current.size, current.size);
			ret += current.size;
		}
	}
	return ret;
}

/* TODO: fix printf */
void			show_alloc_mem(void)
{
	size_t	size;

	size = show_tiny() + show_small() + show_large();
	printf("Total : %zu bytes\n", size);
}

void			show_alloc_mem_ex(void)
{

}
