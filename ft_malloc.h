/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:38:49 by dslogrov          #+#    #+#             */
/*   Updated: 2019/06/19 16:03:03 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# define ALLOC_NUM_TINY 512
# define ALLOC_NUM_SMALL 128
# define ALLOC_SIZE_TINY (LONG_BIT / CHAR_BIT)
# define ALLOC_SIZE_SMALL 512

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

void	show_alloc_mem(void);

void	show_alloc_mem_ex(void);

#endif
