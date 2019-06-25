#include "ft_malloc.h"

t_alloc g_alloc_tiny[ALLOC_NUM_TINY];
t_alloc g_alloc_small[ALLOC_NUM_SMALL];
t_alloc g_alloc_large[ALLOC_NUM_LARGE];
t_alloc g_region_small;
t_alloc g_region_tiny;

/* TODO: this */
void	*realloc(void *ptr, size_t size)
{
	(void)(ptr && size);
	return NULL;
}
