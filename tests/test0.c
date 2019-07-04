#include "ft_malloc.h"

int main()
{
	int i;

	i = 0;
	char *addr;
	show_alloc_mem();
	while (i < 1024)
	{
		i++;
	}
	return 0;
}
