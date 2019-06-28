/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:38:49 by dslogrov          #+#    #+#             */
/*   Updated: 2019/06/28 16:24:43 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <unistd.h>
# include <limits.h>
# include <sys/mman.h>
# include "libft.h"

# define ALLOC_NUM_TINY 512
# define ALLOC_NUM_SMALL 128
# define ALLOC_NUM_LARGE 128
# define ALLOC_SIZE_TINY (LONG_BIT / CHAR_BIT)
# define ALLOC_SIZE_SMALL 512
# define PERM PROT_READ | PROT_WRITE

typedef struct	s_alloc
{
	void	*start;
	size_t	size;
}				t_alloc;

typedef struct	s_alloc_search
{
	t_alloc	*alloc;
	int		index;
	size_t	area_max;
	size_t	distance;
}				t_alloc_search;

extern t_alloc	g_alloc_tiny[ALLOC_NUM_TINY];
extern t_alloc	g_alloc_small[ALLOC_NUM_SMALL];
extern t_alloc	g_alloc_large[ALLOC_NUM_LARGE];

extern t_alloc	g_region_tiny;
extern t_alloc	g_region_small;

void			*alloc_space(
	const t_alloc *alloc, const t_alloc area, const size_t
	alloc_len, const size_t new_size);
void			sort_allocs(t_alloc *allocs, size_t size);

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);

void			show_alloc_mem(void);

void			show_alloc_mem_ex(void);

#endif
