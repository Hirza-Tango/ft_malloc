/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 14:59:17 by tango             #+#    #+#             */
/*   Updated: 2019/07/29 14:13:44 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*alloc_space(
	const t_alloc *alloc, const t_alloc area, const size_t alloc_len,
	const size_t new_size
)
{
	void	*start;
	size_t	i;

	start = area.start;
	i = 0;
	while ((char *)start + new_size <= (char *)area.start + area.size &&
		i < alloc_len)
	{
		if (((char *)(alloc[i].start) - (char *)start) >= (long)new_size ||
			alloc[i].start == NULL)
			return (start);
		start = (char *)(alloc[i].start) + alloc[i].size;
		i++;
	}
	return (NULL);
}

void	sort_allocs(t_alloc *allocs, size_t size)
{
	t_alloc	temp;
	size_t	i;
	size_t	j;

	i = 1;
	while (i < size)
	{
		j = i++;
		while (j > 0 && allocs[j - 1].start > allocs[j].start)
		{
			if (allocs[j - 1].start != NULL && allocs[j].start == NULL)
			{
				j--;
				continue ;
			}
			temp = (allocs)[j - 1];
			(allocs)[j - 1] = (allocs)[j];
			(allocs)[j] = temp;
			j--;
		}
	}
}

void	show_range(t_alloc alloc)
{
	ft_putptr(alloc.start);
	ft_putstr(" - ");
	ft_putptr(alloc.start + alloc.size);
	ft_putstr(" : ");
	ft_put_uintmax_base(alloc.size, 10);
	ft_putendl(" bytes");
}
