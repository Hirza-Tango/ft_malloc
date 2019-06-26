#include "ft_malloc.h"
#include "libft.h"
#include <stdio.h>
#include <time.h>

int main()
{
	printf("Hi\n");
	void *small_stuff[ALLOC_NUM_TINY + 1];
	void *med_stuff[ALLOC_NUM_SMALL + 1];
	void *large_stuff[ALLOC_NUM_LARGE + 1];
	srand(time(NULL));
	for (int i = 0; i <= ALLOC_NUM_TINY; i++){
		small_stuff[i] = malloc(rand() % (ALLOC_SIZE_TINY - 1) + 1);
	}
	for (int i = 0; i <= ALLOC_NUM_SMALL; i++){
		med_stuff[i] = malloc(rand() % (ALLOC_SIZE_SMALL - ALLOC_SIZE_TINY) + ALLOC_SIZE_TINY);
	}
	for (int i = 0; i <= ALLOC_NUM_LARGE; i++){
		large_stuff[i] = malloc(rand() % (getpagesize() - ALLOC_SIZE_SMALL) + ALLOC_SIZE_SMALL);
	}
	show_alloc_mem();
	printf("%p %p %p\n", small_stuff[ALLOC_NUM_TINY], med_stuff[ALLOC_NUM_SMALL], large_stuff[ALLOC_NUM_LARGE]);
	for (int i = 0; i <= ALLOC_NUM_TINY; i++){
		free(small_stuff[i]);
	}
	for (int i = 0; i <= ALLOC_NUM_SMALL; i++){
		free(med_stuff[i]);
	}
	for (int i = 0; i <= ALLOC_NUM_LARGE; i++){
		free(large_stuff[i]);
	}
	show_alloc_mem();
	ft_putendl("Bye");
}