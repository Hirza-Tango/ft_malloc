#include "ft_malloc.h"
#include "libft.h"

int main()
{
	ft_putendl("Hi");
	void * a = malloc(1);
	void * b = malloc(9);
	void * c = malloc(513);
	show_alloc_mem();
	free(a);
	free(b);
	free(c);
	show_alloc_mem();
	ft_putendl("Bye");
}