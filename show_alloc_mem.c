#include "ft_malloc.h"
#include "ft_printf.h"

t_alloc g_alloc_tiny[ALLOC_NUM_TINY];
t_alloc g_alloc_small[ALLOC_NUM_SMALL];
t_alloc g_alloc_large[ALLOC_NUM_LARGE];
t_alloc g_region_small;
t_alloc g_region_tiny;

static size_t	show_tiny(void)
{
	size_t	i;
	size_t	ret;
	t_alloc	current;
	
	ft_printf("TINY : %p\n", g_region_tiny.start);
	sort_allocs((t_alloc *)g_alloc_tiny, ALLOC_NUM_TINY);
	i = 0;
	ret = 0;
	while (g_alloc_tiny[i].start != NULL && i < ALLOC_NUM_TINY)
	{
		current = g_alloc_tiny[i++];
		ft_printf("%p - %p : %zu bytes\n", current.start, (char *)
			current.start + current.size, current.size);
		ret += current.size;
	}
	return ret;
}

static size_t	show_small(void)
{
	size_t	i;
	size_t	ret;
	t_alloc	current;
	
	ft_printf("SMALL : %p\n", g_region_small.start);
	sort_allocs((t_alloc *)g_alloc_small, ALLOC_NUM_SMALL);
	i = 0;
	ret = 0;
	while (g_alloc_small[i].start != NULL && i < ALLOC_NUM_SMALL)
	{
		current = g_alloc_small[i++];
		ft_printf("%p - %p : %zu bytes\n", current.start, (char *)
			current.start + current.size, current.size);
		ret += current.size;
	}
	return ret;
}

static size_t	show_large(void)
{
	size_t	i;
	size_t	ret;
	t_alloc	current;
	
	ft_printf("LARGE : \n");
	sort_allocs((t_alloc *)g_alloc_large, ALLOC_NUM_LARGE);
	i = 0;
	ret = 0;
	while (g_alloc_large[i].start != NULL && i < ALLOC_NUM_LARGE)
	{
		current = g_alloc_large[i++];
		ft_printf("%p - %p : %zu bytes\n", current.start, (char *)
			current.start + current.size, current.size);
		ret += current.size;
	}
	return ret;
}

void			show_alloc_mem(void)
{
	size_t	size;

	size = show_tiny() + show_small() + show_large();
	ft_printf("Total : %zu bytes\n");
}

void			show_alloc_mem_ex(void)
{

}
