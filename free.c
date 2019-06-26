#include "ft_malloc.h"

t_alloc g_alloc_tiny[ALLOC_NUM_TINY];
t_alloc g_alloc_small[ALLOC_NUM_SMALL];
t_alloc g_alloc_large[ALLOC_NUM_LARGE];
t_alloc g_region_small;
t_alloc g_region_tiny;

/* TODO: handle error codes */
static int	dealloc(t_alloc *alloc)
{
	int ret;

	ret = munmap(alloc->start, alloc->size);
	alloc->start = NULL;
	alloc->size = 0;
	return ret;
}

/* TODO: atexit handler for unmap */
void		free(void *ptr)
{
	size_t i;

	if (!g_region_small.start || !g_region_tiny.start || ptr == NULL)
		return;
	i = 0;
	while (i < ALLOC_NUM_TINY)
	{
		if (g_alloc_tiny[i].start == ptr)
		{
			dealloc(&g_alloc_tiny[i]);
			return;
		}
		i++;
	}
	i = 0;
	while (i < ALLOC_NUM_SMALL)
	{
		if (g_alloc_small[i].start == ptr)
		{
			dealloc(&g_alloc_small[i]);
			return;
		}
		i++;
	}
	i = 0;
	while (i < ALLOC_NUM_LARGE)
	{
		if (g_alloc_large[i].start == ptr)
		{
			dealloc(&g_alloc_large[i]);
			return;
		}
		i++;
	}
}
