#include "ft_malloc.h"

t_alloc g_alloc_tiny[ALLOC_NUM_TINY];
t_alloc g_alloc_small[ALLOC_NUM_SMALL];
t_alloc g_alloc_large[ALLOC_NUM_LARGE];
t_alloc g_region_small;
t_alloc g_region_tiny;

/* TODO: hook main start? */
static void	init_mem()
{
	size_t i;

	g_region_tiny.start = mmap(NULL,ALLOC_NUM_TINY * ALLOC_SIZE_TINY, 0, 0, -1, 0);
	g_region_tiny.size = ALLOC_NUM_TINY * ALLOC_SIZE_TINY;
	g_region_small.start = mmap(NULL,ALLOC_NUM_SMALL * ALLOC_SIZE_SMALL, 0, 0, -1, 0);
	g_region_small.size = ALLOC_NUM_SMALL * ALLOC_SIZE_SMALL;
	i = 0;
	while (i < ALLOC_NUM_TINY)
	{
		g_alloc_tiny[i].start = NULL;
		g_alloc_tiny[i].size = 0;
	}
	i = 0;
	while (i < ALLOC_NUM_SMALL)
	{
		g_alloc_small[i].start = NULL;
		g_alloc_small[i].size = 0;
	}
	i = 0;
	while (i < ALLOC_NUM_LARGE)
	{
		g_alloc_large[i].start = NULL;
		g_alloc_large[i].size = 0;
	}
}

/* TODO: deal with null */
static void sort_allocs(t_alloc **allocs, size_t size)
{
	t_alloc	temp;
	size_t	i;
	size_t	j;

	while (i < size)
	{
		j = i++;
		while (j > 0 && ((*allocs)[j - 1].start > (*allocs)[j].start ||
			((*allocs)[j - 1].start == NULL && (*allocs)[j].start != NULL )))
		{
			temp = (*allocs)[j - 1];
			(*allocs)[j - 1] = (*allocs)[j];
			(*allocs)[j] = temp;
			j--;
		}
	}
}

static void *alloc_tiny()
{
	sort_allocs((t_alloc **)&g_alloc_tiny, ALLOC_NUM_TINY);
	// find first open space
	// return first open space

}

void		*malloc(size_t size)
{
	static char init = 0;
	void *ret;

	if (!init)
		init_mem();
	init = 1;
	if (size <= ALLOC_SIZE_TINY)
		return alloc_tiny();
	else if (size <= ALLOC_SIZE_SMALL)
		return alloc_small();
	else
		return alloc_large();
}
