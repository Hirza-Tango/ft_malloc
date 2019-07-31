/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:38:49 by dslogrov          #+#    #+#             */
/*   Updated: 2019/07/30 15:53:51 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <unistd.h>
# include <limits.h>
# include <sys/mman.h>
# include "libft.h"
# include <pthread.h>

# define ALLOC_SIZE_TINY 16
# define ALLOC_SIZE_SMALL 1024
# define ALLOC_NUM_TINY 128
# define ALLOC_NUM_SMALL 1024
# define ALLOC_NUM_LARGE 128
# define PERM PROT_READ | PROT_WRITE

typedef struct			s_alloc
{
	void	*start;
	size_t	size;
}						t_alloc;

typedef struct			s_alloc_search
{
	t_alloc	*alloc;
	int		index;
	size_t	area_max;
	size_t	distance;
}						t_alloc_search;

typedef struct			s_alloc_table
{
	t_alloc	tiny[ALLOC_NUM_TINY];
	t_alloc	small[ALLOC_NUM_SMALL];
	t_alloc	large[ALLOC_NUM_LARGE];
	t_alloc	area_t;
	t_alloc area_s;
}						t_alloc_table;

extern t_alloc_table	g_alloc;
extern pthread_mutex_t	g_mutex;

void					*alloc_space(const t_alloc *alloc, const t_alloc area,
	const size_t alloc_len, const size_t new_size);
void					sort_allocs(t_alloc *allocs, size_t size);
void					show_range(t_alloc alloc);

void					free(void *ptr);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);

void					show_alloc_mem(void);
void					show_alloc_mem_ex(void);

#endif
