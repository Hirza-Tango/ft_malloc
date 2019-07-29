/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:00:45 by dslogrov          #+#    #+#             */
/*   Updated: 2019/07/29 15:17:59 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_alloc_table	g_alloc;

static size_t	show_tiny(char show_hexdump)
{
	size_t	i;
	size_t	ret;

	ft_putstr("TINY : ");
	ft_putptr(g_alloc.area_t.start);
	ft_putendl("");
	sort_allocs((t_alloc *)g_alloc.tiny, ALLOC_NUM_TINY);
	i = 0;
	ret = 0;
	while (i < ALLOC_NUM_TINY)
	{
		if (g_alloc.tiny[i].start == NULL)
			break ;
		show_range(g_alloc.tiny[i]);
		if (show_hexdump)
			ft_hexdump(g_alloc.tiny[i].start, g_alloc.tiny[i].size, 0, 1);
		ret += g_alloc.tiny[i++].size;
	}
	return (ret);
}

static size_t	show_small(char show_hexdump)
{
	size_t	i;
	size_t	ret;

	ft_putstr("SMALL : ");
	ft_putptr(g_alloc.area_s.start);
	ft_putendl("");
	sort_allocs((t_alloc *)g_alloc.small, ALLOC_NUM_SMALL);
	i = 0;
	ret = 0;
	while (i < ALLOC_NUM_SMALL)
	{
		if (g_alloc.small[i].start == NULL)
			break ;
		show_range(g_alloc.small[i]);
		if (show_hexdump)
			ft_hexdump(g_alloc.small[i].start, g_alloc.small[i].size, 0, 1);
		ret += g_alloc.small[i++].size;
	}
	return (ret);
}

static size_t	show_large(char show_hexdump)
{
	size_t	i;
	size_t	ret;

	ft_putendl("LARGE :");
	sort_allocs((t_alloc *)g_alloc.large, ALLOC_NUM_LARGE);
	i = 0;
	ret = 0;
	while (i < ALLOC_NUM_LARGE)
	{
		if (g_alloc.large[i].start == NULL)
			break ;
		show_range(g_alloc.large[i]);
		if (show_hexdump)
			ft_hexdump(g_alloc.small[i].start, g_alloc.small[i].size, 0, 1);
		ret += g_alloc.large[i++].size;
	}
	return (ret);
}

void			show_alloc_mem(void)
{
	size_t	size;

	size = show_tiny(0) + show_small(0) + show_large(0);
	ft_putstr("Total : ");
	ft_putnbr(size);
	ft_putendl(" bytes");
}

void			show_alloc_mem_ex(void)
{
		size_t	size;

	size = show_tiny(1) + show_small(1) + show_large(1);
	ft_putstr("Total : ");
	ft_putnbr(size);
	ft_putendl(" bytes");
}
