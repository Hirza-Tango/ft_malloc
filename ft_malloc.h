/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:38:49 by dslogrov          #+#    #+#             */
/*   Updated: 2019/06/26 10:36:12 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/mman.h>

# ifdef __linux__
#  define LONG_BIT 8
# endif

# define ALLOC_NUM_TINY 512
# define ALLOC_NUM_SMALL 128
# define ALLOC_NUM_LARGE 128
# define ALLOC_SIZE_TINY (LONG_BIT / CHAR_BIT)
# define ALLOC_SIZE_SMALL 512

typedef struct	s_alloc{
	void	*start;
	size_t	size;
}				t_alloc;

extern t_alloc	g_alloc_tiny[ALLOC_NUM_TINY];
extern t_alloc	g_alloc_small[ALLOC_NUM_SMALL];
extern t_alloc	g_alloc_large[ALLOC_NUM_LARGE];

extern t_alloc	g_region_tiny;
extern t_alloc	g_region_small;

void			*alloc_space(
	t_alloc *alloc, const t_alloc area, const size_t
	alloc_len, const size_t new_size);
void			sort_allocs(t_alloc **allocs, size_t size);

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);

void			show_alloc_mem(void);

void			show_alloc_mem_ex(void);

#endif
