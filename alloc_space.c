#include "ft_malloc.h"

void	*alloc_space(t_allocation *alloc, const t_allocation area, const size_t alloc_len, const size_t new_size)
{
	void *start;
	size_t i;

	start = area.start;
	i = 0;
	while ((char *)start + new_size < (char *)area.start + area.size && i < alloc_len && alloc[i].start != NULL)
	{
		if ((unsigned)((char *)(alloc[i].start) - (char *)start) >= new_size)
			return start;
		start = (char *)(alloc[i].start) + alloc[i].size;
		i++;
	}
	return NULL;
}
