/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:00:45 by dslogrov          #+#    #+#             */
/*   Updated: 2019/06/27 16:56:22 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "libft.h"

t_alloc g_alloc_tiny[ALLOC_NUM_TINY];
t_alloc g_alloc_small[ALLOC_NUM_SMALL];
t_alloc g_alloc_large[ALLOC_NUM_LARGE];
t_alloc g_region_small;
t_alloc g_region_tiny;

static void		show_range(t_alloc alloc)
{
		ft_putptr(alloc.start);
		ft_putstr(" - ");
		ft_putptr(alloc.start + alloc.size);
		ft_putstr(" : ");
		ft_put_uintmax_base(alloc.size, 10);
		ft_putendl(" bytes");
}

static size_t	show_tiny(void)
{
	size_t	i;
	size_t	ret;
	
	ft_putstr("TINY : ");
	ft_putptr(g_region_tiny.start);
	ft_putendl("");
	sort_allocs((t_alloc *)g_alloc_tiny, ALLOC_NUM_TINY);
	i = 0;
	ret = 0;
	while (i < ALLOC_NUM_TINY)
	{
		if (g_alloc_tiny[i].start == NULL)
			break ;
		show_range(g_alloc_tiny[i]);
		ret += g_alloc_tiny[i++].size;
	}
	return ret;
}

static size_t	show_small(void)
{
	size_t	i;
	size_t	ret;
	
	ft_putstr("SMALL : ");
	ft_putptr(g_region_small.start);
	ft_putendl("");
	sort_allocs((t_alloc *)g_alloc_small, ALLOC_NUM_SMALL);
	i = 0;
	ret = 0;
	while (i < ALLOC_NUM_SMALL)
	{
		if (g_alloc_small[i].start == NULL)
			break ;
		show_range(g_alloc_small[i]);
		ret += g_alloc_small[i++].size;
	}
	return ret;
}

static size_t	show_large(void)
{
	size_t	i;
	size_t	ret;
	
	ft_putendl("LARGE :");
	sort_allocs((t_alloc *)g_alloc_large, ALLOC_NUM_LARGE);
	i = 0;
	ret = 0;
	while (i < ALLOC_NUM_LARGE)
	{
		if (g_alloc_large[i].start == NULL)
			break ;
		show_range(g_alloc_large[i]);
		ret += g_alloc_large[i++].size;
	}
	return ret;
}

/* TODO: fix printf */
void			show_alloc_mem(void)
{
	size_t	size;

	size = show_tiny() + show_small() + show_large();
	ft_putstr("Total : ");
	ft_putnbr(size);
	ft_putendl("bytes");
}
