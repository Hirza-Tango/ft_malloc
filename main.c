#include "ft_malloc.h"
#include "libft.h"
#include <stdio.h>
#include <time.h>

int main()
{
	printf("Hi\n");
	void *small_stuff[ALLOC_NUM_TINY];
	void *med_stuff[128];
	void *large_stuff[128];
	srand(time(NULL));
	for (int i = 0; i < 5; i++){
		small_stuff[i] = malloc(rand() % ALLOC_SIZE_TINY);
	}
	for (int i = 0; i < ALLOC_NUM_SMALL; i++){
		med_stuff[i] = malloc(rand() % (ALLOC_SIZE_SMALL - ALLOC_SIZE_TINY) + ALLOC_SIZE_TINY);
	}
	for (int i = 0; i < ALLOC_NUM_LARGE; i++){
		med_stuff[i] = malloc(rand() % (getpagesize() - ALLOC_SIZE_SMALL) + ALLOC_SIZE_SMALL);
	}
	show_alloc_mem();
	ft_putendl("Bye");
}